#include "util/sync_log.h"
#include "util/auto_proc.h"
#include <cstdlib>

using namespace util;

int main() {
  sync_log log;

  log.info("Starting DIRECTOR process");

  log.info("About to start all controller processes");

  {
    auto_proc audit("build/exec/audit", {});
    auto_proc carrousel("build/exec/carrousel", {});
    auto_proc cashier("build/exec/cashier", {});
    auto_proc spawner("build/exec/spawner", { "10" });

    log.info("All controller processes spawned, waiting for termination");
  }

  log.info("Controller processes finished, simulation completed");

  return EXIT_SUCCESS;
}
