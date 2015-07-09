/*
 * CornerFinder.h
 *
 *  Created on: 17 Apr 2015
 *      Author: Shravan
 */

#ifndef CORNERFINDER_H_
#define CORNERFINDER_H_

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "Corners.h"
#include "Preferences.h"

class CornerFinder {
public:
	static Corners findCorners(cv::Mat m, Preferences prefs);

	class CornersNotFoundException : public std::runtime_error {
	public:
		CornersNotFoundException(const std::string &msg) : runtime_error(msg) {};
		CornersNotFoundException(const char* msg) : runtime_error(msg) {};
	};

private:

	class Cluster {
	public:
		Cluster(const int b) : bound(b) {};
		~Cluster() {};

		cv::Point2f average();
		int size();
		bool join(cv::Point2f p);
	private:
		int bound;
		std::vector<cv::Point2f> points;
		bool inBounds(cv::Point2f p1, cv::Point2f p2);
	};

	static void clockwiseSort(cv::Point2f(&corners)[4]);
	static float angle(int i1, int j1, int i2, int j2);
	static float constrainAngle(float x);
};


#endif /* CORNERFINDER_H_ */
