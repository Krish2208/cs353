#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int pipefd[2];
    char buf[100];
    pipe(pipefd);
    if(fork() == 0){
        printf("Enter a string: ");
        fgets(buf, 100, stdin);
        write(pipefd[1], buf, strlen(buf)+1);
        exit(0);
    }
    else{
        read(pipefd[0], buf, 100);
        printf("Received string: %s", buf);
        exit(0);
    }
}