#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define LENGTH           3
#define WIN_STRIKE       3
#define MAX_NUMBER       9
#define DRAW             255
#define NOT_FINSHED      0
#define TRUE             1
#define FALSE            0
void matrixInit(char (*xoMatrix)[LENGTH]);
void printMatrix(char (*xoMatrix)[LENGTH]);
uint8_t notEmpty(uint8_t row, uint8_t col,char (*xoMatrix)[LENGTH]);
uint8_t checkWin(char (*xoMatrix)[LENGTH]);
void startTheGame(char (*xoMatrix)[LENGTH],char *winnerStatus);

int main()
{
    char xoMatrix[LENGTH][LENGTH];
    uint8_t winner = 0;
    uint8_t drawInRow = 0;

    while(1)
    {
        startTheGame(xoMatrix,&winner);
        if(winner == DRAW)
        {
                drawInRow++;
                printf("********************************\n");
                printf("********************************\n");
                printf("************* Draw *************\n");
                printf("********************************\n");
                printf("********************************\n\n");
                printf("Draw times in row = %d\n\n",drawInRow);

        }
        else
        {
                printMatrix(xoMatrix);
                printf("********************************\n");
                printf("********************************\n");
                printf("***** %c user is the Winner *****\n",winner);
                printf("********************************\n");
                printf("********************************\n\n");

            break;
        }
    }

    return 0;
}

void matrixInit(char (*xoMatrix)[LENGTH])
{
    uint8_t rows = 0, cols= 0, counter = 0;
    for(rows = 0 ; rows < LENGTH ; rows++)
    {
        for(cols = 0 ; cols < LENGTH ; cols++)
        {
            xoMatrix[rows][cols] = (char)('1'+counter++);
        }
    }
}
void printMatrix(char (*xoMatrix)[LENGTH])
{
    uint8_t rows = 0, cols= 0, counter = 0;
    for(rows = 0 ; rows < LENGTH ; rows++)
    {
        for(cols = 0 ; cols < LENGTH ; cols++)
        {
           printf("%c ",xoMatrix[rows][cols]);
        }
        printf("\n");
    }
    printf("\n");
}

uint8_t notEmpty(uint8_t row, uint8_t col,char (*xoMatrix)[LENGTH])
{
    if(xoMatrix[row][col] >= '1' && xoMatrix[row][col]<= '9')
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
uint8_t checkWin(char (*xoMatrix)[LENGTH])
{
    uint8_t rows = 0, cols= 0, counter1 = 0,counter2 = 0,counter3 = 0,counter4 = 0, counter5 = 0;
    for(rows = 0 ; rows < LENGTH ; rows++)
    {
        for(cols = 0 ; cols < LENGTH ; cols++)
        {
           if(xoMatrix[rows][cols] == 'X')
           {
               counter1++;
               counter5++;
           }
           else if(xoMatrix[rows][cols] == 'O')
           {
               counter2++;
               counter5++;
           }
           if(xoMatrix[cols][rows] == 'X')
           {
               counter3++;
           }
           else if(xoMatrix[cols][rows] == 'O')
           {
               counter4++;
           }
        }
        if(counter1 == WIN_STRIKE || counter2 == WIN_STRIKE)
        {
            return 'X';
        }
        else if(counter3 == WIN_STRIKE || counter4 == WIN_STRIKE)
        {
            return 'O';
        }
        else
        {
             counter1 = counter2 = counter3 = counter4 = 0;
        }
    }

    if(
       (xoMatrix[0][0] == xoMatrix[1][1] && xoMatrix[0][0] == xoMatrix[2][2]) ||
       (xoMatrix[0][2] == xoMatrix[1][1] && xoMatrix[0][2] == xoMatrix[2][0])
      )
    {
        return xoMatrix[1][1];
    }
    else
    {
        if(counter5 == MAX_NUMBER)
        {
            return DRAW;
        }
        else
        {
            return NOT_FINSHED;
        }
    }
}
void startTheGame(char (*xoMatrix)[LENGTH], char *winnerStatus)
{
    uint8_t rows = 0, cols= 0;
    uint8_t input = 0;
    uint8_t chosenRow = 0, chosenCol = 0;
    char currentTurn = 'X';
    char winner = 0;

    matrixInit(xoMatrix);

    for(rows = 0 ; rows < LENGTH ; rows++)
    {
        for(cols = 0 ; cols < LENGTH ; cols++)
        {

            printf("%c turn, please choose empty number\n",currentTurn);
            printMatrix(xoMatrix);
            scanf(" %c",&input);

            while(1)
            {
                chosenRow = (input-'1')/LENGTH;
                chosenCol = (input-'1')%LENGTH;
                if(notEmpty(chosenRow,chosenCol,xoMatrix))
                {
                   printf("Wrong input! Please choose valid input\n");
                   scanf(" %c",&input);
                }
                else
                {
                    break;
                }
            }
            xoMatrix[chosenRow][chosenCol] = currentTurn;

            winner = checkWin(xoMatrix);
            if(winner == NOT_FINSHED)
            {

                if(currentTurn == 'X')
                {
                    currentTurn = 'O';
                }
                else
                {
                    currentTurn = 'X';
                }
            }
            else
            {
                 *winnerStatus = winner;
                 return;
            }

        }
    }
}
