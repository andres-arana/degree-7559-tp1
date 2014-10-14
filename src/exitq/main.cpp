#include "util/app_owned.h"
#include "util/names.h"
#include "raii/fifo_reader.h"

using namespace std;

class exitq : public util::app_owned {
  public:
    explicit exitq() :
      app_owned("EXITQ") {}

  protected:
    virtual void do_run(raii::shmem<util::shared_data> &shmem) override {
      (void)shmem;

      log.debug("Opening exitq fifo for reading");
      raii::fifo_reader<unsigned long> fifo(NAMES_EXITQ_FIFO);
      log.debug("Fifo opened");

      while (!is_halted()) {
        log.debug("Reading child from exitq fifo");
        auto child_id = fifo.read();

        log.info("Child $ has left the carrousel", child_id);
      }
    }
};

DEFINE_MAIN(exitq);

