#include "util/app_owned.h"
#include "util/randomizer.h"
#include "raii/sem_set.h"
#include <vector>
#include <numeric>

using namespace std;

class childinc : public util::app_owned {
  public:
    explicit childinc() :
      app_owned("CHILDINC"),
      child_id("c", "child", "Identifier for the child to simulate", true, 0, "int", args) {}

  protected:
    virtual void do_run(raii::shmem<util::shared_data> &shmem) override {
      auto id = child_id.getValue();

      log.debug("Initializing random seed");
      util::randomizer randomizer(0, 100);

      log.debug("Constructing semaphores");
      raii::sem_set places_sem(shmem->sem_carrousel_places);

      log.info("Child $ is now running looking for a place to sit", id);
      vector<unsigned int> places(shmem->config_capacity);
      iota(places.begin(), places.end(), 0);
      random_shuffle(places.begin(), places.end());

      auto chosen_place = find_place(id, places, places_sem);
      log.info("Child $ sat down on place $", id, chosen_place);

      // TODO: Send child to carrousel
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
    }
};

DEFINE_MAIN(childinc);

