#include <stdio.h>
#include "PhotoCollection.h"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;
using namespace imgcore;

PhotoCollection::PhotoCollection(int numFiles, char **fileNames)
{
    // All images are initialized as gray-scale.
    for (int i = 0; i < numFiles; i++) {
        photoNames.push_back(fileNames[i]);
        photos.push_back(imread(fileNames[i], IMREAD_GRAYSCALE));
    }
}

vector<string>
PhotoCollection::similaritySort()
{
    return photoNames;
}
