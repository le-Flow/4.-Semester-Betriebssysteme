/**
 * isPrime.c
 *
 * HAW Landshut
 * Fakultät Informatik
 *
 * in Verbindung mit isPrime.h
 *
 *
 * Führt einen Fermatschen Primzahlentest durch. Der Test wird von der
 * Funktion isPrime durchgeführt. Die Funktion liefert eine 1, wenn es 
 * sich um eine Primzahl handelt und eine 0, wenn es sich um keine Primzahl handelt.
 *
 *
 */

#include "isPrime.h"

int modexp(unsigned long x, unsigned long y, unsigned long p ){
    int result = 1;
    x = x%p;
    if (x == 0) return 0;
    while (y>0){
        if (y & 1)
            result = (result*x) % p;

        y = y>>1;
        x=(x*x) % p;
    }
    return result;
}

int isPrime(unsigned long number){
    return modexp(2,number-1,number)==1;
}
