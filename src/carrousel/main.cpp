#include "util/app.h"

using namespace util;
using namespace std;

class carrousel : public util::app {
  public:
    explicit carrousel() :
      app("CARROUSEL") { }

  protected:
    virtual void do_run() override {

    }
};

DEFINE_MAIN(carrousel);

