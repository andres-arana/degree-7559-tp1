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
      log.info("About to start all controller processes");

      {
        auto_proc audit("build/exec/audit");
        auto_proc carrousel("build/exec/carrousel");
        auto_proc cashier("build/exec/cashier");

        {
          auto_proc spawner("build/exec/spawner", "-c", children.getValue());

          log.info("All controller processes spawned, waiting for termination");
        }

      }

      log.info("All controller processes finished");
    }

  private:
    TCLAP::ValueArg<int> children;
};

DEFINE_MAIN(director);

