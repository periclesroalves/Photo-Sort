#include "PhotoCollection.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace imgcore;
using namespace std;

int main(int argc, char **argv)
{
    // The application expects a list of image paths as input parameters.
    PhotoCollection collection((argc - 2), &(argv[2]));

    vector<string> sortedPhotoNames;
    
    if (argv[1][0] == 'c')
        collection.colorSort();
    else if(argv[1][0] == 'o')
        collection.similaritySort();

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
