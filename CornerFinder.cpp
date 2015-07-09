/*
 * CornerFinder.cpp
 *
 *  Created on: 17 Apr 2015
 *      Author: Shravan
 */

#include "CornerFinder.h"

Corners CornerFinder::findCorners(cv::Mat m, Preferences prefs) {
	using namespace cv;
	Mat gray;
	cvtColor(m, gray, CV_BGR2GRAY);
	medianBlur(gray, gray, prefs.get(Options::MEDIAN_BLUR_SIZE));

	double morphSize = prefs.get(Options::MORPH_GRADIENT_SIZE);
	Mat morphKernel = getStructuringElement(CV_SHAPE_RECT, Size(morphSize, morphSize));
	morphologyEx(gray, gray, MORPH_GRADIENT, morphKernel);

	Mat thresh;
	threshold(gray, thresh, 0, 255, THRESH_BINARY | THRESH_OTSU);

	vector<Vec4i> hLines;
	HoughLinesP(thresh, hLines, min(thresh.rows, thresh.cols) / prefs.get(Options::RHO_VAL_NO),
		prefs.get(Options::THETA_RESOLUTION), prefs.get(Options::VOTE_THRESHOLD),
		min(thresh.rows, thresh.cols) / prefs.get(Options::MIN_LINE_LENGTH_FRAC));

	if (hLines.size() < 4) throw CornersNotFoundException("HoughLinesP returned < 4 lines");

	vector<Point2f> intersections;
	for (Vec4i &lineA : hLines) {
		for (Vec4i &lineB : hLines) {
			if (&lineA != &lineB) {
				// direction vectors of lines
				int i1 = lineA[2] - lineA[0];
				int j1 = lineA[3] - lineA[1];

				int i2 = lineB[2] - lineB[0];
				int j2 = lineB[3] - lineB[1];

				//Line represented in Ax + By = C form (standard form)
				int a1 = j1; int a2 = j2;
				int b1 = -i1; int b2 = -i2;
				int	c1 = a1 * lineA[0] + b1 * lineA[1];
				int c2 = a2 * lineB[0] + b2 * lineB[1];

				//Find minor angle between lines
				double ang = std::abs(constrainAngle(angle(i1, j1, i2, j2)));
				int det = a1*b2 - a2*b1; //Square matrix determinant
				if (ang > prefs.get(Options::MIN_ANGLE) && det != 0) {
					//If lines arent parallel or coincident and form a significant minor angle
					float x = (b2 * c1 - b1 * c2) / det;
					float y = (a1 * c2 - a2 * c1) / det;
					if (x >= 0 && y >= 0 && x <= thresh.cols && y <= thresh.rows)
						//if intersection is within image (line intersections are calculated to infinity)
						intersections.push_back(Point2f(x, y)); //Add intersection of lines to list
				}
			}
		}
	}

	if (intersections.size() < 4) throw CornersNotFoundException("Number of Intersections was < 4");

	vector<Cluster> clusters;

	for (Point2f pnt : intersections) {
		bool success = false;
		for (Cluster &c : clusters) {
			success = c.join(pnt);
			if (success) break;
		}
		if (!success) {
			Cluster c(prefs.get(Options::CLUSTER_BOUND));
			c.join(pnt);
			clusters.push_back(c);
		}
	}

	if (clusters.size() < 4) throw CornersNotFoundException("Number of Clusters was < 4");

	std::sort(clusters.begin(), clusters.end(), [](Cluster a, Cluster b) { return a.size() > b.size(); });
	Point2f corners[] = { clusters[0].average(), clusters[1].average(), clusters[2].average(),
		clusters[3].average() };
	clockwiseSort(corners);

	Corners output;
	output.tl = corners[0]; output.tr = corners[1];
	output.bl = corners[3]; output.br = corners[2];

	return output;
}

bool CornerFinder::Cluster::inBounds(cv::Point2f p1, cv::Point2f p2) {
	float dx = std::abs(p2.x - p1.x);
	float dy = std::abs(p2.y - p1.y);
	return (dx <= bound) && (dy <= bound);
}

cv::Point2f CornerFinder::Cluster::average() {
	if (points.size() == 0) throw std::runtime_error("No points - Cluster::average()");
	float xAcc = 0;
	float yAcc = 0;
	for (cv::Point2f pnt : points) {
		xAcc += pnt.x;
		yAcc += pnt.y;
	}
	return cv::Point2f(xAcc / points.size(), yAcc / points.size());
}

int CornerFinder::Cluster::size() {
	return points.size();
}

bool CornerFinder::Cluster::join(cv::Point2f p) {
	if (points.empty()) { //if no points, push bank and return true
		points.push_back(p);
		return true;
	}
	for (cv::Point2f pnt : points) { //else if there are points, check if point belongs in cluster and return accordingly
		if (inBounds(pnt, p)) {
			points.push_back(p);
			return true;
		}
	}
	return false; //point outside of cluster
}

float CornerFinder::angle(int i1, int j1, int i2, int j2) {
	return acos(((i1 * i2) + (j1 * j2)) / (sqrt(i1 * i1 + j1 * j1)*sqrt(i2 * i2 + j2 * j2))); //tricky vector shit, look at Maths SL databook for ref
} 

float CornerFinder::constrainAngle(float x) { //Stright from SO. Constrains angle between 0 to 180 (returns minor arc angle)
	x = fmod(x + 180, 360);
	if (x < 0)
		x += 360;
	return x - 180;
}

//http://cdecl.org/ to translate declaration gibberish
void CornerFinder::clockwiseSort(cv::Point2f(&corners)[4]) { //TODO Need to find a better method that works on angles from center of points.
	std::sort(corners, corners + 4, [](cv::Point2f a, cv::Point2f b) { return a.y < b.y; });
	if (corners[0].x > corners[1].x) std::swap(corners[0], corners[1]);
	if (corners[2].x < corners[3].x) std::swap(corners[2], corners[3]);
}
