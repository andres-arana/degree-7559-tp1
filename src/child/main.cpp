#include "util/app.h"
#include <unistd.h>

using namespace std;

class child : public util::app {
  public:
    explicit child() :
      app("CHILD") { }

  protected:
    virtual void do_run() override {
      log.info("A new child has arrived!");
      sleep(5);
      log.info("The child is leaving");
    }
};

DEFINE_MAIN(child);

