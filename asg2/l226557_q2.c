#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#define NumberOfAccounts 5

pthread_mutex_t mutex; 

void deposit(int *balance, int amount, int accountNum) {
    pthread_mutex_lock(&mutex); 
    balance[accountNum] += amount;
    printf("Deposited %d to Account %d. New balance: %d\n", amount, accountNum + 1, balance[accountNum]);
    pthread_mutex_unlock(&mutex); 
}

void withdraw(int *balance, int amount, int accountNum) {
    pthread_mutex_lock(&mutex); 
    if (balance[accountNum] >= amount) {
        balance[accountNum] -= amount;
        printf("Withdrawn %d from Account %d. New balance: %d\n", amount, accountNum + 1, balance[accountNum]);
    } else {
        printf("Insufficient balance for withdrawal from Account %d.\n", accountNum + 1);
    }
    pthread_mutex_unlock(&mutex); 
}

int main(void) {
    int balance[NumberOfAccounts]={0};
    pthread_mutex_init(&mutex, NULL); 

    for (int i = 0; i < NumberOfAccounts; i++) {
        pid_t p = fork();
        if (p < 0) {
            perror("fork failed");
            exit(1);
        } else if (p == 0) {
            deposit(balance, 300, i);
            withdraw(balance, 34, i);
            exit(0);
        } else {
            wait(NULL); 
        }
    }

    pthread_mutex_destroy(&mutex); 

    return 0;
}
