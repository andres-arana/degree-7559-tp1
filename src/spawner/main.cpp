#include "util/sync_log.h"
#include "util/auto_proc.h"
#include <cstdlib>
#include <vector>

using namespace util;
using namespace std;

int main(int argc, char** argv) {
  sync_log log("SPAWNER");

  log.info("Starting");

  if (argc < 2) {
    log.error("I don't know the amount of processes to spawn");
    return EXIT_FAILURE;
  }

  auto processes = atoi(argv[1]);

  log.info("I will spawn $ CHILD processes", processes);

  vector<string> args;

  {
    vector<auto_proc> children;

    for (int i = 0; i < processes; i++) {
      children.emplace_back("build/exec/child", args);
      log.info("Launched CHILD process $", children.back().pid());
    }

    log.info("All CHILD processes launched, waiting for termination");
  }

  log.info("Finishing");

  return EXIT_SUCCESS;
}
