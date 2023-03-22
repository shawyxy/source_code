#ifndef _COMM_H_
#define _COMM_H_

#include <iostream>
#include <cstdio>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <cstring>
#include <cstdlib>
using namespace std;

#define FILE_PATH "./myfifo" // 文件路径
#define MODE 0666            // 文件权限
#define BUFF_SIZE 1024       // 缓冲区大小
#define CHILD_NUM 3          // mutiServer子进程数量

#endif