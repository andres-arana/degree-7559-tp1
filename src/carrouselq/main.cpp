#include "util/app_owned.h"
#include "util/names.h"
#include "util/proc_childinc.h"
#include "raii/sem.h"
#include "raii/fifo_reader.h"
#include <vector>

using namespace std;

class carrouselq : public util::app_owned {
  public:
    explicit carrouselq() :
      app_owned("CARROUSELQ") {}

  protected:
    virtual void do_run(raii::shmem<util::shared_data> &shmem) override {
      log.debug("Opening carouselq fifo for reading");
      raii::fifo_reader<unsigned long> fifo(NAMES_CARROUSELQ_FIFO);
      log.debug("Fifo opened");

      log.debug("Constructing entrance semaphore");
      raii::sem entrance_sem(shmem->sem_carrousel_entrance, NAMES_SEM_CARROUSEL_ENTRANCE);

      while (!is_halted()) {
        log.debug("Trying to acquire entrance semaphore");
        entrance_sem.wait();
        log.info("The carrousel is now ready for children");

        {
          vector<util::proc_childinc> children;

          for (unsigned int i = 0; i < shmem->config_capacity; i++) {
            log.debug("Reading a child from the carrousel queue");
            auto id = fifo.read();
            log.info("Child $ went through the carrousel entrance", id);

            log.debug("Creating new childinc process for child $", id);
            children.emplace_back(log, shmem, id);
          }

          log.info("No more children can enter the carrousel, waiting for the next lap");
        }
      }
    }
};

DEFINE_MAIN(carrouselq);

