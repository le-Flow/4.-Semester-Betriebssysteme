#include <stdio.h>      // Für Ein- und Ausgabefunktionen
#include <stdlib.h>     // Für allgemeine Hilfsfunktionen wie exit()
#include <sys/types.h>  // Für Datentypen wie pid_t
#include <sys/ipc.h>    // Für IPC (Inter-Prozess-Kommunikations)-Mechanismen
#include <sys/msg.h>    // Für Nachrichtenwarteschlangen-Operationen
#include <string.h>     // Für Stringfunktionen wie strcpy()
#include <unistd.h>     // Für POSIX-API, einschließlich getpid()

#include "ServerClientMsg.h"  // Benutzerdefinierte Header-Datei für Server-Client-Kommunikation

/* Client-Prozess */
int main(int argc, char** argv) {
    int qid;                // Nachrichtenwarteschlangen-Identifikator
    msg rcvMessage;         // Nachrichtenstruktur zum Empfangen von Nachrichten
    msg_content content;    // Inhalt der zu sendenden Nachricht

    pid_t pid = getpid();   // PID des aktuellen Prozesses abrufen
    content.pid_sender = pid;  // Setzt die Sender-PID im Nachrichteninhalt
    printf("PID: %d\n", content.pid_sender);
    strcpy(content.text, "Hallo Welt!");  // Text in den Nachrichteninhalt kopieren

    printf("Client %d startet ...\n", pid);

    sendMessage(SERVER_TYPE, content);  // Nachricht an den Server senden

    qid = setupQueue();  // Nachrichtenwarteschlange einrichten
    if (qid >= 0) {
        while (1) {  // Endlosschleife zum Empfangen von Nachrichten
            if (msgrcv(qid, &rcvMessage, sizeof(msg_content), pid, 0) > 0)
                printf("Nachricht von Server: %s\n", rcvMessage.content.text);
            else {
                printf("Fehler beim Lesen einer Nachricht vom Server\n");
                break;  // Schleife beenden bei Fehler
            }
        }
    }

    printf("Client %d beendet sich.\n", pid);
    return (EXIT_SUCCESS);  // Erfolgreiche Beendigung des Programms
}
