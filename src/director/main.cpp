#include "util/app.h"
#include "util/names.h"
#include "util/proc_service.h"
#include "util/shared_data.h"
#include "raii/signal.h"
#include "raii/fifo_owner.h"
#include "raii/sem_owner.h"
#include "raii/shmem_owner.h"
#include "raii/shmem.h"
#include "raii/temp_file.h"
#include <iostream>

using namespace std;

class director : public util::app {
  public:
    explicit director() :
      app("DIRECTOR"),
      price("p", "price", "Amount to charge", true, 0, "int", args),
      carrousel_capacity("c", "capacity", "Amount of places in the carrousel", true, 0, "int", args),
      lap_duration("d", "duration", "Amount of seconds a carrousel lap lasts", true, 0, "int", args) {}

  protected:
    virtual void do_run() override {
      log.info("Simulation started");
      log.debug("About to start all controller processes");

      log.debug("Creating shared memory");
      raii::shmem_owner<util::shared_data> shmem;

      log.debug("Attaching to shared memory for initialization");
      raii::shmem<util::shared_data> memory(shmem.id());
      memory->balance = 0;
      memory->config_price = price.getValue();
      memory->config_duration = lap_duration.getValue();
      memory->config_capacity = carrousel_capacity.getValue();

      log.debug("Creating lock file for the balance");
      raii::temp_file balance_file(NAMES_BALANCE_FILE);

      log.debug("Creating FIFO for cashierq");
      raii::fifo_owner cashierq_fifo(NAMES_CASHIERQ_FIFO);

      log.debug("Creating FIFO for carrouselq");
      raii::fifo_owner carrouselq_fifo(NAMES_CARROUSELQ_FIFO);

      log.debug("Creating binary semaphores for cashier");
      raii::sem_owner cashier_sem(NAMES_SEM_CASHIER_AMOUNT, {1, 0, 0, 0});
      memory->sem_cashier = cashier_sem.id();

      log.debug("Creating binary semaphore for carrousel entrance");
      raii::sem_owner carrousel_entrance_sem(NAMES_SEM_CARROUSEL_AMOUNT, 1);
      memory->sem_carrousel_entrance = carrousel_entrance_sem.id();

      log.debug("Creating binary semaphores for the carrousel places");
      raii::sem_owner carrousel_places_sem(carrousel_capacity.getValue(), 1);
      memory->sem_carrousel_places = carrousel_places_sem.id();

      {
        util::proc_service  audit("build/exec/audit", log, shmem);
        util::proc_service  carrousel("build/exec/carrousel", log, shmem);
        util::proc_service  carrouselq("build/exec/carrouselq", log, shmem);
        util::proc_service  cashier("build/exec/cashier", log, shmem);
        util::proc_service  cashierq("build/exec/cashierq", log, shmem);
        util::proc_service  spawner("build/exec/spawner", log, shmem);

        log.debug("All process spawned");

        cout << "Simulation running, press enter to stop it" << endl;
        cin.ignore();

        log.debug("Sending interruption signal to all proccesses");
      }

      log.debug("All controller processes finished");
      log.info("Simulation completed");
    }

  private:
    TCLAP::ValueArg<unsigned int> price;
    TCLAP::ValueArg<unsigned int> carrousel_capacity;
    TCLAP::ValueArg<unsigned int> lap_duration;
};

DEFINE_MAIN(director);

