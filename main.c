#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define LENGTH  3
#define WIN_STRIKE  3
char xoMatrix[LENGTH][LENGTH];
void matrixInit(void);
void printMatrix(void);
uint8_t notEmpty(uint8_t row, uint8_t col);
uint8_t checkWin(void);
void startTheGame(uint8_t *winStatus);

int main()
{
    uint8_t winnerNotExist = 0;
    while(1)
    {
        startTheGame(&winnerNotExist);
        if(winnerNotExist)
        {
                printf("********************************\n");
                printf("********************************\n");
                printf("************* Draw *************\n");
                printf("********************************\n");
                printf("********************************\n\n");
        }
        else
        {
            break;
        }
    }



    return 0;
}

void matrixInit(void)
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
void printMatrix(void)
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

uint8_t notEmpty(uint8_t row, uint8_t col)
{
    if(xoMatrix[row][col] >= '1' && xoMatrix[row][col]<= '9')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
uint8_t checkWin(void)
{
    uint8_t rows = 0, cols= 0, counter1 = 0,counter2 = 0,counter3 = 0,counter4 = 0;
    for(rows = 0 ; rows < LENGTH ; rows++)
    {
        for(cols = 0 ; cols < LENGTH ; cols++)
        {
           if(xoMatrix[rows][cols] == 'X')
           {
               counter1++;
           }
           else if(xoMatrix[rows][cols] == 'O')
           {
               counter2++;
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
        if(counter1 == WIN_STRIKE || counter2 == WIN_STRIKE || counter3 == WIN_STRIKE || counter4 == WIN_STRIKE)
        {
            return 1;
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
        return 1;
    }
    else
    {
        return 0;
    }
}
void startTheGame(uint8_t *drawStatus)
{
    uint8_t rows = 0, cols= 0;
    uint8_t input = 0;
    uint8_t chosenRow = 0, chosenCol = 0;
    char currentTurn = 'X';
    *drawStatus = 1;

    matrixInit();

    for(rows = 0 ; rows < LENGTH ; rows++)
    {
        for(cols = 0 ; cols < LENGTH ; cols++)
        {

            printf("%c turn, please choose empty number\n",currentTurn);
            printMatrix();
            scanf(" %c",&input);

            while(1)
            {
                chosenRow = (input-'1')/LENGTH;
                chosenCol = (input-'1')%LENGTH;
                if(notEmpty(chosenRow,chosenCol))
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


            if(checkWin())
            {
                printMatrix();
                printf("********************************\n");
                printf("********************************\n");
                printf("***** %c user is the Winner *****\n",currentTurn);
                printf("********************************\n");
                printf("********************************\n\n");
                *drawStatus = 0;
                return;
            }
            else
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

        }
    }


}
