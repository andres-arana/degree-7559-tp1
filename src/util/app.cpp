#include "util/app.h"

using namespace std;
using namespace util;

app::app(const string& name)
  : log(name), args(name) {
  
  }

int app::run(int argc, char** argv) {
  log.info("Starting");

  args.parse(argc, argv);

  do_run();

  log.info("Terminating");

  return EXIT_SUCCESS;
}

