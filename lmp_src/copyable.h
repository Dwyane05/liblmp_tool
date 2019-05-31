/*
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the License file.
 *
 *  copyable.h
 *  Created on: May 30, 2019
 *  Author:     cuiyongfei
 */

#ifndef LMP_TOOL_COPYABLE_H
#define LMP_TOOL_COPYABLE_H

namespace lmp_tool
{

/// A tag class emphasises the objects are copyable.
/// The empty base class optimization applies.
/// Any derived class of copyable should be a value type.
class copyable
{
 protected:
  copyable() = default;
  ~copyable() = default;
};

}  // namespace lmp_tool

#endif  // LMP_TOOL_COPYABLE_H
