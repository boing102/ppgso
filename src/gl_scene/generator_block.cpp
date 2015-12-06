#include "generator_block.h"
#include "block.h"

bool Generator_Block::Update(Scene &scene, float dt) {
  // Accumulate time
  time += dt;

  // Add object to scene when time reaches certain level
  if (time > 2 && previouslySpawned == NULL) {
    auto obj = BlockPtr(new Block());
    previouslySpawned = obj;
    obj->position = this->position;
    obj->position.x += 0;
    scene.objects.push_back(obj);
    time = 0;
  }

  return true;
}

void Generator_Block::Render(Scene &scene) {
  // Generator will not be rendered
}

Generator_Block::~Generator_Block() {
}

Generator_Block::Generator_Block() {
  time = 0;
}
