#ifndef __UTIL__PROC_CHILDINC__H_INCLUDED__
#define __UTIL__PROC_CHILDINC__H_INCLUDED__

#include "raii/proc.h"
#include "raii/shmem.h"
#include "util/shared_data.h"
#include "util/sync_log.h"

namespace util {
  class proc_childinc : public raii::proc {
    public:
      explicit proc_childinc(
          util::sync_log &log,
          raii::shmem<util::shared_data> &shmem,
          unsigned long childid);
  };
}

#endif
