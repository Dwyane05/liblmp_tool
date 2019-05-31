#include "Singleton.h"
#include "CurrentThread.h"
#include "Thread.h"

#include <stdio.h>

class Test : lmp_tool::noncopyable
{
 public:
  Test()
  {
    printf("tid=%d, constructing %p\n", lmp_tool::CurrentThread::tid(), this);
  }

  ~Test()
  {
    printf("tid=%d, destructing %p %s\n", lmp_tool::CurrentThread::tid(), this, name_.c_str());
  }

  const lmp_tool::string& name() const { return name_; }
  void setName(const lmp_tool::string& n) { name_ = n; }

 private:
  lmp_tool::string name_;
};

class TestNoDestroy : lmp_tool::noncopyable
{
 public:
  // Tag member for Singleton<T>
  void no_destroy();

  TestNoDestroy()
  {
    printf("tid=%d, constructing TestNoDestroy %p\n", lmp_tool::CurrentThread::tid(), this);
  }

  ~TestNoDestroy()
  {
    printf("tid=%d, destructing TestNoDestroy %p\n", lmp_tool::CurrentThread::tid(), this);
  }
};

void threadFunc()
{
  printf("tid=%d, %p name=%s\n",
         lmp_tool::CurrentThread::tid(),
         &lmp_tool::Singleton<Test>::instance(),
         lmp_tool::Singleton<Test>::instance().name().c_str());
  lmp_tool::Singleton<Test>::instance().setName("only one, changed");
}

int main()
{
  lmp_tool::Singleton<Test>::instance().setName("only one");
  lmp_tool::Thread t1(threadFunc);
  t1.start();
  t1.join();
  printf("tid=%d, %p name=%s\n",
         lmp_tool::CurrentThread::tid(),
         &lmp_tool::Singleton<Test>::instance(),
         lmp_tool::Singleton<Test>::instance().name().c_str());
  lmp_tool::Singleton<TestNoDestroy>::instance();
  printf("with valgrind, you should see %zd-byte memory leak.\n", sizeof(TestNoDestroy));
}
