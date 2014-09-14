#include "util/sync_log.h"
#include <cstdlib>
#include <unistd.h>

int main() {
  util::sync_log log;

  log.info("Starting CHILD process");

  sleep(3);

  log.info("CHILD process is finishing");

  return EXIT_SUCCESS;
}
