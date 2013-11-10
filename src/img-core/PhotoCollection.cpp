#include <stdio.h>
#include <iostream>
#include <limits>
#include "PhotoCollection.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;
using namespace imgcore;

PhotoCollection::PhotoCollection(int numFiles, char **fileNames)
{
    // All images are initialized as gray-scale.
    for (int i = 0; i < numFiles; i++) {
        photoNames.push_back(fileNames[i]);
        grayScalePhotos.push_back(imread(fileNames[i], IMREAD_GRAYSCALE));

        Mat src, hsv;
        src = imread(fileNames[i], 1);
        cvtColor(src, hsv, COLOR_BGR2HSV);
        hsvPhotos.push_back(hsv);
    }
}

vector<string>
PhotoCollection::similaritySort()
{
    extractFeatureDescriptors();
    computeNumFPMatches();

    vector<int> sorted;
    int currentIdx = 0;
    sorted.push_back(currentIdx);

    // Greedly sort the images by number of matching point.
    while (sorted.size() < grayScalePhotos.size()) {
        int max = 0;
        int maxIdx;

        for (int i = 0; i < grayScalePhotos.size(); i++)
            if (numFPMatches[currentIdx][i] > max &&
                std::find(sorted.begin(), sorted.end(), i) == sorted.end()) {
                max = numFPMatches[currentIdx][i];
                maxIdx = i;
            }

        currentIdx = maxIdx;
        sorted.push_back(currentIdx);
    }

    vector<string> sortedNames;
    for (int i = 0; i < sorted.size(); i++)
        sortedNames.push_back(photoNames[sorted[i]]);

    return sortedNames;
}

vector<string>
PhotoCollection::colorSort()
{
    computeHistDistances();

    vector<int> sorted;
    int currentIdx = 0;
    sorted.push_back(currentIdx);

    // Greedly sort the images by histogram distance.
    while (sorted.size() < hsvPhotos.size()) {
        double min = numeric_limits<double>::max();
        int minIdx;

        for (int i = 0; i < hsvPhotos.size(); i++)
            if (histDistances[currentIdx][i] < min &&
                std::find(sorted.begin(), sorted.end(), i) == sorted.end()) {
                min = histDistances[currentIdx][i];
                minIdx = i;
            }

        currentIdx = minIdx;
        sorted.push_back(currentIdx);
    }

    vector<string> sortedNames;
    for (int i = 0; i < sorted.size(); i++)
        sortedNames.push_back(photoNames[sorted[i]]);

    return sortedNames;
}

void
PhotoCollection::extractFeatureDescriptors()
{
    for (vector<Mat>::iterator photo = grayScalePhotos.begin(); photo != grayScalePhotos.end(); photo++) {
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
    vector<int> line(grayScalePhotos.size());
    for (int i = 0; i < grayScalePhotos.size(); i++) {
        numFPMatches.push_back(line);
    }

    // Compute the matches between every pair of images.
    for (int i = 0; i < grayScalePhotos.size(); i++) {
        for (int j = (i+1); j < grayScalePhotos.size(); j++) {
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
    for (int i = 0; i < grayScalePhotos.size(); i++)
        for (int j = 0; j < i; j++)
            numFPMatches[i][j] = numFPMatches[j][i];

    // When comparing an image to itself, all points match.
    for (int i = 0; i < grayScalePhotos.size(); i++) {
        numFPMatches[i][i] = featureDescriptors[i].rows;
    }
}

Mat
PhotoCollection::clusterize()
{
    // Build the features matrix.
    Mat features = cvCreateMat(grayScalePhotos.size(), grayScalePhotos.size(), CV_32F);
    for (int i = 0; i < grayScalePhotos.size(); i++) {
        for (int j = 0; j < grayScalePhotos.size(); j++) {
            features.at<double>(i, j) = numFPMatches[i][j];
        }
    }

    Mat labels;
    TermCriteria term(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10, 1.0);

    kmeans(features, numClusters(), labels, term, 3, KMEANS_PP_CENTERS);

    return labels;
}

int
PhotoCollection::numClusters()
{
    // ~ Heuristics ~
    if (grayScalePhotos.size() < 5)
        return 1;

    return (grayScalePhotos.size() / 3);
}

void
PhotoCollection::computeHistDistances()
{
    // Using 30 bins for hue and 32 for saturation.
    int hBins = 50;
    int sBins = 60;
    int histSize[] = {hBins, sBins};

    // Hue varies from 0 to 256, saturation from 0 to 180.
    float sRanges[] = {0, 256};
    float hRanges[] = {0, 180};
    const float* ranges[] = {hRanges, sRanges};
    int channels[] = {0, 1};

    // Initialize the distance matrix.
    vector<double> line(hsvPhotos.size());
    for (int i = 0; i < hsvPhotos.size(); i++) {
        histDistances.push_back(line);
    }

    // Compute the distance between every pair of images.
    for (int i = 0; i < hsvPhotos.size(); i++) {
        MatND histBase;
        calcHist(&(hsvPhotos[i]), 1, channels, Mat(), histBase, 2, histSize, ranges, true, false);
        normalize(histBase, histBase, 0, 1, NORM_MINMAX, -1, Mat());

        for (int j = i; j < hsvPhotos.size(); j++) {
            MatND histCurrent;
            calcHist(&(hsvPhotos[j]), 1, channels, Mat(), histCurrent, 2, histSize, ranges, true, false);
            normalize(histCurrent, histCurrent, 0, 1, NORM_MINMAX, -1, Mat());
            histDistances[i][j] = compareHist(histBase, histCurrent, 1);

        }
    }

    // Complete the lower triagular part of the matrix with numbers already computed.
    for (int i = 0; i < hsvPhotos.size(); i++)
        for (int j = 0; j < i; j++)
            histDistances[i][j] = histDistances[j][i];
}
