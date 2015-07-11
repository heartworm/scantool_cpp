#include "KeystoneProcessor.h"

cv::Mat KeystoneProcessor::process(cv::Mat &src, Corners corners) {
	using namespace cv;
	double width = max(magnitude(corners.tl, corners.tr), magnitude(corners.bl, corners.br));
	double height = max(magnitude(corners.tl, corners.bl), magnitude(corners.tr, corners.br));
	Mat dst(height, width, src.type());
	Point2f cnrs[] = { corners.tl, corners.tr, corners.br, corners.bl };
	Point2f dsts[] = { Point2f(0, 0), Point2f(width, 0), Point2f(width, height), Point2f(0, height) };
	Mat transform = getPerspectiveTransform(cnrs, dsts);
	warpPerspective(src, dst, transform, Size(width, height));
	return dst;
}

double KeystoneProcessor::magnitude(cv::Point2f a, cv::Point2f b) { //pythag
	double dx2 = (b.x - a.x) * (b.x - a.x);
	double dy2 = (b.y - a.y) * (b.y - a.y);
	return sqrt(dx2 + dy2);
}