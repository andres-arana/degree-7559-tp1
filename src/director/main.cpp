#include "util/app.h"
#include "util/names.h"
#include "util/proc_audit.h"
#include "util/proc_carrousel.h"
#include "util/proc_cashier.h"
#include "util/proc_cashierq.h"
#include "util/proc_spawner.h"
#include "raii/signal.h"
#include "raii/fifo_owner.h"
#include <iostream>

using namespace std;

class director : public util::app {
  public:
    explicit director() :
      app("DIRECTOR") { }

  protected:
    virtual void do_run() override {
      log.info("Simulation started");
      log.debug("About to start all controller processes");

      log.debug("Creating FIFO for cashierq");
      raii::fifo_owner cashierq_fifo(NAMES_CASHIERQ_FIFO);

      {
        util::proc_audit audit(log);
        util::proc_carrousel carrousel(log);
        util::proc_cashier cashier(log);
        util::proc_cashierq cashierq(log);
        util::proc_spawner spawner(log);

        log.debug("All process spawned");

        cout << "Simulation running, press enter to stop it" << endl;
        cin.ignore();

        log.debug("Sending interruption signal to all proccesses");
      }

      log.debug("All controller processes finished");
      log.info("Simulation completed");
    }
};

DEFINE_MAIN(director);

