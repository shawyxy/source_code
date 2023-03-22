#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

int main()
{
    // 1. 创建管道
    int pipefd[2] = { 0 };
    int n = pipe(pipefd);
    assert(n != -1); (void)n; // debug && release assert
#ifdef DEBUG
    cout << "pipefd[0]: " << pipefd[0] << endl; // 3
    cout << "pipefd[1]: " << pipefd[1] << endl; // 4
#endif
    // 2. 创建子进程

    pid_t id = fork();
    assert(id != -1);
    if(id == 0) // 子进程
    {
        // 2.1 子进程读取，关闭写端
        close(pipefd[1]);
        char get_buffer[1024];
        while(1)
        {
            // sleep(5);
            ssize_t ret = read(pipefd[0], get_buffer, sizeof(get_buffer) - 1); // 注意长度忽略了'\0'
            if (ret > 0) // 返回值>0，表示读取到字符串的长度
            {
                get_buffer[ret] = 0;
                cout << "Child get a message[" << getpid() << "] from Father# " << get_buffer << endl;
            }
            else if(ret == 0) // 返回值=0，表示写数据的一方终止
            {
                cout << "Father stoped writing, child exits" << endl;
                break;
            }
        }
        exit(0);
    }
    // 父进程
    // 3.1 父进程写入，关闭读端
    close(pipefd[0]);
    string message = "I am Father and I am sending you a message!";
    int count = 0;
    char send_buffer[1024 * 4];
    while (1)
    {
        // 3.2 构建一个变化的字符串
        snprintf(send_buffer, sizeof(send_buffer), "%s[%d] : %d", message.c_str(), getpid(), count++);
        // 3.3 写入
        write(pipefd[1], send_buffer, strlen(send_buffer));
        // 3.3 sleep(1)
        sleep(1);
        if (count == 10)
            break;
        cout << count << endl;
    }
    close(pipefd[1]); // 关闭文件
    pid_t ret = waitpid(id, nullptr, 0); // 回收子进程资源
    cout << "id : " << id << " ret: " << ret <<endl;
    assert(ret > 0); 
    (void)ret;
    return 0;
}
