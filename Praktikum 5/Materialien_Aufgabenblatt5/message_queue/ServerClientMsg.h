/*
 ============================================================================
 ServerClientMsg.h

 HAW Landshut
 Fakultät Informatik
 Modul: Betriebssysteme


 Aufgabenblatt 5

 ============================================================================
 */



#ifndef SERVERCLIENTMSG_H_
#define SERVERCLIENTMSG_H_

#include <sys/unistd.h>

/* Schlüssel der Message-Queue für Server und Clients */
#define MQ_KEY 0xD7
/* Maximale Länge des Nachrichtentextes */
#define MAX_LAENGE 1000
/*  Server hört auf Nachrichten vom Typ SERVER_TYPE */
#define SERVER_TYPE 1

/* Struktur des Inhalts einer Nachricht vom Typ SERVER_TYPE
 *
 * pid_sender    Prozess-ID des Senders
 * text          der zu übermittelnde Text
 */
typedef struct {
	pid_t pid_sender;
	char text [MAX_LAENGE];
} msg_content;

/* Struktur einer Nachricht vom Typ SERVER_TYPE
 *
 * type 	Nachrichtentyp
 * content  Inhalt der Nachricht
 */
typedef struct
{
	long type;
 	msg_content content;
} msg;

extern int setupQueue();
extern int sendMessage(long type, msg_content content);

#endif /* SERVERCLIENTMSG_H_ */
