#ifndef __UTIL__PROC_CASHIER__H_INCLUDED__
#define __UTIL__PROC_CASHIER__H_INCLUDED__

#include "raii/proc.h"
#include "util/sync_log.h"

namespace util {
  class proc_cashier : public raii::proc {
    public:
      explicit proc_cashier(util::sync_log &log);
  };
}

#endif
