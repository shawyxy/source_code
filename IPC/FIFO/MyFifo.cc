#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

#define FILE_NAME "myfifo"
int main()
{
    umask(0);
    if(mkfifo(FILE_NAME, 0666) < 0) // 创建失败
    {
        perror("mkfifo");
        return 1;
    }

    return 0;
}
