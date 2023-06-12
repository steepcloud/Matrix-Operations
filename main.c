#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_SIZE 35

// Matrices and variables for calculations
int A[MAX_SIZE][MAX_SIZE],
    B[MAX_SIZE][MAX_SIZE],
    C[MAX_SIZE][MAX_SIZE],
    SUM[MAX_SIZE][MAX_SIZE],
    PROD[MAX_SIZE][MAX_SIZE],
    TRANSP[MAX_SIZE][MAX_SIZE];
int TRC;

// Menu options
char menu[][MAX_SIZE] = {"1. Sum and product of 2 matrices", "2. Matrix trace", "3. Check symmetry"};

// Function to read matrix elements from user input
void read(char m1, int m[][MAX_SIZE], int lc) {
    printf("\nIntroduce elements of matrix %c:\n", m1);

    for (int i = 0; i < lc; i++) {
        for (int j = 0; j < lc; j++) {
            printf("\n%c[%d][%d]= ", m1, i, j);
            scanf("%d", &m[i][j]);
        }
    }

    system("cls");
}

// Function to display (contents of) a matrix
void display(char m1[], int m[][MAX_SIZE], int lc) {
    printf("%s =\n", m1);

    for (int i = 0; i < lc; i++) {
        printf("\t");

        for (int j = 0; j < lc; j++) {
            printf("%d ", m[i][j]);
        }

        printf("\n");
    }
}

// Function to display two matrices side by side
void display_1(char m1, char m2, int mat1[][MAX_SIZE], int mat2[][MAX_SIZE], int n) {
    printf("%c, %c =\n", m1, m2);

    for (int i = 0; i < n; i++) {
        int ok = 0,
             k = 0;

        printf("\t");

        while (k < 2) {
            if (ok) {
                printf(" ");
            }

            if (k % 2 == 0) {
                for (int j = 0; j < n; j++) {
                    printf("%d ", mat1[i][j]);
                }
            }
            else {
                for (int j = 0; j < n; j++) {
                    printf("%d ", mat2[i][j]);
                }
            }

            ok = 1;
            k++;
        }
        printf("\n");
    }
}

// Function to print the menu options
void printMenu(char menu[][MAX_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n",  menu[i]);
    }

    printf("\n");
}

// Function to ask the user if they want to return to the menu
void comeBack() {
    int ans;

    printf("\nDo you want to return to the menu? (y/n) ");

    while ((ans = _getch()) != ('y' && 'n')) {
        if (ans == 'n') {
            exit(0);
        }
        else {
            if (ans == 'y') {
                break;
            }
        }

        printf("\nUnknown command!");
        Sleep(1000);
        printf("\r                    ");
        CONSOLE_SCREEN_BUFFER_INFO coninfo;   // structure for cursor position
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // get console handle
        GetConsoleScreenBufferInfo(hConsole, &coninfo);  // get cursor position
        coninfo.dwCursorPosition.Y -= 1;    // moving one line up
        coninfo.dwCursorPosition.X += 15;    // moving right with 15 characters
        SetConsoleCursorPosition(hConsole, coninfo.dwCursorPosition);   // set cursor position
    }
}

// Function to calculate the sum of two matrices
void sum(int lc) {
    for (int i = 0; i < lc; i++) {
        for (int j = 0; j < lc; j++) {
            SUM[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Function to calculate the product of two matrices
void product(int lc) {
    for (int i = 0; i < lc; i++) {
        for (int j = 0; j < lc; j++) {
            PROD[i][j] = 0;

            for (int k = 0; k < lc; k++) {
                PROD[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Function to calculate the trace of a square matrix
void trace(int m[][MAX_SIZE], int lc) {
    TRC = 0;
    for (int i = 0; i < lc; i++) {
        TRC += m[i][i];
    }
}

// Function to calculate the transpose of a matrix
void transpose(int m[][MAX_SIZE], int lc) {
    for (int i = 0; i < lc; i++) {
        for (int j = 0; j < lc; j++) {
            TRANSP[i][j] = m[j][i];
        }
    }
}

// Function to check if a matrix is symmetric or antisymmetric
int check_sym(int m[][MAX_SIZE], int lc) {
    int ok = 1;

    for (int i = 0; i < lc; i++) {
        for (int j = 0; j < lc; j++) {
            if (TRANSP[i][j] != m[i][j]) {
                ok = 0;
                break;
            }
        }
    }
    return ok;
}

// Function for the "Sum and product of 2 matrices" menu option
void do1(int *n) {
    system("cls");

    printf("Introduce a number of rows and columns: ");

    scanf("%d", &*n);

    read('A', A, *n);
    read('B', B, *n);

    sum(*n);
    product(*n);

    display_1('A', 'B', A, B, *n);

    display("Sum", SUM, *n);
    display("Product", PROD, *n);

    comeBack();
}

// Function for the "Matrix trace" menu option
void do2(int *n) {
    system("cls");

    printf("Introduce a number of rows and columns: ");

    scanf("%d", &*n);

    read('C', C, *n);

    display("C", C, *n);

    trace(C, *n);

    printf("\nTrace of matrix is: %d\n", TRC);

    comeBack();
}

// Function for the "Check symmetry" menu option
void do3(int *n) {
    system("cls");
    
    printf("Introduce a number of rows and columns: ");

    scanf("%d", &*n);

    read('C', C, *n);

    display("C", C, *n);

    transpose(C, *n);

    display("Transpose", TRANSP, *n);

    if (check_sym(C, *n)) {
        printf("\nMatrix is symmetric!\n");
    }
    else {
        printf("\nMatrix is antisymmetric!\n");
    }

    comeBack();
}

int main() {
    int *n, ch;

    system("cls");
    printMenu(menu, sizeof(menu) / sizeof(menu[0]));

    while((ch = _getch()) != '\r') {
        switch(ch) {
            case '1':   do1(&n);
                        break;

            case '2':   do2(&n);
                        break;

            case '3':   do3(&n);
                        break;

            default:    printf("Unknown command!\n");
                        Sleep(1000);
        }

        system("cls");
        printMenu(menu, sizeof(menu) / sizeof(menu[0]));
    }

    return 0;
}