#include "util/sync_log.h"
#include <cstdlib>

using namespace util;

int main() {
  sync_log log("CASHIER");

  log.info("Starting");

  log.info("Finishing");

  return EXIT_SUCCESS;
}
