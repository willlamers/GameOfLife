/* ************************************************** */
/*                                                    */
/*  Will Lamers CS 10 Sect 5393                       */
/*                                                    */
/*  Project#5 - Two-dimensional array operations:     */
/*              Game of Life program                  */
/*                                                    */
/*  input: text file containing initial populations   */
/*                                                    */
/*  output: display of bacteria after 5 generations   */
/*                                                    */
/* ************************************************** */

// The game of life is a computer simulation of the life and
// death events of a population of organisms. This program
// will determine the life, death, and survival of bacteria
// from one generation to the next, assuming the starting grid
// of bacteria is generation zero (0). Each cell has a total
// of up to 8 neighbors, including the 4 immediately adjacent
// cells and the 4 diagonal cells. The rules for the creation
// of each cell in the next generation are as follows:
//
//  If the cell is currently empty:
//      If the cell has exactly three living neighbors,
//             it will come to life in the next generation.
//      If the cell has any other number of living neighbors,
//             it will remain empty.
//
//  If the cell is currently living:
//      If the cell has one or zero living neighbors, it will
//             die of loneliness in the next generation.
//      If the cell has four or more living neighbors, it will
//             die of overcrowding in the next generation.
//      If the cell has two or three neighbors,
//             it will remain living.
//
// All births and deaths occur simultaneously.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

bool openFile (ifstream&,string);
void initBactArray(ifstream&, char[][20]);
void closeFile(ifstream&);
void displayBactArray(const char[][20]);
int countBactArrayRow(const char[][20],int);
int countBactArrayCol(const char[][20],int);
void nextGenBactArray(char[][20]);
void updateNeighborCount(const char[][20], int[][20], int, int);
void displayBactArrayStats(const char[][20]);



int main()
{
    char bacteriaArray[20][20] = {' '};
    ifstream bacteriaFile;
    string fileName = "bacteria.txt";

    if (openFile(bacteriaFile,fileName))
    {
        initBactArray(bacteriaFile, bacteriaArray);
        closeFile(bacteriaFile);
    }

    displayBactArray(bacteriaArray);
    cout << "(ORIGINAL GRID) GAME OF LIFE STATISTICS" << endl;
    displayBactArrayStats(bacteriaArray);

    for (int i = 0; i < 5; i++)
    {
        nextGenBactArray(bacteriaArray);
        displayBactArray(bacteriaArray);
        cout << "The grid after " << i+1 << " generations have passed." << endl;
        cout << "(GENERATION #" << i+1 << ") GAME OF LIFE STATISTICS" << endl;
        displayBactArrayStats(bacteriaArray);
    }

    return 0;
}


/* ************************************************** */
/*                                                    */
/*  This function gets the file name and opens the    */
/*  file, then returns a boolean value regarding      */
/*  file open                                         */
/*                                                    */
/* ************************************************** */
bool openFile (/*inout*/ifstream &inputFile,/*in*/ string fileName)
{
    bool returnValue;

    inputFile.open(fileName.c_str());

    if (inputFile.is_open())
    {
        returnValue = true;
    }
    else
    {
        cout << "Error opening the file.\n";
        returnValue = false;
    }

    return returnValue;
}


/* ************************************************** */
/*                                                    */
/*  This function reads the file and initializes the  */
/*  bacteria array                                    */
/*                                                    */
/* ************************************************** */
 void initBactArray(ifstream& inputFile, char bacteriaArray[][20])
{
    int row, col;

    while (inputFile >> row >> col)
    {
        bacteriaArray[row][col] = '*';
    }
}


/* ************************************************** */
/*                                                    */
/*  This function closes the file                     */
/*                                                    */
/* ************************************************** */

 void closeFile(ifstream& inputFile)
{

    inputFile.close();

}



/* ************************************************** */
/*                                                    */
/*  This function writes out the column numbers, then */
/*  displays bacteriaArray in a user friendly form    */
/*                                                    */
/* ************************************************** */
void displayBactArray(/*in*/ const char bacteriaArray[][20])
{
    cout << "  ";

    for (int col = 0; col < 20; col++)
    {
        cout << col%10;
    }

    cout << endl;

    for(int row = 0; row < 20; row++)
    {
        cout << setw (2) << row;

        for (int col = 0; col < 20; col++)
        {
            cout << bacteriaArray[row][col];
        }
        cout << endl;
    }
    cout << endl;
}



