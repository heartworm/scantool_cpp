/*
 * Corners.h
 *
 *  Created on: 17 Apr 2015
 *      Author: Shravan
 */

#ifndef CORNERS_H_
#define CORNERS_H_

#include "opencv2/core/core.hpp"
#include "ppapi/cpp/var.h"
#include "ppapi/cpp/var_dictionary.h"
#include "InvalidCmdException.h"

struct Corners {
	Corners();
	Corners(pp::VarDictionary dict);

	cv::Point2f tl;
	cv::Point2f tr;
	cv::Point2f bl;
	cv::Point2f br;

	void setToDefault(cv::Mat &m);
	pp::VarDictionary getAsVar();
};

#endif /* CORNERS_H_ */
