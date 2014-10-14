#include "util/app_owned.h"
#include "util/names.h"

using namespace std;

class carrousel : public util::app_owned {
  public:
    explicit carrousel() :
      app_owned("CARROUSEL") {}

  protected:
    virtual void do_run(raii::shmem<util::shared_data> &shmem) override {
      log.debug("Starting check loop");

      while (!is_halted()) {
        // TODO: Implement carrousel process, simulated for now
        sleep(1);
      }

      log.debug("Halt was set, terminating");
    }
};

DEFINE_MAIN(carrousel);

