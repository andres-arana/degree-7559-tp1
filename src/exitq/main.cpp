#include "util/app.h"
#include "raii/signal.h"
#include <unistd.h>

using namespace std;

class exitq : public util::app {
  public:
    explicit exitq() :
      app("EXITQ"),
      halt(0),
      sigint(SIGINT, [this]() { halt = 1; }) { }

  protected:
    virtual void do_run() override {
      log.debug("Starting check loop");

      while (!halt) {
        // TODO: Implement exitq process, simulated for now
        sleep(1);
      }

      log.debug("Halt was set, terminating");
    }

  private:
    sig_atomic_t halt;

    raii::signal sigint;
};

DEFINE_MAIN(exitq);

