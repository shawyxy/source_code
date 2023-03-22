#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <fcntl.h>

using namespace std;

#define PATH_NAME "./tmp.cc"   // 文件路径
#define PROJ_ID 0x666          // 标识符
#define SHM_SIZE 4096          // 共享内存大小
#define FIFO_NAME "./fifotest" // 管道文件名
int OpenFifo(const char *pathname, int flags)
{
    int fd = open(pathname, flags);
    assert(fd >= 0);
    return fd;
}
// 等待
void Wait(int fd)
{
    uint32_t temp = 0;
    ssize_t ret = read(fd, &temp, sizeof(uint32_t));
    assert(ret == sizeof(uint32_t));
    (void)ret;
}
// 唤醒
void Wakeup(int fd)
{
    uint32_t temp = 1;
    ssize_t ret = write(fd, &temp, sizeof(uint32_t));
    assert(ret == sizeof(uint32_t));
    (void)ret;
}

void CloseFifo(int fd)
{
    close(fd);
}

class Init
{
public:
    Init()
    {
        umask(0);
        int n = mkfifo(FIFO_NAME, 0666);
        assert(n == 0);
        (void)n;
    }
    ~Init()
    {
        unlink(FIFO_NAME);
    }
};