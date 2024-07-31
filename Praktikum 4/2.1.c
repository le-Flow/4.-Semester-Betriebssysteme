#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#define MAX 100000
#define NUM_THREADS 4

int prime_count = 0;

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

int is_prime(unsigned long number){
    return modexp(2,number-1,number)==1;
}


void* count_primes(void* arg) {
    int start = *((int*)arg);
    int end = start + MAX / NUM_THREADS;

    for (int i = start; i < end; i++) {
        if (is_prime(i)) {
            prime_count++;
        }
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i * (MAX / NUM_THREADS);
        pthread_create(&threads[i], NULL, count_primes, (void*)&thread_args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Total primes: %d\n", prime_count);
    return 0;
}
