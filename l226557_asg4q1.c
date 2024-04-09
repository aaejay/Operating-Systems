#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_ROWS 100
#define MAX_COLS 100

int matrix[MAX_ROWS][MAX_COLS];
int m, n; // dimensions of the matrix

void *convertBinaryToDecimal(void *arg) {
    int *array = (int *)arg;
    int result = 0;

    for (int i = 0; i < array[0]; i++) {
        result = result * 2 + array[i + 1];
    }

    printf("Converted: %d\n", result);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <number of rows> <number of columns>\n", argv[0]);
        return 1;
    }

    m = atoi(argv[1]);
    n = atoi(argv[2]);

    // Input the matrix
    printf("Enter the binary matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    pthread_t threads[MAX_ROWS];
if (MAX_ROWS > MAX_COLS) {
    // If the number of rows is greater than the number of columns
    // Use MAX_ROWS as the size of the array
    pthread_t threads[MAX_ROWS];
} else {
    // If the number of columns is greater than or equal to the number of rows
    // Use MAX_COLS as the size of the array
    pthread_t threads[MAX_COLS];
}

    // Create threads based on the last digit of the student ID
    int num_threads = (m * n) % 10 <= 4 ? n : m;
    for (int i = 0; i < num_threads; i++) {
        int *array = malloc((m * n) % 10 <= 4 ? m : n * sizeof(int));
        if ((m * n) % 10 <= 4) {
            array[0] = m;
            for (int j = 0; j < m; j++) {
                array[j + 1] = matrix[j][i];
            }
        } else {
            array[0] = n;
            for (int j = 0; j < n; j++) {
                array[j + 1] = matrix[i][j];
            }
        }
        pthread_create(&threads[i], NULL, convertBinaryToDecimal, (void *)array);
    }

    // Join threads
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}














#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

int main() {
    int ofd = open("orig.txt", O_RDONLY);
    if (ofd == -1) {
        perror("Error opening orig.txt");
        return 1;
    }

    // Duplicate the file descriptor
    int dfd = dup(ofd);
    if (dfd == -1) {
        perror("Error duplicating file descriptor");
        close(ofd);
        return 1;
    }

    // Open a temporary file for writing
    int tempfd = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (tempfd == -1) {
        perror("Error opening temp.txt");
        close(ofd);
        close(dfd);
        return 1;
    }

    // Read from original file, convert to lowercase, and write to temp file
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    while ((bytes_read = read(ofd, buffer, BUFFER_SIZE)) > 0) {
        for (ssize_t i = 0; i < bytes_read; i++) {
            buffer[i] = tolower(buffer[i]);
        }
        ssize_t bytes_written = write(tempfd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to temp.txt");
            close(ofd);
            close(dfd);
            close(tempfd);
            return 1;
        }
    }

    // Close file descriptors
    close(ofd);
    close(dfd);
    close(tempfd);

    // Rename temp file to original file
    if (rename("temp.txt", "orig.txt") == -1) {
        perror("Error renaming temp.txt to original.txt");
        return 1;
    }

    printf("File successfully updated with lowercase text.\n");

    return 0;
}
