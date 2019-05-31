/*
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the License file.
 *
 *  noncopyable.h
 *  Created on: May 30, 2019
 *  Author:     cuiyongfei
 */

#ifndef LMP_TOOL_NONCOPYABLE_H
#define LMP_TOOL_NONCOPYABLE_H

namespace lmp_tool
{

class noncopyable
{
 public:
  noncopyable(const noncopyable&) = delete;
  void operator=(const noncopyable&) = delete;

 protected:
  noncopyable() = default;
  ~noncopyable() = default;
};

}  // namespace lmp_tool

#endif  // LMP_TOOL_NONCOPYABLE_H
