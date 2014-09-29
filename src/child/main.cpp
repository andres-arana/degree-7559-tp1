#include "util/app.h"

using namespace util;
using namespace std;

class child : public util::app {
  public:
    explicit child() :
      app("CHILD") { }

  protected:
    virtual void do_run() override {
      // TODO: Implement this
    }
};

DEFINE_MAIN(child);

