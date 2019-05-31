/*
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the License file.
 *
 *  Exception.h
 *  Created on: May 30, 2019
 *  Author:     cuiyongfei
 */

#ifndef LMP_TOOL_EXCEPTION_H
#define LMP_TOOL_EXCEPTION_H

#include "Common.h"
#include <exception>

namespace lmp_tool
{

class Exception : public std::exception
{
 public:
  Exception(string what);
  ~Exception() noexcept override = default;

  // default copy-ctor and operator= are okay.

  const char* what() const noexcept override
  {
    return message_.c_str();
  }

  const char* stackTrace() const noexcept
  {
    return stack_.c_str();
  }

 private:
  string message_;
  string stack_;
};

}  // namespace lmp_tool

#endif  // LMP_TOOL_EXCEPTION_H
