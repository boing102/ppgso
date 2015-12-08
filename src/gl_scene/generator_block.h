#ifndef PPGSO_GENERATOR_BLOCK_H
#define PPGSO_GENERATOR_BLOCK_H

#include <random>
#include "object.h"
#include "scene.h"
#include "block.h"

// Example generator of objects
// Constructs a new object during Update and adds it into the scene
// Does not render anything
class Generator_Block : public Object {
public:
  Generator_Block();
  ~Generator_Block();

  bool Update(Scene &scene, float dt) override;
  void Render(Scene &scene) override;

  float time;
  int spawnedBricks;
};
typedef std::shared_ptr< Generator_Block > GeneratorBlockPtr;

#endif //PPGSO_GENERATOR_BLOCK_H
