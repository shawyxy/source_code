#include "comm.hpp"

int main()
{
    // 1. 获取管道文件
    int fd = open(FILE_PATH, O_WRONLY);
    if(fd < 0)
    {
        perror("open");
        exit(1);
    }

    // 2. 通信逻辑
    string buffer;
    while(true)
    {
        cout << "请键入信息 >> ";
        getline(cin, buffer);
        write(fd, buffer.c_str(), buffer.size());
    }

    // 3. 关闭文件
    close(fd);

    return 0;
}