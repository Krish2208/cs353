#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct msg_buffer{
    long msg_type;
    int msg_text;
};

int main() {
    struct msg_buffer message;
    key_t key;
    int msg_id;
    key = ftok("progfile", 65);
    msg_id = msgget(key, 0666 | IPC_CREAT);
    message.msg_type = 1;
    printf("Write Data: ");
    int n;
    scanf("%d", &n);
    message.msg_text = n;
    msgsnd(msg_id, &message, sizeof(message), 0);
    printf("Data sent is: %d\n", message.msg_text);
    struct msg_buffer message2;
    for(int i = 0; i < n; i++) {
        msgrcv(msg_id, &message2, sizeof(message2), 1, 0);
        printf("Data received is: %d\n", message2.msg_text);
        message2.msg_type = 1;
        message2.msg_text = -1;
        msgsnd(msg_id, &message2, sizeof(message2), 0);
    }    
    msgctl(msg_id, IPC_RMID, NULL);
    return 0;
}