#include "Singleton.h"
#include "CurrentThread.h"
#include "ThreadLocal.h"
#include "Thread.h"

#include <stdio.h>
#include <unistd.h>

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

#define STL lmp_tool::Singleton<lmp_tool::ThreadLocal<Test> >::instance().value()

void print()
{
  printf("tid=%d, %p name=%s\n",
         lmp_tool::CurrentThread::tid(),
         &STL,
         STL.name().c_str());
}

void threadFunc(const char* changeTo)
{
  print();
  STL.setName(changeTo);
  sleep(1);
  print();
}

int main()
{
  STL.setName("main one");
  lmp_tool::Thread t1(std::bind(threadFunc, "thread1"));
  lmp_tool::Thread t2(std::bind(threadFunc, "thread2"));
  t1.start();
  t2.start();
  t1.join();
  print();
  t2.join();
  pthread_exit(0);
}
