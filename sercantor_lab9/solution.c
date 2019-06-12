#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_THREADS 5
#define BUFFER_SIZE 10

sem_t *empty, *full, *mutex;

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

static volatile int keepRunning = 1;

void intHandler(int dummy) {
    keepRunning = 0;
}

void *producer(void * id_ptr) {
    int ID = *((int *) id_ptr);
    static int nextProduced = 0;

    while (keepRunning) {

        (void) sem_wait(empty);
        (void) sem_wait(mutex);

       /* Check to see if Overwriting unread slot */
        if (buffer[in] != -1) {
            fprintf(stderr, "Synchronization Error: Producer %d Just overwrote %d from Slot %d\n", ID, buffer[in], in);
            exit(1);
        }

        nextProduced++; // Producing Integers

        /* Looks like we are OK */
        buffer[in] = nextProduced;
        printf("Producer %d. Put %d in slot %d\n", ID, nextProduced, in);
        in = (in + 1) % BUFFER_SIZE;
        printf("incremented in!\n");

        (void) sem_post(mutex);
        (void) sem_post(full);
    }

    return NULL;
}

void *consumer (void *id_ptr) {
    int ID = *((int *) id_ptr);
    static int nextConsumed = 0;

    while (keepRunning) {

        (void) sem_wait(full);
        (void) sem_wait(mutex);

        nextConsumed = buffer[out];

        /* Check to make sure we did not read from an empty slot */
        if (nextConsumed == -1) {
            fprintf(stderr, "Synch Error: Consumer %d Just Read from empty slot %d\n", ID, out);
            exit(1);
        }

        /* We must be OK */
        printf("Consumer %d Just consumed item %d from slot %d\n", ID, nextConsumed, out);
        buffer[out] = -1;
        out = (out + 1) % BUFFER_SIZE;
        printf("incremented out!\n");

        (void) sem_post(mutex);
        (void) sem_post(empty);
    }

    return NULL;
}

int main() {
    int ID[MAX_THREADS];
    pthread_t TID[MAX_THREADS];

    empty = sem_open("/empty", O_CREAT, 0644, 10);
    full = sem_open("/full", O_CREAT, 0644, 0);
    mutex = sem_open("/mutex", O_CREAT, 0644, 1);

    signal(SIGINT, intHandler);

    for (int i = 0; i < MAX_THREADS; i++) {
        ID[i] = i;
    }

    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = -1;
    }

    pthread_create(&TID[0], NULL, producer, (void *) &ID[0]);
    printf("Producer ID = %d created!\n", 0);
    sleep(1);
    pthread_create(&TID[1], NULL, consumer, (void *) &ID[1]);
    printf("Consumer ID = %d created!\n", 1);

    pthread_create(&TID[2], NULL, producer, (void *) &ID[2]);
    printf("Producer ID = %d created!\n", 2);
    pthread_create(&TID[3], NULL, consumer, (void *) &ID[3]);
    printf("Consumer ID = %d created!\n", 3);

    for (int i = 0; i < 4; i++) {
        pthread_join(TID[i], NULL);
    }

    (void) sem_unlink("/empty");
    (void) sem_unlink("/full");
    (void) sem_unlink("/mutex");

    return 0;
}
