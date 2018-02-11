#pragma once
#include <fstream>

class Median
{
  public:
    Median(int nR, int nC, int min, int max);
    ~Median();
    void mirrorFramed();
    void loadImage(std::istream &in);
    void outputFile(std::ostream &out);
    void loadNeighbors(int r, int c);
    int selectionSort(int a[]);

  private:
    int numRows, numCols, minVal, maxVal, newMin, newMax;
    int **mirrorFramedAry;
    int neighborAry[9];
    int **tempAry;
};