#include "ThreadPool.h"
#include "CountDownLatch.h"
#include "CurrentThread.h"
#include "Logging.h"

#include <stdio.h>
#include <unistd.h>  // usleep

void print()
{
  printf("tid=%d\n", lmp_tool::CurrentThread::tid());
}

void printString(const std::string& str)
{
  LOG_INFO << str;
  usleep(100*1000);
}

void test(int maxSize)
{
  LOG_WARN << "Test ThreadPool with max queue size = " << maxSize;
  lmp_tool::ThreadPool pool("MainThreadPool");
  pool.setMaxQueueSize(maxSize);
  pool.start(5);

  LOG_WARN << "Adding";
  pool.run(print);
  pool.run(print);
  for (int i = 0; i < 100; ++i)
  {
    char buf[32];
    snprintf(buf, sizeof buf, "task %d", i);
    pool.run(std::bind(printString, std::string(buf)));
  }
  LOG_WARN << "Done";

  lmp_tool::CountDownLatch latch(1);
  pool.run(std::bind(&lmp_tool::CountDownLatch::countDown, &latch));
  latch.wait();
  pool.stop();
}

/*
 * Wish we could do this in the future.
void testMove()
{
  lmp_tool::ThreadPool pool;
  pool.start(2);

  std::unique_ptr<int> x(new int(42));
  pool.run([y = std::move(x)]{ printf("%d: %d\n", lmp_tool::CurrentThread::tid(), *y); });
  pool.stop();
}
*/

int main()
{
  test(0);
  test(1);
  test(5);
  test(10);
  test(50);
}
