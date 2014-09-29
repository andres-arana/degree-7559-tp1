#include "util/app.h"

using namespace util;
using namespace std;

class cashier : public util::app {
  public:
    explicit cashier() :
      app("CASHIER") { }

  protected:
    virtual void do_run() override {

    }
};

DEFINE_MAIN(cashier);

