#include "util/app.h"

using namespace util;
using namespace std;

class audit : public util::app {
  public:
    explicit audit() :
      app("AUDIT") { }

  protected:
    virtual void do_run() override {
      // TODO: Implement this
    }
};

DEFINE_MAIN(audit);

