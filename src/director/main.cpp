#include "util/sync_log.h"
#include "util/auto_proc.h"
#include <cstdlib>

using namespace util;

int main() {
  sync_log log("DIRECTOR");

  log.info("Starting");

  log.info("About to start all controller processes");

  {
    auto_proc_int audit("build/exec/audit", {});
    auto_proc_int carrousel("build/exec/carrousel", {});
    auto_proc_int cashier("build/exec/cashier", {});

    {
      auto_proc spawner("build/exec/spawner", { "10" });
    }

    log.info("All controller processes spawned, waiting for termination");
  }

  log.info("Finishing");

  return EXIT_SUCCESS;
}
