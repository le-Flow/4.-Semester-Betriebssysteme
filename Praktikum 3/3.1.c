#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h> // Für intptr_t

bool is_prime(int num) {
    if (num <= 1) {
        return false;
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

typedef struct {
    int start;
    int end;
} Range;

void *findPrimes(void *arg) {
    Range *range = (Range *)arg;
    int count = 0;

    for (int num = range->start; num <= range->end; num++) {
        if (is_prime(num)) {
            count++;
        }
    }

    pthread_exit((void *)(intptr_t)count);
}

int main() {
    const int lower_bound = 10000000;
    const int upper_bound = 20000000;
    const int thread_count = 1;

    pthread_t threads[thread_count];
    Range range = {lower_bound, upper_bound};

    clock_t start_time, end_time;
    double execution_time;

    start_time = clock();

    pthread_create(&threads[0], NULL, findPrimes, (void *)&range);

    int count;
    pthread_join(threads[0], (void **)&count);

    end_time = clock();
    execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Anzahl der Primzahlen im Bereich von %d bis %d: %d\n", lower_bound, upper_bound, count);
    printf("Ausführungszeit: %.6f Sekunden\n", execution_time);

    return 0;
}
