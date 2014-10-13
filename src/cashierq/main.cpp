#include "util/app.h"
#include "util/names.h"
#include "util/shared_data.h"
#include "util/randomizer.h"
#include "raii/signal.h"
#include "raii/fifo_reader.h"
#include "raii/shmem.h"
#include "raii/sem.h"

using namespace std;

class cashierq : public util::app {
  public:
    explicit cashierq() :
      app("CASHIERQ"),
      halt(0),
      semid("s", "semaphore", "Semaphore id", true, 0, "int", args),
      shmemid("m", "memory", "Shared memory id", true, 0, "int", args),
      randomizer(100, 200),
      sigint(SIGINT, [this]() { halt = 1; }) { }

  protected:
    virtual void do_run() override {
      log.debug("Attaching shared memory");
      raii::shmem<util::shared_data> shmem(shmemid.getValue());

      log.debug("Constructing semaphores");
      raii::sem cashier_sem(semid.getValue(), NAMES_SEM_CASHIER_CASHIER);
      raii::sem child_sem(semid.getValue(), NAMES_SEM_CASHIER_CHILD);
      raii::sem money_sem(semid.getValue(), NAMES_SEM_CASHIER_MONEY);
      raii::sem change_sem(semid.getValue(), NAMES_SEM_CASHIER_CHANGE);

      log.debug("Opening cashierq fifo for reading");
      raii::fifo_reader<unsigned long> fifo(NAMES_CASHIERQ_FIFO);
      log.debug("Fifo opened, starting arrival loop");

      while (!halt) {
        log.debug("Reading a child id from the cashier queue");
        auto id = fifo.read();

        log.debug("Read child id $ from cashier queue", id);

        log.info("Child $ is waiting for the cashier to be available", id);
        cashier_sem.wait();

        log.debug("The cashier is mine. Writting child id.");
        shmem->child_id = id;

        log.debug("Child id provided, making it available");
        child_sem.signal();

        log.debug("Writing money to shared memory");
        shmem->money = randomizer.next();

        log.info("The child $ gives $ money to the cashier", id, shmem->money);
        money_sem.signal();

        log.info("The child $ is waiting for the change", id);
        change_sem.wait();
        log.info("The child $ received change $", id, shmem->change);

        log.info("Child $ is done with the cashier, going to the carrousel", id);
        cashier_sem.signal();

        // TODO: Go to the carrousel
      }

      log.debug("Halt was set, terminating");
    }

  private:
    sig_atomic_t halt;
    TCLAP::ValueArg<int> semid;
    TCLAP::ValueArg<int> shmemid;
    util::randomizer randomizer;
    raii::signal sigint;
};

DEFINE_MAIN(cashierq);

