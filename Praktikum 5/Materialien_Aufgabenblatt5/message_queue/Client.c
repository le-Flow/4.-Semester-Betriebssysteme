/*
 ============================================================================
 Client.c

 HAW Landshut
 Fakultät Informatik
 Modul: Betriebssysteme


 Aufgabenblatt 5

 Aufgabenstellung: Vervollständigen Sie die Stellen im Code, die mit
 "Bitte vervollständigen" gekennzeichnet sind.

 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#include "ServerClientMsg.h"

/* Client-Prozess */
int main(int argc, char** argv) {

    int qid;
    /* Die Variable, in die eingehende Nachrichten geschrieben werden */
    msg rcvMessage;
    /* Der Inhalt der Nachricht, die an den Server geschickt wird */
    msg_content content;

    pid_t pid = getpid();

    content.pid_sender = pid;
    printf("PID: %d\n", content.pid_sender);
    strcpy(content.text,"Hallo Welt!\0");

    printf("Client %d startet ...\n", pid);

    sendMessage(SERVER_TYPE,content);

    /* eigene Queue aufmachen */
    qid = setupQueue();
    if(qid>=0){
        while(1){
            /* Auf (alle) eingehende Nachrichten warten und empfangen */
        	/* Bitte vervollständigen */


        	if(len>0)
        		printf("Nachricht von Server: %s\n", rcvMessage.content.text);
        	else {
        		printf("Fehler beim Lesen einer Nachricht von Server\n");
        		break;
        	}

        }
    }

    printf("Client %d beendet sich.\n", pid);
    return (EXIT_SUCCESS);
}

