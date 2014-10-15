#include "util/app_owned.h"
#include "util/names.h"
#include "util/randomizer.h"
#include "raii/fifo_reader.h"
#include "raii/fifo_writer.h"
#include "raii/sem.h"

using namespace std;

class cashierq : public util::app_owned {
  public:
    explicit cashierq() :
      app_owned("CASHIERQ"),
      randomizer(100, 200) {}

  protected:
    virtual void do_run(raii::shmem<util::shared_data> &shmem) override {
      log.debug("Constructing semaphores");
      raii::sem cashier_sem(shmem->sem_cashier, NAMES_SEM_CASHIER_CASHIER);
      raii::sem child_sem(shmem->sem_cashier, NAMES_SEM_CASHIER_CHILD);
      raii::sem money_sem(shmem->sem_cashier, NAMES_SEM_CASHIER_MONEY);
      raii::sem change_sem(shmem->sem_cashier, NAMES_SEM_CASHIER_CHANGE);

      log.debug("Opening cashierq fifo for reading");
      raii::fifo_reader<unsigned long> cashier_fifo(NAMES_CASHIERQ_FIFO);
      log.debug("Fifo opened");

      log.debug("Opening carrouselq fifo for writing");
      raii::fifo_writer<unsigned long> carrousel_fifo(NAMES_CARROUSELQ_FIFO);
      log.debug("Fifo opened. Starting arrival loop");

      while (!is_halted()) {
        try {
          log.debug("Reading a child id from the cashier queue");
          auto id = cashier_fifo.read();
          log.debug("Read child id $ from cashier queue", id);

          log.info("Child $ is waiting for the cashier to be available", id);
          cashier_sem.wait();

          log.debug("The cashier is mine. Writting child id.");
          shmem->cashier_child_id = id;

          log.debug("Child id provided, making it available");
          child_sem.signal();

          log.debug("Writing money to shared memory");
          shmem->cashier_child_money = randomizer.next();

          log.info("The child $ gives $ money to the cashier", id, shmem->cashier_child_money);
          money_sem.signal();

          log.info("The child $ is waiting for the change", id);
          change_sem.wait();
          log.info("The child $ received change $", id, shmem->cashier_child_change);

          log.info("Child $ is done with the cashier, going to the carrousel", id);
          cashier_sem.signal();

          log.debug("Writing child id $ to carrousel queue", id);
          carrousel_fifo.write(id);
        } catch (syscalls::interrupt &e) {
          log.debug("An interrupt occurred while blocked on system call: $", e.what());
        }
      }

      log.debug("Halt was set, terminating");
    }

  private:
    util::randomizer randomizer;
};

DEFINE_MAIN(cashierq);

