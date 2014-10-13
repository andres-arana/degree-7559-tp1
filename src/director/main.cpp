#include "util/app.h"
#include "util/names.h"
#include "util/proc_audit.h"
#include "util/proc_carrousel.h"
#include "util/proc_cashier.h"
#include "util/proc_cashierq.h"
#include "util/proc_spawner.h"
#include "util/shared_data.h"
#include "raii/signal.h"
#include "raii/fifo_owner.h"
#include "raii/sem_owner.h"
#include "raii/shmem_owner.h"
#include <iostream>

using namespace std;

class director : public util::app {
  public:
    explicit director() :
      app("DIRECTOR"),
      price("p", "price", "Amount to charge", true, 0, "int", args) {}

  protected:
    virtual void do_run() override {
      log.info("Simulation started");
      log.debug("About to start all controller processes");

      log.debug("Creating FIFO for cashierq");
      raii::fifo_owner cashierq_fifo(NAMES_CASHIERQ_FIFO);

      log.debug("Creating binary semaphores for cashier");
      raii::sem_owner cashier_sem(NAMES_SEM_CASHIER_AMOUNT, {1, 0, 0, 0});

      log.debug("Creating shared memory for cashier");
      raii::shmem_owner<util::shared_data> cashier_shmem;

      {
        util::proc_audit audit(
            log);
        util::proc_carrousel carrousel(
            log);
        util::proc_cashier cashier(
            log, cashier_sem.id(), cashier_shmem.id(), price.getValue());
        util::proc_cashierq cashierq(
            log, cashier_sem.id(), cashier_shmem.id());
        util::proc_spawner spawner(
            log);

        log.debug("All process spawned");

        cout << "Simulation running, press enter to stop it" << endl;
        cin.ignore();

        log.debug("Sending interruption signal to all proccesses");
      }

      log.debug("All controller processes finished");
      log.info("Simulation completed");
    }

  private:
    TCLAP::ValueArg<int> price;
};

DEFINE_MAIN(director);

