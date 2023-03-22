#include "comm.hpp"

static void GetMessage(int fd)
{
    char buffer[BUFF_SIZE];
    while(1)
    {
        memset(buffer, '\0', sizeof(buffer)); // 清空缓冲区

        ssize_t ret = read(fd, buffer, sizeof(buffer) - 1); // 读取数据
        if(ret > 0) 
        {
            cout <<"进程["  << getpid() << "]:"<< "来自客户端的消息：" << buffer << endl;
        }
        else if (ret == 0) // 读到文件结尾
        {
            cerr <<"进程["  << getpid() << "]：" << "读到文件结尾，客户端已退出，服务端退出。" << endl;
            break;
        }
        else // 读取错误
        {
            perror("read");
            break;
        }
    }
}
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
    // 3. 获取客户端数据
    GetMessage(fd);
    
    close(fd); // 关闭管道文件
    unlink(FILE_PATH); // 删除管道文件

    return 0;
}
