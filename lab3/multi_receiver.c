#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct msg_buffer{
    long msg_type;
    char msg_text[100];
};

int main() {
    struct msg_buffer messages[100];
    key_t key;
    int msg_id;
    key = ftok("progfile", 65);
    msg_id = msgget(key, 0666 | IPC_CREAT);
    int i = 0;
    while(1){
        msgrcv(msg_id, &messages[i], sizeof(messages[i]), 1, 0);
        printf("Data received is: %s\n", messages[i].msg_text);
        if(messages[i].msg_text[0] == 'e' && messages[i].msg_text[1] == 'n' && messages[i].msg_text[2] == 'd') break;
        i++;
    }
    msgctl(msg_id, IPC_RMID, NULL);
    return 0;
}