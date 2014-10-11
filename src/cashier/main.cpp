#include "util/app.h"
#include "raii/signal.h"
#include <unistd.h>

using namespace std;

class cashier : public util::app {
  public:
    explicit cashier() :
      app("CASHIER"),
      halt(0),
      sigint(SIGINT, [this]() { halt = 1; }) { }

  protected:
    virtual void do_run() override {
      log.debug("Starting check loop");

      while (!halt) {
        // TODO: Implement cashier process, simulated for now
        log.debug("Before going to sleep");
        sleep(1);
        log.debug("Woke up!");
      }

      log.debug("Halt was set, terminating");
    }

  private:
    sig_atomic_t halt;

    raii::signal sigint;
};

DEFINE_MAIN(cashier);

