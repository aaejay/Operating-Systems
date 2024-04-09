#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

char board[3][3];  //keeping it global so we can change it in other functions
int flag[2] = {0, 0}; // Flags to indicate intention to enter critical section
int turn = 0; // Shared variable to indicate whose turn it is
int gameover=0;

void boardInitialize() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = '-';  //initializing it with a blank 
        }
    }
}

void printboard() {
    printf("  0  1  2\n");
    for (int i = 0; i < 3; i++) {
        printf("%d  ", i);
        for (int j = 0; j < 3; j++) {
            printf("%c  ", board[i][j]);
        }
        printf("\n");
    }
}

int check(char symbol) {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
            return 1; //check for  rows
    }
    // Check columns
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == symbol && board[1][j] == symbol && board[2][j] == symbol)
            return 1; // check for cols
    }
    // Check diagonals
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
        return 1;
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
        return 1;

    return 0;
}

int checkEnd() {
    if ( (board[0][0] != '-' && board[0][1] != '-' && board[0][2] != '-' &&
        board[1][0] != '-' && board[1][1] != '-' && board[1][2] != '-' &&
        board[2][0] != '-' && board[2][1] != '-' && board[2][2] != '-')) {
            return 1; // Game is over
        }
    return 0; // Game is not over yet
}

void enter_critical_section(int self) {
    int other = 1 - self;
    flag[self] = 1; // I want to enter
    turn = other;   // But it's your turn
    while (flag[other] == 1 && turn == other); // Wait while the other is in the critical section or it's their turn
}

void leave_critical_section(int self) {
    flag[self] = 0; // I'm done
}

void* PlayerTurn(void *arg) {
    int row,col;
    while (!gameover) {
        enter_critical_section(0);
        int valid_input = 0;
        while (!valid_input && !gameover) {
            printf("Your turn. Enter row and column numbers (0-2): ");
            if (scanf("%d %d", &row, &col) != 2 || row < 0 || row > 2 || col < 0 || col > 2) {
                // Invalid input, clear input buffer
                while (getchar() != '\n');
                printf("Invalid input. Please enter row and column numbers between 0 and 2.\n");
            } else {
                if (board[row][col] == '-') {
                    valid_input = 1;
                    board[row][col] = 'X';
                    printboard();
                    if (check('X')) {
                        printf("Congratulations! You win!\n");
                        gameover = 1;  //setting flag to 1 to exit loop
                    }
                    if (checkEnd()) {
                        printf("Game ended in a draw!\n");
                        gameover = 1;
                    }
                } else {
                    printf("This cell is already taken. Try again.\n");
                }
            }
        }
        leave_critical_section(0); //to get the comp to start its turn
    }
    return NULL;
}

void* ComputerTurn(void *arg) {
    int row,col;
    while (!gameover) {
        enter_critical_section(1);
        printf("Computer's turn...\n");
        sleep(1);
        row = rand() % 3; //to randomize a number btw 0 and 2
        col = rand() % 3;
        if (board[row][col] == '-') {
            board[row][col] = 'O';
            printboard();
            if (check('O')) {
                printf("Computer wins! Try again.\n");
                gameover = 1;
            }
            if (checkEnd()) {
                printf("Game ended in a draw!\n");
                gameover = 1;
            }
        }
        leave_critical_section(1);
    }
    return NULL;
}

int main() {
     // Seed the random number generator

    boardInitialize();
    printboard();
    pthread_t player, computer;

    pthread_create(&player, NULL, PlayerTurn, NULL);
    pthread_create(&computer, NULL, ComputerTurn, NULL);

    pthread_join(player, NULL);
    pthread_join(computer, NULL);

    return 0;
}
