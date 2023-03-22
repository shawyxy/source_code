#include "comm.hpp"

// 0. 创建全局对象
Init init; 

int main()
{
    // 1. 获取公共key值
    key_t key = ftok(PATH_NAME, PROJ_ID);
    if (key < 0)        
    {
        perror("ftok");
        exit(1);
    }
    // 2. 申请共享内存
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | IPC_EXCL | 0666);
    if (shmid < 0)
    {
        perror("shmget");
        exit(2);
    }
    // 3. 将共享内存挂接到进程的地址空间
    char *shmaddr = (char *)shmat(shmid, nullptr, 0);
    if (shmaddr == (void *)-1)
    {
        perror("shmat");
        exit(3);
    }

    // 4. 打开文件
    int fd = OpenFifo(FIFO_NAME, O_RDONLY);
    // 进程间通信逻辑
    while(1)
    {
        // 4.2 读取
        Wait(fd);
        printf("%s\n", shmaddr);
        if(strcmp(shmaddr, "quit") == 0) 
            break;
        //sleep(1);
    }
    // 5. 去关联
    int n = shmdt(shmaddr);
    if(n == -1)
    {
        perror("shmdt");
        exit(4);
    }
    // 6. 释放共享内存
    shmctl(shmid, IPC_RMID, NULL);
    // 7. 关闭文件
    CloseFifo(fd);

    return 0;
}
