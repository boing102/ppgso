#include "block.h"

#include "object_frag.h"
#include "object_vert.h"

#include <GLFW/glfw3.h>

Block::Block() {
  // Set random scale speed and rotation
  scale *= 1.0f;
  speed = glm::vec3(Rand(-5.0f, 5.0f), 10.5f, 0.0f);
  rotation = glm::vec3(PI, 0.0f, 0.0f);
  rotMomentum = glm::vec3(0.0f, 0.0f, 0.0f);

  // Initialize static resources if needed
  if (!shader) shader = ShaderPtr(new Shader{object_vert, object_frag});
  if (!texture) texture = TexturePtr(new Texture{"sphere.rgb", 256, 256});
  if (!mesh) mesh = MeshPtr(new Mesh{shader, "ball2.obj"});
}

Block::~Block() {
}

bool Block::Update(Scene &scene, float dt) {

  // Animate position according to time
  position += speed * dt;

  // Collisions with view borders
  if(left() < -7.5f) {
    speed.x *= -1;
  }
  else if(right() > 7.5f) {
    speed.x *= -1;
  }
  if(top() > 7.5f) {
    speed.y *= -1;
  }

  if(bottom() < -7.5f) {
    speed.y *= -1;
  }

  // Generate modelMatrix from position, rotation and scale
  GenerateModelMatrix();

  return true;
}

void Block::Render(Scene &scene) {
  shader->Use();

  // use camera
  shader->SetMatrix(scene.camera->projectionMatrix, "ProjectionMatrix");
  shader->SetMatrix(scene.camera->viewMatrix, "ViewMatrix");

  // render mesh
  shader->SetMatrix(modelMatrix, "ModelMatrix");
  shader->SetTexture(texture, "Texture");
  mesh->Render();
}

float Block::left() {
  return position.x + 0.686f;
}
float Block::right() {
  return position.x - 0.686f;
}
float Block::top() {
  return position.y - 0.686f;
}
float Block::bottom() {
  return position.y + 0.686f;
}

// shared resources
MeshPtr Block::mesh;
ShaderPtr Block::shader;
TexturePtr Block::texture;
