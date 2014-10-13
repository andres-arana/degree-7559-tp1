#include "util/app.h"
#include "util/names.h"
#include "util/shared_data.h"
#include "raii/signal.h"
#include "raii/shmem.h"
#include "raii/sem.h"
#include <unistd.h>

using namespace std;

class cashier : public util::app {
  public:
    explicit cashier() :
      app("CASHIER"),
      halt(0),
      semid("s", "semaphore", "Semaphore id", true, 0, "int", args),
      shmemid("m", "memory", "Shared memory id", true, 0, "int", args),
      price("p", "price", "Amount to charge", true, 0, "int", args),
      sigint(SIGINT, [this]() { halt = 1; }) { }

  protected:
    virtual void do_run() override {
      log.debug("Attaching shared memory");
      raii::shmem<util::shared_data> shmem(shmemid.getValue());

      log.debug("Constructing semaphores");
      raii::sem child_sem(semid.getValue(), NAMES_SEM_CASHIER_CHILD);
      raii::sem money_sem(semid.getValue(), NAMES_SEM_CASHIER_MONEY);
      raii::sem change_sem(semid.getValue(), NAMES_SEM_CASHIER_CHANGE);

      while (!halt) {
        log.info("The cashier is waiting for the next child");
        child_sem.wait();
        log.info("The cashier is serving child $", shmem->child_id);

        log.info("The cashier is waiting for the child's money");
        money_sem.wait();
        log.info("The cashier received $ from the child $", shmem->money, shmem->child_id);

        log.debug("Writting change to shared memory");
        shmem->change = shmem->money - price.getValue();

        log.info("The cashier is giving the child $ the change $", shmem->child_id, shmem->change);
        change_sem.signal();
      }

      log.debug("Halt was set, terminating");
    }

  private:
    sig_atomic_t halt;
    TCLAP::ValueArg<int> semid;
    TCLAP::ValueArg<int> shmemid;
    TCLAP::ValueArg<int> price;
    raii::signal sigint;
};

DEFINE_MAIN(cashier);

