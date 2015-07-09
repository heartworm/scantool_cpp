#include "KeystoneProcessor.h"

void KeystoneProcessor::process(cv::Mat &src, cv::Mat &dst, Corners c) {
	using namespace cv;
	double width = max(magnitude(corners.tl, corners.tr), magnitude(corners.bl, corners.br));
	double height = max(magnitude(corners.tl, corners.bl), magnitude(corners.tr, corners.br));
	Point2f cnrs[] = { corners.tl, corners.tr, corners.br, corners.bl };
	Point2f dsts[] = { Point2f(0, 0), Point2f(width, 0), Point2f(width, height), Point2f(0, height) };
	Mat transform = getPerspectiveTransform(cnrs, dsts);
	warpPerspective(m, d, transform, Size(width, height));
}

double KeystoneProcessor::magnitude(cv::Point2f a, cv::Point2f b) { //pythag
	double dx2 = (b.x - a.x) * (b.x - a.x);
	double dy2 = (b.y - a.y) * (b.y - a.y);
	return sqrt(dx2 + dy2);
}