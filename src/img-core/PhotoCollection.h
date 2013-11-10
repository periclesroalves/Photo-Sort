#ifndef imgcore_photocollection_h__
#define imgcore_photocollection_h__

#include <vector>
#include "opencv2/core/core.hpp"

namespace imgcore {

class PhotoCollection
{
    std::vector<cv::Mat> photos;
    std::vector<std::string> photoNames;
    std::vector<cv::Mat> featureDescriptors;
    std::vector<std::vector<int> > numFPMatches;

  public:
    // Builds a colletion from a list of picture file names.
    PhotoCollection(int numFiles, char **fileNames);

    // Returns the photo file names in similarity order.
    std::vector<std::string> similaritySort();

    // Extracts SIFT feaure point descriptors for each image.
    void extractFeatureDescriptors();

    // Computes the number of matching feature points between every pair of photos.
    void computeNumFPMatches();

    // Uses kmeans to clusterize similar images.
    void clusterize();
};

} // namespace imgcore

#endif // imgcore_photocollection_h__
