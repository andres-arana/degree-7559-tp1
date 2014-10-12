#ifndef __UTIL__PROC_CARROUSEL__H_INCLUDED__
#define __UTIL__PROC_CARROUSEL__H_INCLUDED__

#include "raii/proc.h"
#include "util/sync_log.h"

namespace util {
  class proc_carrousel : public raii::proc {
    public:
      explicit proc_carrousel(util::sync_log &log);
  };
}

#endif
