#include "util/sync_log.h"
#include "util/auto_proc.h"
#include <cstdlib>

using namespace std;

int main() {
  util::sync_log log;

  log.info("Starting AUDIT process");

  log.info("About to fork CHILD process");

  {
    util::auto_proc process("build/exec/child");

    log.info("CHILD process forked, waiting for process to finish");
  }

  log.info("CHILD finished executing"); 

  return EXIT_SUCCESS;
}
