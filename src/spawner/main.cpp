#include "util/auto_proc.h"
#include "util/app.h"
#include <vector>

using namespace util;
using namespace std;

class spawner : public util::app {
  public:
    explicit spawner() :
      app("spawner"),
      children("c", "children", "Amount of children", true, 0, "int", args) { }

  protected:
    virtual void do_run() override {
      log.info("I will spawn $ CHILD processes", children.getValue());

      vector<auto_proc> processes;

      for (int i = 0; i < children.getValue(); i++) {
        processes.emplace_back("build/exec/child");
        log.info("Launched CHILD process $", processes.back().pid());
      }

      log.info("All CHILD processes launched, waiting for termination");
    }

  private:
    TCLAP::ValueArg<int> children;
};

DEFINE_MAIN(spawner);
