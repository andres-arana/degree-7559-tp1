#include "util/proc_childinc.h"

using namespace util;
using namespace raii;
using namespace std;

proc_childinc::proc_childinc(
    sync_log &log,
    shmem<shared_data> &shmem,
    unsigned long childid)
  : proc(false, "build/exec/childinc",
      "-l", log.get_level(), "-m", shmem.id(), "-c", childid) {

    log.debug("Started build/exec/childinc process with id $", pid());
  }
