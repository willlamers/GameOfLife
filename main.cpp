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
void getNextGen(const char[][20], int[][20], int, int);
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
bool openFile (/*inout*/ifstream &inputFile, string fileName)
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
/*  This function reads the file, and initializes the */
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



void displayBactArray(const char bacteriaArray[][20])
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



int countBactArrayRow(const char bacteriaArray[][20], int row)
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



int countBactArrayCol(const char bacteriaArray[][20], int col)
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




void displayBactArrayStats(const char bacteriaArray[][20])
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


void nextGenBactArray(char bacteriaArray[][20])
{
    int neighbors[20][20] = {0};

    for (int row = 0; row < 20; row ++)
    {
        for (int col = 0; col < 20; col++)
        {
             getNextGen(bacteriaArray, neighbors, row, col);
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


void getNextGen(const char bacteriaArray[][20], int neighbors[][20], int row, int col)
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
            if ((bacteriaArray[row+r][col+c] == '*') && (r != 0 || c != 0))
            {
                neighbors[row][col] += 1;
            }
        }
    }
}


