#include "util/sync_log.h"
#include <cstdlib>
#include <unistd.h>

int main() {
  util::sync_log log("CHILD");

  log.info("Starting");

  sleep(3);

  log.info("Finishing");

  return EXIT_SUCCESS;
}
