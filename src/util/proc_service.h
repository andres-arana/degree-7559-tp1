#ifndef __UTIL__PROC_SERVICE__H_INCLUDED__
#define __UTIL__PROC_SERVICE__H_INCLUDED__

#include "raii/proc.h"
#include "raii/shmem_owner.h"
#include "util/shared_data.h"
#include "util/sync_log.h"

namespace util {
  class proc_service : public raii::proc {
    public:
      explicit proc_service(
          const std::string &name,
          util::sync_log &log,
          raii::shmem_owner<util::shared_data> &shmem);
  };
}

#endif
