#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"
#define MAXARGS 10
int main(int argc, char* argv[])
{
    // 保存可执行命令
    char* command[MAXARG];
    for (int i = 1; i < argc; i ++)
    {
        command[i - 1] = argv[i];
    }
    char buf[100];
    while (gets(buf, 100) && buf[0] != 0) //从标准输入中读取到一行
    {
        int argv_idx = argc - 1;
        //根据空格划分每个参数
        int len = strlen(buf), start_pos = 0;
        buf[len] = ' ';
        for (int i = 0; i <= len; i ++)
        {
            if (buf[i] == ' ')
            {
                if (i - start_pos > 1) //有效参数产生
                {
                    int argv_len = i - start_pos;
                    command[argv_idx] = (char*)malloc(sizeof(char) * argv_len);
                    memset(command[argv_idx], 0, sizeof(command[argv_idx]));
                    memcpy(command[argv_idx], buf + start_pos, argv_len - 1);
                    argv_idx ++;
                }
                start_pos = i + 1;
            }
        }
        if (fork() == 0)
        {
            //将char *[10]强转为char **和exec参数类型匹配
            exec(command[0], command); //exec的参数是这样不 comand数组最后一个字符串是不是空串
            for (int i = argc; i < argv_idx; i ++)
            {
                free(command[i]);
            }
            exit(0);
        }
        wait(0);
    }
    exit(0);
}