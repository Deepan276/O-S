#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MESSAGE_SIZE 128

struct Message {
    long mtype; 
    char mtext[MESSAGE_SIZE]; 
};

int main() {
    
    key_t key = ftok("msgq_example", 5678);
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    int msgqid = msgget(key, IPC_CREAT | 0666);
    if (msgqid == -1) {
        perror("msgget");
        exit(1);
    }

    struct Message message;

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0) {
        
        if (msgrcv(msgqid, &message, MESSAGE_SIZE, 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        printf("Child process received message: %s\n", message.mtext);

        exit(0);
    } else {
        
        message.mtype = 1;
        strcpy(message.mtext, "Hello from the parent process!");

        if (msgsnd(msgqid, &message, sizeof(message.mtext), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        wait(NULL);

        if (msgctl(msgqid, IPC_RMID, NULL) == -1) {
            perror("msgctl");
            exit(1);
        }
    }

    return 0;
}
