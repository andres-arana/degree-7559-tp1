#include "util/auto_proc.h"
#include "util/app.h"

using namespace util;
using namespace std;

class director : public util::app {
  public:
    explicit director() :
      app("DIRECTOR"),
      children("c", "children", "Amount of children", true, 0, "int", args) { }

  protected:
    virtual void do_run() override {
      log.separator();
      log.info("Simulation started");
      log.debug("About to start all controller processes");

      auto log_level = configured_log_level();

      {
        auto_proc audit(true, "build/exec/audit", "-l", log_level);
        log.debug("Started AUDIT process with id $", audit.pid());

        auto_proc carrousel(true, "build/exec/carrousel", "-l", log_level);
        log.debug("Started CARROUSEL process with id $", carrousel.pid());

        auto_proc cashier(true, "build/exec/cashier", "-l", log_level);
        log.debug("Started CASHIER process with id $", cashier.pid());

        {
          auto_proc spawner(false, "build/exec/spawner",
              "-c", children.getValue(), "-l", log_level);
          log.debug("Started SPAWNER process with id $", spawner.pid());
        }
      }

      log.debug("All controller processes finished");
      log.info("Simulation completed");
    }

  private:
    TCLAP::ValueArg<int> children;
};

DEFINE_MAIN(director);

