#include "util/app.h"
#include <unistd.h>

using namespace util;
using namespace std;

namespace {
  class child : public util::app {
    public:
      explicit child() :
        app("CHILD") { }

    protected:
      virtual void do_run() override {
        log.info("About to sleep for 3 seconds");
        sleep(3);
        log.info("Woke up");
      }
  };
}

DEFINE_MAIN(::child);

