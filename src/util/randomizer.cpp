#include "util/randomizer.h"
#include <cstdlib>
#include <time.h>

using namespace util;

randomizer::randomizer(unsigned long min, unsigned long max)
  : min(min), max(max) {
    srand(time(nullptr));
  }

unsigned long randomizer::next() {
  return rand() % (max - min) + min;
}
