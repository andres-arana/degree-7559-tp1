#include "util/sync_log.h"
#include <cstdlib>

using namespace util;

int main() {
  sync_log log;

  log.info("Starting AUDIT process");

  return EXIT_SUCCESS;
}
