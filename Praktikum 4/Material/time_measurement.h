/**
 * time_measurement.h
 *
 * HAW Landshut
 * Fakultät Informatik
 *
 * in Verbindung mit time_measurement.h
 *
 *
 * Dient zur Zeitmessung in ms. Benutzung:
 *
 * //Start der Zeitmessung
 * Measurement m1 = startMeasurement;
 * ...
 * Code, dessen Ausführungszeit gemessen werden soll
 * ...
 * //Ende der Zeitmessung; Ergebnis in Millisekunden
 * double execution_time = stopMeasurement(m1);
 *
 */

#ifndef TIME_MEASUREMENT_H
#define TIME_MEASUREMENT_H
#include <sys/time.h>



typedef struct {
    struct timeval begin;
    struct timeval end;
}Measurement;


Measurement startMeasurement();

double stopMeasurement(Measurement measurement);




#endif
