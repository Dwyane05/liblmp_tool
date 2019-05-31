#include "GzipFile.h"

#include "Logging.h"

int main()
{
  const char* filename = "/tmp/gzipfile_test.gz";
  ::unlink(filename);
  const char data[] = "123456789012345678901234567890123456789012345678901234567890\n";
  {
  lmp_tool::GzipFile writer = lmp_tool::GzipFile::openForAppend(filename);
  if (writer.valid())
  {
    LOG_INFO << "tell " << writer.tell();
    LOG_INFO << "wrote " << writer.write(data);
    LOG_INFO << "tell " << writer.tell();
  }
  }

  {
  printf("testing reader\n");
  lmp_tool::GzipFile reader = lmp_tool::GzipFile::openForRead(filename);
  if (reader.valid())
  {
    char buf[256];
    LOG_INFO << "tell " << reader.tell();
    int nr = reader.read(buf, sizeof buf);
    printf("read %d\n", nr);
    if (nr >= 0)
    {
      buf[nr] = '\0';
      printf("data %s", buf);
    }
    LOG_INFO << "tell " << reader.tell();
    if (strncmp(buf, data, strlen(data)) != 0)
    {
      printf("failed!!!\n");
      abort();
    }
    else
    {
      printf("PASSED\n");
    }
  }
  }

  {
  lmp_tool::GzipFile writer = lmp_tool::GzipFile::openForWriteExclusive(filename);
  if (writer.valid() || errno != EEXIST)
  {
    printf("FAILED\n");
  }
  }
}
