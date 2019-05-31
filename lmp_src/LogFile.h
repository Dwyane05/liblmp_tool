/*
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the License file.
 *
 *  LogFile.h
 *  Created on: May 31, 2019
 *  Author:     cuiyongfei
 */

#ifndef LMP_TOOL_LOGFILE_H
#define LMP_TOOL_LOGFILE_H

#include "Mutex.h"
#include "Common.h"

#include <memory>

namespace lmp_tool
{

namespace FileUtil
{
class AppendFile;
}

class LogFile : noncopyable
{
 public:
  LogFile(const string& basename,
          off_t rollSize,
          bool threadSafe = true,
          int flushInterval = 3,
          int checkEveryN = 1024);
  ~LogFile();

  void append(const char* logline, int len);
  void flush();
  bool rollFile();

 private:
  void append_unlocked(const char* logline, int len);

  static string getLogFileName(const string& basename, time_t* now);

  const string basename_;
  const off_t rollSize_;
  const int flushInterval_;
  const int checkEveryN_;

  int count_;

  std::unique_ptr<MutexLock> mutex_;
  time_t startOfPeriod_;
  time_t lastRoll_;
  time_t lastFlush_;
  std::unique_ptr<FileUtil::AppendFile> file_;

  const static int kRollPerSeconds_ = 60*60*24;
};

}  // namespace lmp_tool
#endif  // LMP_TOOL_LOGFILE_H