/* ************************************************** */
/*                                                    */
/*  This function counts the number of bacteria in    */
/*  a particular row                                  */
/*                                                    */
/* ************************************************** */
int countBactArrayRow(/*in*/ const char bacteriaArray[][20],/*in*/ int row)
{
    int accum = 0;

    for (int col = 0; col < 20; col++)
    {
        if (bacteriaArray[row][col] == '*')
        {
            accum++;
        }
    }
    return accum;
}


/* ************************************************** */
/*                                                    */
/*  This function counts the number of bacteria in    */
/*  a particular column                               */
/*                                                    */
/* ************************************************** */
int countBactArrayCol(/*in*/ const char bacteriaArray[][20],/*in*/ int col)
{
    int accum = 0;

    for (int row = 0; row < 20; row++)
    {
        if (bacteriaArray[row][col] == '*')
        {
            accum++;
        }
    }
    return accum;
}



/* ************************************************** */
/*                                                    */
/*   This function displays the various statistics    */
/*   required for demonstration of the program        */
/*                                                    */
/* ************************************************** */
void displayBactArrayStats(/*inout*/ const char bacteriaArray[][20])
{
    int accumLive = 0;

    cout << endl;
    cout << "Total alive in row 10 = " << countBactArrayRow(bacteriaArray,10) << endl;
    cout << "Total alive in col 10 = " << countBactArrayCol(bacteriaArray,10) << endl;
    cout << "Total dead in row 16 = " << 20 - countBactArrayRow(bacteriaArray,16) << endl;
    cout << "Total dead in col 1  = " << 20 - countBactArrayCol(bacteriaArray,1)  << endl;

    for (int col = 0; col < 20; col++)
    {
        accumLive += countBactArrayRow(bacteriaArray,col);
    }

    cout << "Total alive  = " << accumLive << endl;
    cout << "Total dead   = " << 400 - accumLive << endl;
    cout << endl << endl;

}


/* ************************************************** */
/*                                                    */
/*   This function scans the array by row and column, */
/*   and whenever there is a living bacteria in an    */
/*   element it calls the function                    */
/*   updateNeighborCount() which updates the count    */
/*   of neighboring bacteria in a temporary array     */
/*                                                    */
/*   Next, the temporary array is scanned to determine*/
/*   which of the life/death criteria applies to the  */
/*   current cell, and the value of the cell is       */
/*   updated with either a live or dead cell.         */
/* ************************************************** */
void nextGenBactArray(/*inout*/ char bacteriaArray[][20])
{
    int neighbors[20][20] = {0};

    for (int row = 0; row < 20; row ++)
    {
        for (int col = 0; col < 20; col++)
        {
             if (bacteriaArray[row][col] == '*')
             {
                 updateNeighborCount(bacteriaArray, neighbors, row, col);
             }
        }
    }

    for (int row = 0; row < 20; row ++)
    {
        for (int col = 0; col < 20; col++)
        {
            if (bacteriaArray[row][col] != '*')  //dead
            {
                if (neighbors[row][col] == 3)
                {
                    bacteriaArray[row][col] = '*';
                }
            }
            else  // living
            {
                if (neighbors[row][col] < 2 || neighbors[row][col] > 3)
                {
                    bacteriaArray[row][col] = ' ';
                }
            }
        }
    }
}


/* ************************************************** */
/*                                                    */
/*   This function is called when there is a live     */
/*   bacteria in a cell, and updates the count of     */
/*   count of cells for each of the neighboring cells */
/*                                                    */
/* ************************************************** */
void updateNeighborCount(/*in*/const char bacteriaArray[][20],
                         /*inout*/int neighbors[][20],
                         /*in*/int row,
                         /*in*/ int col)
{
    int rowStart = -1;
    int colStart = -1;
    int rowEnd   = 1;
    int colEnd   = 1;

    if (col == 0)
        colStart = 0;

    if (col == 19)
        colEnd = 0;

    if (row == 0)
        rowStart = 0;

    if (row == 19)
        rowEnd = 0;

    for (int r = rowStart; r <= rowEnd; r++)
    {
        for (int c = colStart; c <= colEnd; c++)
        {
            if (r != 0 || c != 0)
            {
                neighbors[row+r][col+c] += 1;
            }
        }
    }
}


