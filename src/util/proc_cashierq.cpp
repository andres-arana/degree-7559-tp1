#include "util/proc_cashierq.h"

using namespace util;

proc_cashierq::proc_cashierq(sync_log &log)
  : proc(true, "build/exec/cashierq", "-l", log.get_level()) {

    log.debug("Started CASHIERQ process with id $", pid());
  }
