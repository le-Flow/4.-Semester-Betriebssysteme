#include <stdio.h>      // Für Ein- und Ausgabefunktionen
#include <stdlib.h>     // Für allgemeine Hilfsfunktionen wie exit()
#include <signal.h>     // Für Signalhandhabung
#include <sys/types.h>  // Für Datentypen wie pid_t
#include <sys/ipc.h>    // Für IPC (Inter-Prozess-Kommunikations)-Mechanismen
#include <sys/msg.h>    // Für Nachrichtenwarteschlangen-Operationen
#include <string.h>     // Für Stringfunktionen wie strcpy()
#include <unistd.h>     // Für POSIX-API, einschließlich getpid()

#include "ServerClientMsg.h"  // Benutzerdefinierte Header-Datei für Server-Client-Kommunikation

void setSigKillAction();      // Funktion zur Einrichtung der Signalbehandlung
void event_receive_sigkill(); // Signalbehandlungsfunktion

int qid;  // Nachrichtenwarteschlangen-Identifikator

int main(void) {
    msg message;   // Nachrichtenstruktur zum Empfangen von Nachrichten

    long pids[100];        // Array zur Speicherung der Client-PIDs
    int currentIndex = 0;  // Aktueller Index im Array

    printf("Server startet ...\n");
    qid = setupQueue();  // Nachrichtenwarteschlange einrichten
    printf("Die Queue mit der QID %d wurde eingerichtet.\nServer wartet auf Clients...\n\n", qid);
    if (qid >= 0) {
        setSigKillAction();  // Signalbehandlung einrichten

        while (1) {  // Endlosschleife zum Empfangen von Nachrichten
            if (msgrcv(qid, &message, sizeof(msg_content), SERVER_TYPE, 0) > 0) {
                msg_content content = message.content;

                pids[currentIndex] = content.pid_sender;  // Speichert die Sender-PID
                msg_content firstReturn;
                firstReturn.pid_sender = getpid();  // Setzt die Sender-PID im Rückgabemessage
                strcpy(firstReturn.text, "Willkommen!");  // Setzt den Text in der Rückgabemessage
                sendMessage(pids[currentIndex], firstReturn);  // Sendet die Rückgabemessage

                printf("Prozess %i hat sich angemeldet\n", content.pid_sender);

                // Benachrichtigt alle bereits angemeldeten Clients über den neuen Client
                for (int i = 0; i < currentIndex; i++) {
                    printf("Gebe %ld bescheid...\n", pids[i]);
                    msg_content broadcast;
                    broadcast.pid_sender = getpid();  // Setzt die Sender-PID in der Broadcast-Nachricht
                    sprintf(broadcast.text, "Prozess %i ist jetzt auch dabei.", content.pid_sender);
                    sendMessage(pids[i], broadcast);  // Sendet die Broadcast-Nachricht
                }
                currentIndex++;  // Erhöht den Index für den nächsten Client
            } else {
                printf("Fehler beim Empfangen einer Nachricht von einem Client\n");
            }
        }
    }

    return (EXIT_SUCCESS);  // Erfolgreiche Beendigung des Programms
}

// Einrichtung der Signalbehandlung
void setSigKillAction() {
    struct sigaction receiverSIGINT = {0};  // Struktur für SIGINT
    struct sigaction receiverSIGKILL = {0}; // Struktur für SIGKILL
    receiverSIGINT.sa_handler = event_receive_sigkill;  // Signalhandler für SIGINT
    receiverSIGKILL.sa_handler = event_receive_sigkill; // Signalhandler für SIGKILL
    sigaction(SIGINT, &receiverSIGINT, 0);  // Signalbehandlung für SIGINT einrichten
    sigaction(SIGKILL, &receiverSIGKILL, 0);// Signalbehandlung für SIGKILL einrichten
}

// Signalbehandlungsfunktion
void event_receive_sigkill() {
    printf("Lösche Message Queue mit der QID %d.\n", qid);
    msgctl(qid, IPC_RMID, NULL);  // Löscht die Nachrichtenwarteschlange
    exit(0);  // Beendet das Programm
}
