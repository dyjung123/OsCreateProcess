#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void divide(pid_t forkf, int n, int *state) {
    if (forkf < 0) { // 에러 발생시 프로세스 종료
        printf("fork error");
        exit(0);
    }
    
    if (forkf == 0) { // 자식 프로세스이면 실행
        if (n == 1) { // grand child process
            printf("grand child   pid : %d , ppid : %d\n",getpid(),getppid());
            execl("/bin/ls", "ls","-l",(char*) 0);
            exit(0);
        } else { // n이 0이면 한번더 fork()
            int b;
            int *state2 = &b;
            divide(fork(), ++n, state2);
        }
    } else { // 부모 프로세스이면 실행
        if (n == 1) { // child process
            printf("child   pid : %d , ppid : %d\n",getpid(),getppid());
            wait(state);
            execl("/bin/cat", "cat","child.txt",(char*) 0);
            exit(0);
        } else { // parent process
            printf("parent   pid : %d \n",getpid());
            wait(state);
            execl("/bin/cat", "cat","parent.txt",(char*) 0);
            exit(0);
        }
    }
}

int main(int argc, const char * argv[]) {
    int n = 0;
    int a;
    int *state = &a;
    divide(fork(),n,state);
    
    return 0;
}

