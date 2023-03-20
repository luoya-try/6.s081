#include "kernel/types.h"
#include "user/user.h"
int main(int argc, char *argv[]){
    int p[2];
    //0: read 1: write
    pipe(p);
    if(fork() == 0){ //child process
        printf("%d: received ping\n", getpid());
        char ch;
        read(p[0], &ch, 1);
        close(p[0]);
        write(p[1], &ch, 1);
        close(p[1]);
        exit(0);
    } else{
        char ch = 'z';
        write(p[1], &ch, 1);
        close(p[1]);
        wait(0);
        
        read(p[0], &ch, 1);
        close(p[0]);
        printf("%d: received pong\n", getpid());
    }
    exit(0);
}