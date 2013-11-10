#include <stdio.h>
#include <iostream>
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
    computeNumFPMatches();
    clusterize();










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

void
PhotoCollection::computeNumFPMatches()
{
    const float loweRatio = 0.7;
    BFMatcher matcher;

    // Initialize the match counter matrix.
    vector<int> line(photos.size());
    for (int i = 0; i < photos.size(); i++) {
        numFPMatches.push_back(line);
    }

    // Compute the matches between every pair of images.
    for (int i = 0; i < photos.size(); i++) {
        for (int j = (i+1); j < photos.size(); j++) {
            vector<vector<DMatch> > matches;
            matcher.knnMatch(featureDescriptors[i], featureDescriptors[j], matches, 2);  // Find two nearest matches

            // Filter good matches, using Lowe's technique.
            vector<DMatch> goodMatches;
            for (int k = 0; k < matches.size(); k++)
            {
                if (matches[k][0].distance < loweRatio * matches[k][1].distance)
                {
                    goodMatches.push_back(matches[i][0]);
                }
            }

            numFPMatches[i][j] = goodMatches.size();
        }
    }

    // Complete the lower triagular part of the matrix with numbers already computed.
    for (int i = 0; i < photos.size(); i++)
        for (int j = 0; j < i; j++)
            numFPMatches[i][j] = numFPMatches[j][i];

    // Make the diagonal equals the average of the numbers in the column, trying to reduce any noise.
    for (int i = 0; i < photos.size(); i++) {
        int sum = 0;
        for (int j = 0; j < photos.size(); j++)
            if (i != j)
                sum += numFPMatches[i][j];

        numFPMatches[i][i] = sum / (photos.size() - 1);
    }
}

Mat
PhotoCollection::clusterize()
{
    // Build the features matrix.
    Mat features = cvCreateMat(photos.size(), photos.size(), CV_32F);
    for (int i = 0; i < photos.size(); i++) {
        for (int j = 0; j < photos.size(); j++) {
            features.at<double>(i, j) = numFPMatches[i][j];
        }
    }

    Mat labels;
    TermCriteria term(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10, 1.0);  
    int numClusters = photos.size() / 3;

    if (photos.size() < 5)
        numClusters = 1;

    kmeans(features, numClusters, labels, term, 3, KMEANS_PP_CENTERS);

    return labels;
}
