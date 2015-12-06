#include "world.h"
#include "scene.h"
#include "asteroid.h"
#include "projectile.h"
#include "explosion.h"

#include "object_frag.h"
#include "object_vert.h"

#include <GLFW/glfw3.h>

World::World() {
  // Scale the default model
  scale *= 3.0f;

  // Initialize static resources if needed
  if (!shader) shader = ShaderPtr(new Shader{object_vert, object_frag});
  if (!texture) texture = TexturePtr(new Texture{"sphere.rgb", 256, 256});
  if (!mesh) mesh = MeshPtr(new Mesh{shader, "world.obj"});
}

World::~World() {
}

bool World::Update(Scene &scene, float dt) {
  GenerateModelMatrix();
  return true;
}

void World::Render(Scene &scene) {
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
MeshPtr World::mesh;
ShaderPtr World::shader;
TexturePtr World::texture;