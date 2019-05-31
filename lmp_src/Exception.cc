/*
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the License file.
 *
 *  Exception.cc
 *  Created on: May 30, 2019
 *  Author:     cuiyongfei
 */

#include "Exception.h"
#include "CurrentThread.h"

namespace lmp_tool
{

Exception::Exception(string msg)
  : message_(std::move(msg)),
    stack_(CurrentThread::stackTrace(/*demangle=*/false))
{
}

}  // namespace lmp_tool
