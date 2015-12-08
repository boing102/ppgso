#include "player.h"
#include "scene.h"
#include "asteroid.h"
#include "projectile.h"
#include "explosion.h"

#include "object_frag.h"
#include "object_vert.h"
#include "block.h"

#include <GLFW/glfw3.h>

Player::Player() {
  // Rotate and scale model
  rotation = glm::vec3(PI, 0.0f, 0.0f);
  scale *= 1.5f;

  // Initialize static resources if needed
  if (!shader) shader = ShaderPtr(new Shader{object_vert, object_frag});
  if (!texture) texture = TexturePtr(new Texture{"asteroid.rgb", 512, 512});
  if (!mesh) mesh = MeshPtr(new Mesh{shader, "brick.obj"});
}

Player::~Player() {
}

bool Player::Update(Scene &scene, float dt) {

  // Hit detection
  for ( auto obj : scene.objects ) {
    // Ignore self in scene
    if (obj.get() == this)
      continue;

    // We only need to collide with ball
    auto ball = std::dynamic_pointer_cast<Block>(obj);
    if (!ball) continue;

    if ((glm::distance(position.y, ball->position.y) < 0.886f ) &&
        ((glm::distance(position.x, ball->position.x) < 1.391f ))) {

      // Change ball's speed
      ball->speed.y *=-1.0f;

      if(ball->position.x < position.x) {
        ball->speed.x *=-1.0f;
      }
      else {
       ball->speed.x *=1.0f;
      }
    }
  }

  // Keyboard controls
  if(scene.keyboard[GLFW_KEY_LEFT]) {
    position.x += 10 * dt;
  } else if(scene.keyboard[GLFW_KEY_RIGHT]) {
    position.x -= 10 * dt;
  } else {
    rotation.z = 0;
  }

  GenerateModelMatrix();
  return true;
}

void Player::Render(Scene &scene) {
  shader->Use();

  // use camera
  shader->SetMatrix(scene.camera->projectionMatrix, "ProjectionMatrix");
  shader->SetMatrix(scene.camera->viewMatrix, "ViewMatrix");

  // render mesh
  shader->SetMatrix(modelMatrix, "ModelMatrix");
  shader->SetTexture(texture, "Texture");
  mesh->Render();
}

float Player::left() {
  return position.x + 1.835f;
}
float Player::right() {
  return position.x - 1.835f;
}
float Player::top() {
  return position.y - 0.453f;
}
float Player::bottom() {
  return position.y + 0.453f;
}

// shared resources
MeshPtr Player::mesh;
ShaderPtr Player::shader;
TexturePtr Player::texture;