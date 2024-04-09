#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_CHAIRS 5
#define NUM_CUSTOMERS 10

sem_t barber_ready;
sem_t customer_ready;
sem_t access_seats;
int num_waiting = 0;
int served_customers = 0;

void *barber(void *arg) {
    while (served_customers < NUM_CUSTOMERS) {
        sem_wait(&customer_ready); // Wait for a customer to wake up the barber
        sem_wait(&access_seats);   // Ensure exclusive access to the number of waiting chairs

        num_waiting--;
        printf("Barber: Cutting hair\n");
        sleep(2); // Simulate hair cutting process

        sem_post(&access_seats); // Release access to the number of waiting chairs
        sem_post(&barber_ready); // Signal that the barber is ready
        served_customers++;
    }
    pthread_exit(NULL);
}

void *customer(void *arg) {
    int customer_id = *(int *)arg;
    printf("Customer %d: Entering the barbershop\n", customer_id);

    sem_wait(&access_seats); // Ensure exclusive access to the number of waiting chairs

    if (num_waiting < NUM_CHAIRS) {
        num_waiting++;
        printf("Customer %d: Waiting in the waiting room\n", customer_id);
        sem_post(&customer_ready); // Wake up the barber if asleep
        sem_post(&access_seats);   // Release access to the number of waiting chairs
        sem_wait(&barber_ready);   // Wait for the barber to become ready
        printf("Customer %d: Getting haircut\n", customer_id);
    } else {
        printf("Customer %d: Leaving the barbershop (No seats available)\n", customer_id);
        sem_post(&access_seats); // Release access to the number of waiting chairs
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t barber_thread;
    pthread_t customer_threads[NUM_CUSTOMERS];
    int customer_ids[NUM_CUSTOMERS];

    sem_init(&barber_ready, 0, 0);
    sem_init(&customer_ready, 0, 0);
    sem_init(&access_seats, 0, 1);

    pthread_create(&barber_thread, NULL, barber, NULL);

    // Create customer threads
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        customer_ids[i] = i + 1;
        pthread_create(&customer_threads[i], NULL, customer, (void *)&customer_ids[i]);
        sleep(1); // Introduce delay between customer arrivals
    }

    pthread_join(barber_thread, NULL); //joining to avoid 
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        pthread_join(customer_threads[i], NULL);
    }

    sem_destroy(&barber_ready); //destroying to clear memory
    sem_destroy(&customer_ready);
    sem_destroy(&access_seats);

    return 0;
}

























#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void *printer()
{
printf("Hello %ld \n",(long)pthread_self());
pthread_exit(NULL);
}


int main(int argc, char* argv[])
{
if (argc < 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }
    int num = atoi(argv[1]);
pthread_t threads[num];

for(int i=0;i<num;i++){
if(i%5==0)
{
sleep(1);
}
pthread_create(&threads[i],NULL,printer,NULL);

}

for(int i=0;i<num;i++)
{
pthread_join(threads[i],NULL);
}
return 0;

}
