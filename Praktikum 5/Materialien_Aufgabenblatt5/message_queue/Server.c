/*
 ============================================================================
 Server.c

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
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#include "ServerClientMsg.h"

void setSigKillAction();
void event_receive_sigkill();

int qid;

int main(void) {
		msg message;

		/* maximal 100 Clients */
		long pids[100];
	    int currentIndex = 0;

	    printf("Server startet ...\n");
	    qid = setupQueue();
	    printf("Die Queue mit der QID %d wurde eingerichtet.\nServer wartet auf Clients...\n\n", qid);
	    if(qid>=0){
	    	setSigKillAction();

	    	/* Mit jedem Empfang einer Nachricht durchläuft der Server einmal die while-Schleife */
	        while(1){
	        	/* Warten auf den Empfang einer Nachricht vom Typ SERVER_TYPE */
	        	/* Bitte vervollständigen */


	            msg_content content;
	            content = message.content;

	            /* An den Client, der gerade dazu gekommen ist "Willkommen" schicken. */
	            pids[currentIndex] = content.pid_sender;
	            msg_content firstReturn;
	            firstReturn.pid_sender = getpid();
	            strcpy(firstReturn.text,"Willkommen!"),
	            sendMessage(pids[currentIndex],firstReturn);

	            printf("Prozess %i hat sich angemeldet\n", content.pid_sender);

	            /* Alle anderen Clients mit einer Nachricht darüber informieren */
	            for(int i = 0;i<currentIndex;i++){
	                printf("Gebe %ld bescheid...\n", pids[i]);
	                msg_content broadcast;
	                broadcast.pid_sender = getpid();

	                sprintf(broadcast.text,"Prozess %i ist jetzt auch dabei.",content.pid_sender);
	                sendMessage(pids[i],broadcast);
	            }
	            currentIndex++;

	        }
	    }

	    return (EXIT_SUCCESS);
}

void setSigKillAction(){
	struct sigaction receiverSIGINT ={0};
	struct sigaction receiverSIGKILL = {0};
	receiverSIGINT.sa_handler = event_receive_sigkill;
	receiverSIGKILL.sa_handler = event_receive_sigkill;
	sigaction (SIGINT, &receiverSIGINT, 0);
	sigaction (SIGKILL, &receiverSIGKILL, 0);
}

void event_receive_sigkill(){
	printf("Lösche Message Queue mit der QID %d.\n",qid);
	/* Bitte vervollständigen */

	exit(0);
}


