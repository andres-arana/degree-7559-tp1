#include "util/util.h"
#include "raii/raii.h"
#include <unistd.h>

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

    raii::auto_signal sigint;
};

DEFINE_MAIN(audit);

