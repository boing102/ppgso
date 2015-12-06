#include "generator.h"
#include "asteroid.h"

bool Generator::Update(Scene &scene, float dt) {
  // Accumulate time
  time += dt;

  // Add object to scene when time reaches certain level
  if (time > 5) {
    auto obj = AsteroidPtr(new Asteroid());
    obj->position = this->position;
    obj->position.x += 0;
    scene.objects.push_back(obj);
    time = 0;
  }

  return true;
}

void Generator::Render(Scene &scene) {
  // Generator will not be rendered
}

Generator::~Generator() {
}

Generator::Generator() {
  time = 0;
}
