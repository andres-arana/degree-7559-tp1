#include "util/app_owned.h"

using namespace std;

class childinc : public util::app_owned {
  public:
    explicit childinc() :
      app_owned("CHILDINC"),
      child_id("c", "child", "Identifier for the child to simulate", true, 0, "int", args) {}

  protected:
    virtual void do_run(raii::shmem<util::shared_data> &shmem) override {
      auto id = child_id.getValue();

      log.info("Child $ is now running looking for a place to sit", id);
      // TODO: Find a place to sit
    }

  private:
    TCLAP::ValueArg<unsigned long> child_id;
};

DEFINE_MAIN(childinc);

