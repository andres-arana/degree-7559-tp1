#include "util/sync_log.h"
#include "util/auto_proc.h"
#include <cstdlib>
#include <vector>
#include <sstream>

using namespace util;
using namespace std;

int main(int argc, char** argv) {
  sync_log log;

  log.info("Starting SPAWNER process");

  if (argc < 2) {
    log.error("SPWANER process not given the amount of children to spawn");
    return EXIT_FAILURE;
  }

  auto processes = atoi(argv[1]);

  {
    vector<auto_proc> children(processes);

    for (int i = 0; i < processes; i++) {
      children.push_back(auto_proc("build/exec/child", {}));
      log.info("Launched CHILD process");
    }

    log.info("All CHILD processes launched, waiting for termination");
  }

  log.info("All CHILD processes finished");

  return EXIT_SUCCESS;
}
