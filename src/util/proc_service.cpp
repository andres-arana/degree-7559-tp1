#include "util/proc_service.h"

using namespace util;
using namespace raii;
using namespace std;

proc_service::proc_service(
    const string &name,
    sync_log &log,
    shmem_owner<shared_data> &shmem)
  : proc(true, name, "-l", log.get_level(), "-m", shmem.id()) {

    log.debug("Started $ process with id $", name, pid());
  }
