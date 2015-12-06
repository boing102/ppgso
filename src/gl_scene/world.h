#ifndef PPGSO_WORLD_H
#define PPGSO_WORLD_H

#include <texture.h>
#include <shader.h>
#include <mesh.h>

#include "object.h"

// Simple object representing the player
// Reads keyboard status and manipulates its own position
// On Update checks collisions with Asteroid objects in the scene
class World : public Object {
public:
   World();
  ~World();

  bool Update(Scene &scene, float dt) override;
  void Render(Scene &scene) override;

//private:
    // Nothing for now

  // Static resources (Shared between instances)
  static MeshPtr mesh;
  static ShaderPtr shader;
  static TexturePtr texture;
};
typedef std::shared_ptr< World > WorldPtr;

#endif //PPGSO_WORLD_H
