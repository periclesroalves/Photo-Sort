#include <stdio.h>
#include "PhotoCollection.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"

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
    extractFeatureDescriptors();









    return photoNames;
}

void
PhotoCollection::extractFeatureDescriptors()
{
    for (vector<Mat>::iterator photo = photos.begin(); photo != photos.end(); photo++) {
        // Compute SIFT feature keypoints.
        SiftFeatureDetector detector;
        vector<KeyPoint> keypoints;
        detector.detect(*photo, keypoints);

        // Compute feature point descriptors.
        SiftDescriptorExtractor extractor;
        Mat descriptors;
        extractor.compute(*photo, keypoints, descriptors);

        featureDescriptors.push_back(descriptors);
    }
}
