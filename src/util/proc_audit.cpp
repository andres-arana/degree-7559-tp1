#include "util/proc_audit.h"

using namespace util;

proc_audit::proc_audit(sync_log &log)
  : proc(true, "build/exec/audit", "-l", log.get_level()) {

    log.debug("Started AUDIT process with id $", pid());
  }
