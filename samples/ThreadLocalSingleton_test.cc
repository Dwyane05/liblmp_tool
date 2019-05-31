#include "ThreadLocalSingleton.h"
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

void threadFunc(const char* changeTo)
{
  printf("tid=%d, %p name=%s\n",
         lmp_tool::CurrentThread::tid(),
         &lmp_tool::ThreadLocalSingleton<Test>::instance(),
         lmp_tool::ThreadLocalSingleton<Test>::instance().name().c_str());
  lmp_tool::ThreadLocalSingleton<Test>::instance().setName(changeTo);
  printf("tid=%d, %p name=%s\n",
         lmp_tool::CurrentThread::tid(),
         &lmp_tool::ThreadLocalSingleton<Test>::instance(),
         lmp_tool::ThreadLocalSingleton<Test>::instance().name().c_str());

  // no need to manually delete it
  // lmp_tool::ThreadLocalSingleton<Test>::destroy();
}

int main()
{
  lmp_tool::ThreadLocalSingleton<Test>::instance().setName("main one");
  lmp_tool::Thread t1(std::bind(threadFunc, "thread1"));
  lmp_tool::Thread t2(std::bind(threadFunc, "thread2"));
  t1.start();
  t2.start();
  t1.join();
  printf("tid=%d, %p name=%s\n",
         lmp_tool::CurrentThread::tid(),
         &lmp_tool::ThreadLocalSingleton<Test>::instance(),
         lmp_tool::ThreadLocalSingleton<Test>::instance().name().c_str());
  t2.join();

  pthread_exit(0);
}
