/*
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the License file.
 *
 *  CountDownLatch.h
 *  Created on: May 30, 2019
 *  Author:     cuiyongfei
 */

#ifndef LMP_TOOL_COUNTDOWNLATCH_H
#define LMP_TOOL_COUNTDOWNLATCH_H

#include "Condition.h"
#include "Mutex.h"

namespace lmp_tool
{

class CountDownLatch : noncopyable
{
 public:

  explicit CountDownLatch(int count);

  void wait();

  void countDown();

  int getCount() const;

 private:
  mutable MutexLock mutex_;
  Condition condition_ GUARDED_BY(mutex_);
  int count_ GUARDED_BY(mutex_);
};

}  // namespace lmp_tool
#endif  // LMP_TOOL_COUNTDOWNLATCH_H
