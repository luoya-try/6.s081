#include "kernel/types.h"
#include "user/user.h"
int main(int argc, char *argv[]){
    int p_child_to_parent[2];
    int p_parent_to_child[2];
    //0: read 1: write
    pipe(p_child_to_parent);
    pipe(p_parent_to_child);
    if(fork() == 0){ //child process
        printf("%d: received ping\n", getpid());
        char ch;
        close(p_parent_to_child[1]);
        close(p_child_to_parent[0]);
        read(p_parent_to_child[0], &ch, 1);
        close(p_parent_to_child[0]);
        write(p_child_to_parent[1], &ch, 1);
        close(p_child_to_parent[1]);
        exit(0);
    } else{
        char ch = 'z';
        close(p_child_to_parent[1]);
        close(p_parent_to_child[0]);
        write(p_parent_to_child[1], &ch, 1);
        close(p_parent_to_child[1]);
        wait(0);
        read(p_child_to_parent[0], &ch, 1);
        close(p_child_to_parent[0]);
        printf("%d: received pong\n", getpid());
    }
    exit(0);
}