#include "ServerClientMsg.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>

int setupQueue() {
    key_t key = ftok("serverclientmsg", MQ_KEY); // Generate unique key
    int qid = msgget(key, 0666 | IPC_CREAT); // Create message queue and return id
    if (qid < 0) {
        perror("msgget");
    }
    return qid;
}

int sendMessage(long type, msg_content content) {
    int qid;
    msg message;

    qid = setupQueue();
    if (qid < 0) {
        printf("Fehler beim Einrichten oder Öffnen der Message Queue\n");
        return -1;
    } else {
        message.type = type;
        message.content = content;

        if (msgsnd(qid, &message, sizeof(msg_content), 0) < 0) {
            perror("msgsnd");
            return -1;
        }
    }
    return 0;
}
