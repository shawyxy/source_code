#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>//注意memset的头文件
#define NUM 1024    //定义缓冲区的长度
#define SIZE 32
#define SEP " "     //定义" "为拆散字符串的分隔符
char cmd_line[NUM];  //定义缓冲区字符数组，保存输入的命令行字符串
char *g_argv[SIZE];  //保存拆散后的命令行字符串


int main()
{
	//0. 用死循环让程序常驻内存
	while(1)
	{
		//1. 打印提示信息
		printf("[root@localhost myshell]# ");//随便写的
		fflush(stdout);//将上面的字符串刷新到屏幕
		memset(cmd_line, '\0', sizeof(cmd_line));
		//2. 获取键入信息
		//输入"ls -a -l"
		if(fgets(cmd_line, sizeof(cmd_line), stdin) == NULL)
		{
			continue;
		}
		cmd_line[strlen(cmd_line) - 1] = '\0';//除去\n
		printf("echo:%s\n", cmd_line);
		//3. 解析命令
		g_argv[0] = strtok(cmd_line, SEP);//strtok第一次要传入字符串地址
		int index = 1;
		if(strcmp(g_argv[0], "ls") == 0)
		{
		    g_argv[index++] = "--color=auto";
		}
		if(strcmp(g_argv[0], "ll") == 0)
		{
		    g_argv[0] = "ls";
		    g_argv[index++] = "-l";
		    g_argv[index++] = "--color=auto";
		}
		while(g_argv[index++] = strtok(NULL, SEP));//传入NULL，表示继续分割
		// 测试是否解析成功
		// for(int i = 0; g_argv[i]; i++)
		// {
		// 	printf("g_argv[%d]:%s\n", i, g_argv[i]);
		// }
		
		//5. 创建子进程 
		pid_t id = fork();
		if(id == 0)//子进程
		{
			//printf("子进程开始运行：\n");
			execvp(g_argv[0], g_argv);// 6. 程序替换
			exit(1);
		}
		else//父进程
		{
			int status = 0;
			pid_t ret = waitpid(id, &status, 0);//7. 等待子进程退出
			// if(ret > 0)//退出成功，返回子进程pid
			// {
			// 	printf("退出码：%d\n", WEXITSTATUS(status));
			// }
			//4. TODO，内置指令
			if(strcmp(g_argv[0], "cd") == 0) 
			{
			    if(g_argv[1] != NULL) chdir(g_argv[1]); //cd path, cd ..

			    continue;
			}
		}
	}

	return 0;
}
