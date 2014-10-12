#ifndef __UTIL__PROC_AUDIT__H_INCLUDED__
#define __UTIL__PROC_AUDIT__H_INCLUDED__

#include "raii/proc.h"
#include "util/sync_log.h"

namespace util {
  class proc_audit : public raii::proc {
    public:
      explicit proc_audit(util::sync_log &log);
  };
}

#endif
