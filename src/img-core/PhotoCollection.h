#ifndef imgcore_photocollection_h__
#define imgcore_photocollection_h__

#include <vector>
#include "opencv2/core/core.hpp"

namespace imgcore {

class PhotoCollection
{
    std::vector<cv::Mat> grayScalePhotos;
    std::vector<cv::Mat> hsvPhotos; 
    std::vector<std::string> photoNames;
    std::vector<cv::Mat> featureDescriptors;
    std::vector<std::vector<int> > numFPMatches;

  public:
    // Builds a colletion from a list of picture file names.
    PhotoCollection(int numFiles, char **fileNames);

    // Returns the photo file names in similarity order.
    std::vector<std::string> similaritySort();

    // Returns the photo file names in color order.
    std::vector<std::string> colorSort();

    // Extracts SIFT feaure point descriptors for each image.
    void extractFeatureDescriptors();

    // Computes the number of matching feature points between every pair of photos.
    void computeNumFPMatches();

    // Uses kmeans to clusterize similar images.
    cv::Mat clusterize();

    int numClusters();
};

} // namespace imgcore

#endif // imgcore_photocollection_h__
