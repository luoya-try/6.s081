#include "kernel/types.h"
#include "user/user.h"
void get_primes(int *from_pipe){
    int num, cur_prime;
    close(from_pipe[1]);
    if(read(from_pipe[0], &cur_prime, 4) == 0) return;
    printf("prime %d\n", cur_prime);
    int to_pipe[2];
    pipe(to_pipe);

    if(fork() == 0) {
        close(from_pipe[0]);
        get_primes(to_pipe);
    }
    else{
        close(to_pipe[0]);
        while(read(from_pipe[0], &num, 4) != 0){
            if(num % cur_prime != 0){
                write(to_pipe[1], &num, 4);
            } 
        } 
        close(from_pipe[0]);
        close(to_pipe[1]); 
        wait(0);
    }
}
int main(int argc, char *argv[]){
    int p[2];
    pipe(p);

    if(fork() == 0){ //子孙进程
        get_primes(p);
    } else{ //主进程
        close(p[0]);
        for(int i = 2; i <= 35; i ++) write(p[1], &i, 4);
        close(p[1]);
        wait(0);
    }
    exit(0);
}