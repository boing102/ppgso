#ifndef PPGSO_BRICK_H
#define PPGSO_BRICK_H

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
class Brick : public Object {
public:
  Brick();
  ~Brick();

  // Implement object interface
  bool Update(Scene &scene, float dt) override;
  void Render(Scene &scene) override;


  // Speed momentum
  glm::vec3 speed;
  int lives;

private:
  bool animateTop;
  bool animateBot;
  glm::vec3 animTop;
  glm::vec3 animBot;
  // Static resources (Shared between instances)
  static MeshPtr mesh;
  static ShaderPtr shader;
  float t;

  TexturePtr texture;
};
typedef std::shared_ptr<Brick> BrickPtr;

#endif //PPGSO_BRICK_H
