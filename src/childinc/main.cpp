#include "util/app_owned.h"
#include "util/names.h"
#include "util/randomizer.h"
#include "raii/sem_set.h"
#include "raii/shmem_dyn.h"
#include <vector>
#include <numeric>
#include <stdexcept>

using namespace std;

class childinc : public util::app_owned {
  public:
    explicit childinc() :
      app_owned("CHILDINC"),
      child_id("c", "child", "Identifier for the child to simulate", true, 0, "int", args) {}

  protected:
    virtual void do_run(raii::shmem<util::shared_data> &shmem) override {
      try {
        auto id = child_id.getValue();

        log.debug("Initializing random seed");
        util::randomizer randomizer(0, 100);

        log.debug("Constructing semaphores");
        raii::sem_set places_sem(shmem->sem_carrousel_places);
        raii::sem_set full_places_sem(shmem->sem_carrousel_full_places);

        log.debug("Attaching to carrousel places shared memory");
        raii::shmem_dyn<unsigned long> carrousel_places(shmem->shmem_carrousel_places);

        log.info("Child $ is now running looking for a place to sit", id);
        vector<unsigned int> places(shmem->config_capacity);
        iota(places.begin(), places.end(), 0);
        random_shuffle(places.begin(), places.end());

        auto chosen_place = find_place(id, places, places_sem);
        log.info("Child $ sat down on place $", id, chosen_place);
        carrousel_places[chosen_place] = id;
        full_places_sem.signal(chosen_place);
      } catch (syscalls::interrupt &e) {
          log.debug("An interrupt occurred while blocked on system call: $", e.what());
      }
    }

  private:
    TCLAP::ValueArg<unsigned long> child_id;

    unsigned int find_place(
        int child_id,
        const vector<unsigned int> &preferences,
        raii::sem_set &places_sem) {

      for (auto place : preferences) {
        if (places_sem.try_wait(place)) {
          return place;
        } else {
          log.info("Child $ tried to sit on place $, but was already occupied", child_id, place);
        }
      }

      throw runtime_error("Unable to find a place to sit for a child!");
    }
};

DEFINE_MAIN(childinc);

