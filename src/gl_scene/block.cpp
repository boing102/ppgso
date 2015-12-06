#include "block.h"

#include "object_frag.h"
#include "object_vert.h"

#include <GLFW/glfw3.h>

Block::Block() {
  // Set random scale speed and rotation
  scale *= 2.0f;
  speed = glm::vec3(0.0f, -3.5f, 0.0f);
  rotation = glm::vec3(PI, 0.0f, 0.0f);
  rotMomentum = glm::vec3(0.0f, 0.0f, 0.0f);
  isMoving = true;
  angle = 0;

  // Initialize static resources if needed
  if (!shader) shader = ShaderPtr(new Shader{object_vert, object_frag});
  if (!texture) texture = TexturePtr(new Texture{"asteroid.rgb", 512, 512});
  if (!mesh) mesh = MeshPtr(new Mesh{shader, "block2.obj"});
}

Block::~Block() {
}

bool Block::Update(Scene &scene, float dt) {

  // Animate position according to time
  //position += speed * dt;

  // Keyboard controls
  if(scene.keyboard[GLFW_KEY_LEFT]) {
    angle -= PI/2 *dt;
  } else if(scene.keyboard[GLFW_KEY_RIGHT]) {
    modelMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,0.0f,0.0f));
  }

  // Stop moving when you get to the bottom
  if (position.y < -10.9f) {
    speed = glm::vec3(0.0f, 0.0f, 0.0f);
  }

  // Generate modelMatrix from position, rotation and scale
  //GenerateModelMatrix();

 // modelMatrix = glm::translate(modelMatrix,glm::vec3(0.0f,0.0f,0.0f));
  modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0.0f,0.0f,1.0f));
//  modelMatrix = glm::translate(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f,0.0f,1.0f)),position);

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

// shared resources
MeshPtr Block::mesh;
ShaderPtr Block::shader;
TexturePtr Block::texture;
