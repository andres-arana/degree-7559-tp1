#include "util/app_owned.h"
#include "util/names.h"
#include "raii/sem.h"
#include "raii/file.h"
#include "raii/lock_write.h"

using namespace std;

class cashier : public util::app_owned {
  public:
    explicit cashier() :
      app_owned("CASHIER") {}

  protected:
    virtual void do_run(raii::shmem<util::shared_data> &shmem) override {
      log.debug("Constructing semaphores");
      raii::sem child_sem(shmem->sem_cashier, NAMES_SEM_CASHIER_CHILD);
      raii::sem money_sem(shmem->sem_cashier, NAMES_SEM_CASHIER_MONEY);
      raii::sem change_sem(shmem->sem_cashier, NAMES_SEM_CASHIER_CHANGE);

      log.debug("Opening balance file for locking");
      raii::file balance_file(NAMES_BALANCE_FILE, O_WRONLY);

      while (!is_halted()) {
        try {
          log.info("The cashier is waiting for the next child");
          child_sem.wait();
          log.info("The cashier is serving child $", shmem->cashier_child_id);

          log.info("The cashier is waiting for the child's money");
          money_sem.wait();
          log.info("The cashier received $ from the child $", shmem->cashier_child_money, shmem->cashier_child_id);

          log.info("The cashier needs to deposit the money for the child");

          {
            log.debug("Attempting to lock the balance file for writing");
            raii::lock_write lock(balance_file.fd());

            log.info("The cashier can deposit the money now, and fetches the change");
            shmem->balance += shmem->config_price;

            log.debug("Unlocking the balance file");
          }

          log.debug("Writting change to shared memory");
          shmem->cashier_child_change = shmem->cashier_child_money - shmem->config_price;

          log.info("The cashier is giving the child $ the change $", shmem->cashier_child_id, shmem->cashier_child_change);
          change_sem.signal();
        } catch (syscalls::interrupt &e) {
          log.debug("An interrupt occurred while blocked on system call: $", e.what());
        }
      }

      log.debug("Halt was set, terminating");
    }
};

DEFINE_MAIN(cashier);

