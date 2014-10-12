#include "util/proc_cashier.h"

using namespace util;

proc_cashier::proc_cashier(sync_log &log, int semid, int shmemid)
  : proc(true, "build/exec/cashier",
      "-l", log.get_level(),
      "-s", semid,
      "-m", shmemid) {

    log.debug("Started CASHIER process with id $", pid());
  }
