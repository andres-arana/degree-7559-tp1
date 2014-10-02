#include "util/app.h"
#include "util/auto_signal.h"
#include <unistd.h>

using namespace util;
using namespace std;

class audit : public util::app {
  public:
    explicit audit() :
      app("AUDIT"),
      halt(0),
      sigint(SIGINT, [this]() { halt = 1; }) { }

  protected:
    virtual void do_run() override {
      log.debug("Starting check loop");

      while (!halt) {
        // TODO: Implement audit process, simulated for now
        log.debug("Before going to sleep");
        sleep(1);
        log.debug("Woke up!");
      }

      log.debug("Halt was set, terminating");
    }

  private:
    sig_atomic_t halt;

    auto_signal sigint;
};

DEFINE_MAIN(audit);

