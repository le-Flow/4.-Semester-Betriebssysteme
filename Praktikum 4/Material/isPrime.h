/**
 * isPrime.h
 *
 * HAW Landshut
 * Fakultät Informatik
 *
 * in Verbindung mit isPrime.c
 *
 *
 * Führt einen Fermatschen Primzahlentest durch. Der Test wird von der
 * Funktion isPrime durchgeführt. Die Funktion liefert eine 1, wenn es 
 * sich um eine Primzahl handelt und eine 0, wenn es sich um keine Primzahl handelt.
 *
 *
 */

#ifndef IS_PRIME
#define IS_PRIME


int modexp(unsigned long x, unsigned long y, unsigned long p );

int isPrime(unsigned long number);

#endif // IS_PRIME
