#include "ProcessInfo.h"
#include <stdio.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

int main()
{
  printf("pid = %d\n", lmp_tool::ProcessInfo::pid());
  printf("uid = %d\n", lmp_tool::ProcessInfo::uid());
  printf("euid = %d\n", lmp_tool::ProcessInfo::euid());
  printf("start time = %s\n", lmp_tool::ProcessInfo::startTime().toFormattedString().c_str());
  printf("hostname = %s\n", lmp_tool::ProcessInfo::hostname().c_str());
  printf("opened files = %d\n", lmp_tool::ProcessInfo::openedFiles());
  printf("threads = %zd\n", lmp_tool::ProcessInfo::threads().size());
  printf("num threads = %d\n", lmp_tool::ProcessInfo::numThreads());
  printf("status = %s\n", lmp_tool::ProcessInfo::procStatus().c_str());
}
