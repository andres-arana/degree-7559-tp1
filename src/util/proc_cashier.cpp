#include "util/proc_cashier.h"

using namespace util;

proc_cashier::proc_cashier(sync_log &log, int semid, int shmemid, int price)
  : proc(true, "build/exec/cashier",
      "-l", log.get_level(),
      "-s", semid,
      "-m", shmemid,
      "-p", price) {

    log.debug("Started CASHIER process with id $", pid());
  }
