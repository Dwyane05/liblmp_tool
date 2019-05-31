/*
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the License file.
 *
 *  CurrentThread.h
 *  Created on: May 30, 2019
 *  Author:     cuiyongfei
 */

#ifndef LMP_TOOL_CURRENTTHREAD_H
#define LMP_TOOL_CURRENTTHREAD_H

#include "Common.h"

namespace lmp_tool
{
namespace CurrentThread
{
  // internal
  extern __thread int t_cachedTid;
  extern __thread char t_tidString[32];
  extern __thread int t_tidStringLength;
  extern __thread const char* t_threadName;
  void cacheTid();

  inline int tid()
  {
    if (__builtin_expect(t_cachedTid == 0, 0))
    {
      cacheTid();
    }
    return t_cachedTid;
  }

  inline const char* tidString() // for logging
  {
    return t_tidString;
  }

  inline int tidStringLength() // for logging
  {
    return t_tidStringLength;
  }

  inline const char* name()
  {
    return t_threadName;
  }

  bool isMainThread();

  void sleepUsec(int64_t usec);  // for testing

  string stackTrace(bool demangle);
}  // namespace CurrentThread
}  // namespace lmp_tool

#endif  // LMP_TOOL_CURRENTTHREAD_H
