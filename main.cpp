#include <iostream>
#include <fstream>
#include <climits>
#include "Median.h"

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
