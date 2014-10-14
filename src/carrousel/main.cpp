#include "util/app_owned.h"
#include "util/names.h"
#include "raii/sem.h"
#include "raii/sem_set.h"
#include "raii/shmem_dyn.h"
#include "raii/fifo_reader.h"
#include <unistd.h>

using namespace std;

class carrousel : public util::app_owned {
  public:
    explicit carrousel() :
      app_owned("CARROUSEL") {}

  protected:
    virtual void do_run(raii::shmem<util::shared_data> &shmem) override {
      log.debug("Constructing semaphores");
      raii::sem entrance_sem(shmem->sem_carrousel_entrance, NAMES_SEM_CARROUSEL_ENTRANCE);
      raii::sem_set places_sem(shmem->sem_carrousel_places);
      raii::sem_set full_places_sem(shmem->sem_carrousel_full_places);

      log.debug("Attaching to carrousel places shared memory");
      raii::shmem_dyn<unsigned long> carrousel_places(shmem->shmem_carrousel_places);

      while (!is_halted()) {
        log.debug("Ensuring all places are full");
        for (unsigned int i = 0; i < shmem->config_capacity; i++) {
          log.debug("Ensuring place $ is full", i);
          full_places_sem.wait(i);
          log.debug("Place $ has a children $", i, carrousel_places[i]);
        }

        log.info("All children are on their places, starting carrousel lap");
        log.info("Children will have fun for $ seconds", shmem->config_duration);
        sleep(shmem->config_duration);

        log.info("Lap is over! All children are leaving their places");
        for (unsigned int i = 0; i < shmem->config_capacity; i++) {
          log.debug("Sending child $ to exit queue", carrousel_places[i]);
          // TODO: write to exitq

          log.debug("Releasing child $ from place $", carrousel_places[i], i);
          places_sem.signal(i);
        }

        log.info("All children left the carrousel, openingn carrousel entrance");
        entrance_sem.signal();
      }
    }
};

DEFINE_MAIN(carrousel);

