#include "comm.hpp"

int main()
{
    // 1 .创建命名管道文件
    if(mkfifo(FILE_PATH, MODE) < 0) // 创建失败
    {
        perror("mkfifo");
        exit(1);
    }
    // 2. 以只读的方式打开管道文件
    int fd = open(FILE_PATH, O_RDONLY);
    if(fd < 0)
    {
        perror("open"); // 打开失败
        exit(2);
    }
    // 3. 不读取数据
    while(1){}
    
    close(fd); // 关闭管道文件
    unlink(FILE_PATH); // 删除管道文件

    return 0;
}
