#include "util/app.h"
#include "util/names.h"
#include "util/shared_data.h"
#include "util/randomizer.h"
#include "raii/signal.h"
#include "raii/shmem.h"
#include "raii/file.h"
#include "raii/lock_read.h"
#include <unistd.h>

using namespace std;

class audit : public util::app {
  public:
    explicit audit() :
      app("AUDIT"),
      halt(0),
      shmemid("m", "memory", "Shared memory id", true, 0, "int", args),
      randomizer(3, 5),
      sigint(SIGINT, [this]() { halt = 1; }) { }

  protected:
    virtual void do_run() override {
      log.debug("Attaching shared memory");
      raii::shmem<util::shared_data> shmem(shmemid.getValue());

      log.debug("Opening balance file for locking");
      raii::file balance_file(NAMES_BALANCE_FILE, O_RDONLY);

      while (!halt) {
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
    sig_atomic_t halt;
    TCLAP::ValueArg<int> shmemid;
    util::randomizer randomizer;

    raii::signal sigint;
};

DEFINE_MAIN(audit);

