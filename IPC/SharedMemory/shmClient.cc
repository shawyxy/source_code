#include "comm.hpp"

int main()
{
    // 1. 获取公共key值
    key_t key = ftok(PATH_NAME, PROJ_ID);
    if (key < 0)
    {
        perror("ftok");
        exit(1);
    }
    // 2. 「获取」共享内存
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT); 
    if (shmid < 0)
    {
        perror("shmget");
        exit(2);
    }
    // 3. 将共享内存挂接到进程的地址空间
    char *shmaddr = (char *)shmat(shmid, nullptr, 0);
    if (shmaddr == nullptr)
    {
        perror("shmat");
        exit(3);
    }
    // 4. 进程间通信逻辑
    // 4.1 打开文件
    int fd = OpenFifo(FIFO_NAME, O_WRONLY);

    while(1)
    {
        ssize_t ret = read(0, shmaddr, SHM_SIZE - 1);
        if(ret > 0)
        {
            shmaddr[ret - 1] = 0;
            Wakeup(fd);
            if(strcmp(shmaddr, "quit") == 0) 
                break;
        }
        //sleep(1);
    }
    // 5. 将进程地址空间和共享内存去关联
    int n = shmdt(shmaddr);
    if(n == -1)
    {
        perror("shmdt");
        exit(4);
    }
    // 6. Client端不需要释放共享内存，但要关闭文件
    CloseFifo(fd);

    return 0;
}
