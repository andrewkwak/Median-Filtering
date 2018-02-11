#include <iostream>
#include <fstream>
#include <climits>

class Median {
public:
    Median(int nR, int nC, int min, int max);
    ~Median();
    void mirrorFramed();
    void loadImage(std::istream& in);
    void outputFile(std::ostream& out);
    void loadNeighbors(int r, int c);
    int selectionSort(int a[]);
    

private:
    int numRows, numCols, minVal, maxVal, newMin, newMax;
    int **mirrorFramedAry;
    int neighborAry[9];
    int **tempAry;
};

Median::Median(int nR, int nC, int min, int max) : 
    numRows(nR),
    numCols(nC),
    minVal(min),
    maxVal(max),
    newMin(INT_MAX),
    newMax(INT_MIN)
{
    mirrorFramedAry = new int*[numRows+2];
    tempAry = new int*[numRows+2];
    for (int i = 0; i < numRows+2; i++) {
        mirrorFramedAry[i] = new int[numCols+2];
        tempAry[i] = new int[numCols+2];
    }

}

Median::~Median() {}

void Median::loadImage(std::istream& in) {
    int pixel_val;
    for (int i = 1; i < numRows+1; i++) {
        for (int j = 1; j < numCols+1; j++) {
            in >> pixel_val;
            mirrorFramedAry[i][j] = pixel_val;
        }
    }
}

void Median::loadNeighbors(int r, int c) {
    neighborAry[0] = mirrorFramedAry[r-1][c-1];
    neighborAry[1] = mirrorFramedAry[r-1][c];
    neighborAry[2] = mirrorFramedAry[r-1][c+1];
    neighborAry[3] = mirrorFramedAry[r][c-1];
    neighborAry[4] = mirrorFramedAry[r][c];
    neighborAry[5] = mirrorFramedAry[r][c+1];
    neighborAry[6] = mirrorFramedAry[r+1][c-1];
    neighborAry[7] = mirrorFramedAry[r+1][c];
    neighborAry[8] = mirrorFramedAry[r+1][c+1];
}

int Median::selectionSort(int a[]) {
    int min;
    for (int i = 0; i <= 9/2; i++) {
        min = i;
        for (int j = i+1; j < 9; j++) {
            if (a[j] < a[min]) min = j;
        }
        std::swap(a[min], a[i]);
    }
    return a[9/2];
}

void Median::mirrorFramed() {
    for (int i = 1; i < numRows+1; i++) {
        for (int j = 1; j < numCols+1; j++) {
            loadNeighbors(i, j);
            tempAry[i][j] = selectionSort(neighborAry);
            if (newMin > tempAry[i][j]) newMin = tempAry[i][j];
            if (newMax < tempAry[i][j]) newMax = tempAry[i][j];
        }
    }
}

void Median::outputFile(std::ostream& out) {
    out << numRows << ' ' << numCols << ' ' << newMin << ' ' << newMax << '\n';
    for (int i = 1; i < numRows+1; i++) {
        for (int j = 1; j < numCols+1; j++) {
            out << tempAry[i][j] << ' ';
        }
        out << '\n';
    }
}

int main(int argc, char **argv) {

    if (argc != 3) {
        std::cout << "Error.  Input file not entered.\n";
        std::exit(EXIT_FAILURE);
    }
    std::ifstream inFile (argv[1]);
    std::ofstream outFile (argv[2]);

    int numRows, numCols, minVal, maxVal;
    inFile >> numRows >> numCols >> minVal >> maxVal;

    Median m(numRows, numCols, minVal, maxVal);

    m.loadImage(inFile);
    m.mirrorFramed();
    m.outputFile(outFile);
    
    inFile.close();
    outFile.close();

    return 0;
}
