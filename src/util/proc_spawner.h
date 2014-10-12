#ifndef __UTIL__PROC_SPAWNER__H_INCLUDED__
#define __UTIL__PROC_SPAWNER__H_INCLUDED__

#include "raii/proc.h"
#include "util/sync_log.h"

namespace util {
  class proc_spawner : public raii::proc {
    public:
      explicit proc_spawner(util::sync_log &log);
  };
}

#endif
