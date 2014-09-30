#include "util/app.h"
#include <unistd.h>

using namespace util;
using namespace std;

class child : public util::app {
  public:
    explicit child() :
      app("CHILD") { }

  protected:
    virtual void do_run() override {
      sleep(5);
    }
};

DEFINE_MAIN(child);

