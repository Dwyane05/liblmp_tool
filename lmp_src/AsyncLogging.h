/*
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the License file.
 *
 *  AsyncLogging.h
 *  Created on: May 31, 2019
 *  Author:     cuiyongfei
 */

#ifndef LMP_TOOL_ASYNCLOGGING_H
#define LMP_TOOL_ASYNCLOGGING_H

#include "BlockingQueue.h"
#include "BoundedBlockingQueue.h"
#include "CountDownLatch.h"
#include "Mutex.h"
#include "Thread.h"
#include "LogStream.h"

#include <atomic>
#include <vector>

namespace lmp_tool
{

class AsyncLogging : noncopyable
{
 public:

  AsyncLogging(const string& basename,
               off_t rollSize,
               int flushInterval = 3);

  ~AsyncLogging()
  {
    if (running_)
    {
      stop();
    }
  }

  void append(const char* logline, int len);

  void start()
  {
    running_ = true;
    thread_.start();
    latch_.wait();
  }

  void stop() NO_THREAD_SAFETY_ANALYSIS
  {
    running_ = false;
    cond_.notify();
    thread_.join();
  }

 private:

  void threadFunc();

  typedef lmp_tool::detail::FixedBuffer<lmp_tool::detail::kLargeBuffer> Buffer;
  typedef std::vector<std::unique_ptr<Buffer>> BufferVector;
  typedef BufferVector::value_type BufferPtr;

  const int flushInterval_;
  std::atomic<bool> running_;
  const string basename_;
  const off_t rollSize_;
  lmp_tool::Thread thread_;
  lmp_tool::CountDownLatch latch_;
  lmp_tool::MutexLock mutex_;
  lmp_tool::Condition cond_ GUARDED_BY(mutex_);
  BufferPtr currentBuffer_ GUARDED_BY(mutex_);
  BufferPtr nextBuffer_ GUARDED_BY(mutex_);
  BufferVector buffers_ GUARDED_BY(mutex_);
};

}  // namespace lmp_tool

#endif  // LMP_TOOL_ASYNCLOGGING_H
