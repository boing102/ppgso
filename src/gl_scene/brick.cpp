#include "brick.h"

#include "object_frag.h"
#include "object_vert.h"
#include "block.h"

#include <GLFW/glfw3.h>

Brick::Brick() {
  // Set random scale speed and rotation
  scale *= 1.0f;
  speed = glm::vec3(0.0f, 0.0f, 0.0f);
  rotation = glm::vec3(0.0f, 0.0f, 0.0f);
  lives = (int) Rand(1.0f, 3.0f);
  animateTop = false;
  animateBot = false;

  // Initialize static resources if needed
  if (!shader) shader = ShaderPtr(new Shader{object_vert, object_frag});
  if(lives == 1) {
    texture = TexturePtr(new Texture{"green.rgb", 256, 256});
  } else if(lives == 2) {
    texture = TexturePtr(new Texture{"red.rgb", 256, 256});
  }
  if (!mesh) mesh = MeshPtr(new Mesh{shader, "brick.obj"});
}

Brick::~Brick() {
}

bool Brick::Update(Scene &scene, float dt) {

  
  if(animateTop) {
    this->position.y = animBot.y + (animTop.y-animBot.y)*t;
    t+=0.5f;
    printf("t\n");
    if(this->position.y >= animTop.y) {
      animateTop = false;
    }
  }

  // Collide with scene
  for (auto obj : scene.objects) {
    // Ignore self in scene
    if (obj.get() == this) continue;

    // We only need to collide with asteroids and projectiles, ignore other objects
    auto ball = std::dynamic_pointer_cast<Block>(obj);
    if (!ball) continue;

    // Compare distance to approximate size of the ball estimated from scale.
    if ((glm::distance(position.y, ball->position.y) < 0.686f ) &&
        ((glm::distance(position.x, ball->position.x) < 1.391f ))) {
      // Change ball's speed
      ball->speed.y = -ball->speed.y;

      if(ball->position.x < position.x) {
        ball->speed.x = -ball->speed.x;
      }
      else {
        ball->speed.x = ball->speed.x;
      }


      lives--;
      if(lives == 1) {
        texture = TexturePtr(new Texture{"green.rgb", 256, 256});
        animateTop = true;
        animBot = this->position;
        animTop = this->position + glm::vec3(0.0f,0.3f,0.0f);
        t = 0;
      } else if(lives == 0) {
        return false;
      }
    }
  }

  // Generate modelMatrix from position, rotation and scale
  GenerateModelMatrix();

  return true;
}

void Brick::Render(Scene &scene) {
  shader->Use();

  // use camera
  shader->SetMatrix(scene.camera->projectionMatrix, "ProjectionMatrix");
  shader->SetMatrix(scene.camera->viewMatrix, "ViewMatrix");

  // render mesh
  shader->SetMatrix(modelMatrix, "ModelMatrix");
  shader->SetTexture(texture, "Texture");
  shader->SetVector(scene.camera->position, "ViewPosition");
  mesh->Render();
}

// shared resources
MeshPtr Brick::mesh;
ShaderPtr Brick::shader;
