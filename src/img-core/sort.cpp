#include "PhotoCollection.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace imgcore;
using namespace std;

int main(int argc, char **argv)
{
    // The application expects a list of image paths to be received as parameters.
    PhotoCollection collection((argc - 1), &(argv[1]));

    vector<string> sortedPhotoNames = collection.similaritySort();

    // Print ordered list of pictures.
    const char *outFileName = "order.txt";
    ofstream outFile;
    outFile.open(outFileName);

    for (vector<string>::iterator photoName = sortedPhotoNames.begin(); photoName !=
            sortedPhotoNames.end(); ++photoName)
        outFile << *photoName << endl;

    outFile.close();

    return 0;
}
