#ifndef __UTIL__APP_OWNED_H_INCLUDED__
#define __UTIL__APP_OWNED_H_INCLUDED__

#include "util/app.h"
#include "util/shared_data.h"
#include "raii/shmem.h"
#include "raii/signal.h"
#include <unistd.h>

namespace util {
  class app_owned : public app {
    public:
      explicit app_owned(const std::string &name);

    protected:
      virtual void do_run();

      bool is_halted() const;

      virtual void do_run(raii::shmem<util::shared_data> &shmem) = 0;

    private:
      sig_atomic_t halt;
      TCLAP::ValueArg<int> shmemid;
      raii::signal sigint;
  };
}

#endif
