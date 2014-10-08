#include "util/util.h"
#include "raii/raii.h"
#include <vector>

using namespace std;

class spawner : public util::app {
  public:
    explicit spawner() :
      app("SPAWNER"),
      children("c", "children", "Amount of children", true, 0, "int", args) { }

  protected:
    virtual void do_run() override {
      log.debug("I will spawn $ CHILD processes", children.getValue());

      auto log_level = configured_log_level();

      vector<raii::auto_proc> processes;

      for (int i = 0; i < children.getValue(); i++) {
        processes.emplace_back(false, "build/exec/child", "-l", log_level);
        log.debug("Launched CHILD process $", processes.back().pid());
      }

      log.debug("All CHILD processes launched, waiting for termination");
    }

  private:
    TCLAP::ValueArg<int> children;
};

DEFINE_MAIN(spawner);
