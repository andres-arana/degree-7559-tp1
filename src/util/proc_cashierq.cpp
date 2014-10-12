#include "util/proc_cashierq.h"

using namespace util;

proc_cashierq::proc_cashierq(sync_log &log, int semid, int shmemid)
  : proc(true, "build/exec/cashierq",
      "-l", log.get_level(),
      "-s", semid, "-m", shmemid) {

    log.debug("Started CASHIERQ process with id $", pid());
  }
