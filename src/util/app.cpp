#include "util/app.h"

using namespace std;
using namespace util;

app::app(const string& name)
  : log(name),
  args(name),
  log_level("l", "loglevel", "Log level to use", true, 0, "int", args) {

  }

int app::run(int argc, char** argv) {
  args.parse(argc, argv);

  log.set_level(log_level.getValue());

  log.debug("Starting");

  do_run();

  log.debug("Terminating");

  return EXIT_SUCCESS;
}

