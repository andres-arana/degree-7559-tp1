#include "util/app_owned.h"
#include "util/names.h"
#include "util/randomizer.h"
#include "raii/file.h"
#include "raii/lock_read.h"

using namespace std;

class audit : public util::app_owned {
  public:
    explicit audit() :
      app_owned("AUDIT"),
      randomizer(3, 5) {}

  protected:
    virtual void do_run(raii::shmem<util::shared_data> &shmem) override {
      log.debug("Opening balance file for locking");
      raii::file balance_file(NAMES_BALANCE_FILE, O_RDONLY);

      while (!is_halted()) {
        auto sleep_time = randomizer.next();
        log.info("The auditor is going to come back in about $ seconds", sleep_time);
        sleep(sleep_time);

        log.info("The auditor has come back. He needs to check the balance");

        {
          log.debug("Attempting to lock the balance file for reading");
          raii::lock_read lock(balance_file.fd());

          log.info("The auditor now checks the balance, taking a bit of time");
          sleep(randomizer.next());

          log.info("The auditor has checked and the balance is $", shmem->balance);

          log.debug("Unlocking the balance file");
        }

        log.info("The cashier has finished his round");
      }

      log.debug("Halt was set, terminating");
    }

  private:
    util::randomizer randomizer;

};

DEFINE_MAIN(audit);

