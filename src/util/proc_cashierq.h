#ifndef __UTIL__PROC_CASHIERQ__H_INCLUDED__
#define __UTIL__PROC_CASHIERQ__H_INCLUDED__

#include "raii/proc.h"
#include "util/sync_log.h"

namespace util {
  class proc_cashierq : public raii::proc {
    public:
      explicit proc_cashierq(util::sync_log &log);
  };
}

#endif
