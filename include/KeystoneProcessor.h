#ifndef KEYSTONEPROCESSOR_H
#define KEYSTONEPROCESSOR_H

#include <opencv2/imgproc/imgproc.hpp>
#include "Corners.h"

class KeystoneProcessor {
public:
	static cv::Mat process(cv::Mat &src, Corners corners);
private:
	static double magnitude(cv::Point2f a, cv::Point2f b);
};

#endif /* KEYSTONEPROCESSOR_H */