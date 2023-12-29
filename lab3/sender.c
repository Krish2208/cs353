#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct msg_buffer{
    long msg_type;
    char msg_text[100];
} message;

int main() {
    key_t key;
    int msg_id;
    key = ftok("progfile", 65);
    msg_id = msgget(key, 0666 | IPC_CREAT);
    message.msg_type = 1;
    printf("Write Data: ");
    fgets(message.msg_text, 100, stdin);
    msgsnd(msg_id, &message, sizeof(message), 0);
    printf("Data sent is: %s\n", message.msg_text);
    msgctl(msg_id, IPC_RMID, NULL);
    return 0;
}