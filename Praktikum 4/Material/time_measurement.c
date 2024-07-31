/**
 * time_measurement.c
 *
 * HAW Landshut
 * Fakultät Informatik
 *
 * in Verbindung mit time_measurement.c
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

#include "time_measurement.h"


Measurement startMeasurement(){

    Measurement result;
    struct timeval begin;
    gettimeofday(&begin,(struct timezone *)0);
    result.begin = begin;
    return result;
}

double stopMeasurement(Measurement measurement){
    double result = 0.0;
    struct timeval end;
    gettimeofday(&end,(struct timezone *)0);
    measurement.end = end;

    result = (measurement.end.tv_sec -measurement.begin.tv_sec) * 1000.0; //Sekunden nach Millisekunden
    result += (measurement.end.tv_usec -measurement.begin.tv_usec) / 1000.0;

    return result;

}
