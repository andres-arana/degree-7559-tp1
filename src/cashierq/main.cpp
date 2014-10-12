#include "util/app.h"
#include "util/names.h"
#include "raii/signal.h"
#include "raii/fifo_reader.h"
#include <unistd.h>

using namespace std;

class cashierq : public util::app {
  public:
    explicit cashierq() :
      app("CASHIERQ"),
      halt(0),
      sigint(SIGINT, [this]() { halt = 1; }) { }

  protected:
    virtual void do_run() override {
      log.debug("Opening cashierq fifo for reading");
      raii::fifo_reader<unsigned long> fifo(NAMES_CASHIERQ_FIFO);
      log.debug("Fifo opened, starting arrival loop");

      while (!halt) {
        log.debug("Reading a child id from the cashier queue");
        auto id = fifo.read();

        log.debug("Read child id $ from cashier queue", id);

        // TODO: Sincronize with cashier
      }

      log.debug("Halt was set, terminating");
    }

  private:
    sig_atomic_t halt;

    raii::signal sigint;
};

DEFINE_MAIN(cashierq);

