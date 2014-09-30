#include "util/app.h"
#include "util/auto_signal.h"
#include <unistd.h>

using namespace util;
using namespace std;

class cashier : public util::app {
  public:
    explicit cashier() :
      app("CASHIER"),
      halt(0),
      sigint(SIGINT, [this]() { halt = 1; }) { }

  protected:
    virtual void do_run() override {
      log.info("Starting check loop");

      while (!halt) {
        // TODO: Implement cashier process, simulated for now
        log.info("Before going to sleep");
        sleep(1);
        log.info("Woke up!");
      }

      log.info("Halt was set, terminating");
    }

  private:
    sig_atomic_t halt;

    auto_signal sigint;
};

DEFINE_MAIN(cashier);

