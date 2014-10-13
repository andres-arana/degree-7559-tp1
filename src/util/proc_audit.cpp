#include "util/proc_audit.h"

using namespace util;

proc_audit::proc_audit(sync_log &log, int shmemid)
  : proc(true, "build/exec/audit",
      "-l", log.get_level(), "-m", shmemid) {

    log.debug("Started AUDIT process with id $", pid());
  }
