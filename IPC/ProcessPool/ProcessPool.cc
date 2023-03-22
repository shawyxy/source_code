#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "Method.hpp"
using namespace std;

#define PROCESS_NUM 3


void SendAndWakeup(pid_t who, int fd, uint32_t command) // 父进程发送命令
{
    write(fd, &command, sizeof(command));
    cout << "main process: call process " << who << " to execute " << desc[command] << " command through " << fd << endl;
}

ssize_t WaitCommand(int fd, bool &quit) // 子进程获取命令
{
    uint32_t command = 0;
    ssize_t ret = read(fd, &command, sizeof(command));
    if (ret == 0) // 读取失败
    {
        quit = true;
        return (int)-1;
    }
    assert(ret == sizeof(uint32_t));
    return command;
}

int main()
{
    load(); // 加载指令对应方法
    vector<pair<pid_t, int>> slots; // 定义记录子进程信息的容器
    // 创建多个子进程
    for(int i = 0; i < PROCESS_NUM; i++)
    {
        // 父进程为每个子进程创建管道
        int pipefd[2] = { 0 };
        int ret = pipe(pipefd);
        assert(ret == 0);
        (void)ret;

        pid_t id = fork();
        assert(id != -1);

        if(id == 0) // 子进程读取
        {
            close(pipefd[1]); // 关闭写端
            while(1) // 等待命令
            {
                // 处理命令的逻辑
                bool quit = false;
                ssize_t command = WaitCommand(pipefd[0], quit);
                if(quit) // 匿名管道里没有指令，子进程转换为阻塞状态
                    break;
                // 获取到指令
                if(command >= 0 && command < MethodNum()) // 检查指令格式
                {
                    MethodList[command](); // 调用command编号对应函数
                } 
                else // 指令格式错误
                {
                    cout << "command not found" << endl; // 打印提示信息
                }
            }
            exit(1);
        }
        // 父进程写入
        close(pipefd[0]); // 关闭读端
        slots.push_back(pair<pid_t, int>(id, pipefd[1])); // 记录子进程信息
    }
    // 父进程的逻辑
    srand((unsigned long)time(nullptr) ^ getpid() ^ 99997837); // 让种子更随机
    while(1) // 发送命令的逻辑
    {
        uint32_t command = rand() % MethodNum(); // 随机获取一个命令
        int ChildNum = rand() % slots.size(); // 随机得到一个进程在日志表中的编号
        SendAndWakeup(slots[ChildNum].first, slots[ChildNum].second, command); // 将任务指派给进程
        sleep(1); // 慢一点指派，观察现象
    }

    // 关闭所有子进程的文件描述符，使之退出
    for (const auto &slot : slots)
    {
        close(slot.second);
    }

    // 回收所有子进程的资源
    for (const auto &slot : slots)
    {
        waitpid(slot.first, nullptr, 0);
    }

    return 0;
}
