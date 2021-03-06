#ifndef PPGSO_BLOCK_H
#define PPGSO_BLOCK_H

#include <memory>

#include "scene.h"
#include "object.h"
#include "mesh.h"
#include "texture.h"
#include "shader.h"

// Simple asteroid object
// This sphere object represents an instance of mesh geometry
// It initializes and loads all resources only once
// It will move down along the Y axis and self delete when reaching below -10
class Block : public Object {
public:
  Block();
  ~Block();

  // Implement object interface
  bool Update(Scene &scene, float dt) override;
  void Render(Scene &scene) override;

  float left();
  float right();
  float top();
  float bottom();

    // Speed momentum
    glm::vec3 speed;
private:
  // Rotation momentum
  glm::vec3 rotMomentum;

  // Static resources (Shared between instances)
  static MeshPtr mesh;
  static ShaderPtr shader;
  static TexturePtr texture;
};
typedef std::shared_ptr<Block> BlockPtr;

#endif //PPGSO_BLOCK_H
