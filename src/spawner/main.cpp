#include "util/app.h"
#include "util/names.h"
#include "util/randomizer.h"
#include "raii/signal.h"
#include "raii/fifo_writer.h"
#include <unistd.h>
#include <cstdlib>
#include <time.h>

using namespace std;

class spawner : public util::app {
  public:
    explicit spawner() :
      app("SPAWNER"),
      halt(0),
      randomizer(1, 3),
      sigint(SIGINT, [this]() { halt = 1; }) { }

  protected:
    virtual void do_run() override {
      unsigned long child_id = 0;

      log.debug("Opening cashierq fifo for writing");
      raii::fifo_writer<unsigned long> fifo(NAMES_CASHIERQ_FIFO);
      log.debug("Fifo opened, starting arrival loop");

      while (!halt) {
        log.debug("A new child was spawned with id $", child_id);
        log.info("A new child with id $ has arrived!", child_id);

        log.info("Child $ is getting into the cashier queue", child_id);
        log.debug("Writing child id $ to the cashierq FIFO", child_id);
        fifo.write(child_id);
        log.debug("Child id $ written to cashierq FIFO", child_id);

        log.debug("Increasing child id");
        child_id++;

        sleep(randomizer.next());
      }

      log.debug("Halt was set, terminating");
    }

  private:
    sig_atomic_t halt;
    util::randomizer randomizer;
    raii::signal sigint;
};

DEFINE_MAIN(spawner);

