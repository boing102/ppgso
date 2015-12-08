#include "generator_block.h"
#include "block.h"
#include "brick.h"

bool Generator_Block::Update(Scene &scene, float dt) {

  float offset = 0.0f;
  // Spawn 5 brick
  while(spawnedBricks < 5) {
    auto brick = BrickPtr(new Brick());
    brick->position = this->position;
    brick->position.y += offset;
    scene.objects.push_back(brick);
    spawnedBricks++;
    offset += 1.1f;
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
  spawnedBricks = 0;
}
