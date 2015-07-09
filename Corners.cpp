/*
 * Corners.cpp
 *
 *  Created on: 17 Apr 2015
 *      Author: Shravan
 */

#include "Corners.h"

Corners::Corners() {
	tl = cv::Point2f(0, 0);
	tr = cv::Point2f(0, 0);
	bl = cv::Point2f(0, 0);
	br = cv::Point2f(0, 0);
}

Corners::Corners(pp::VarDictionary dict) {
	if (!dict.Get("tlx").is_number() || !dict.Get("tly").is_number() || !dict.Get("blx").is_number() || !dict.Get("bly").is_number() ||
			!dict.Get("trx").is_number() || !dict.Get("try").is_number() || !dict.Get("brx").is_number() || !dict.Get("bry").is_number()) {
		throw InvalidCmdException("One or more of the fields in command key 'corners' are not numbers!");
	}

	float TLX = dict.Get("tlx").is_double() ? dict.Get("tlx").AsDouble() : dict.Get("tlx").AsInt();
	float TLY = dict.Get("tly").is_double() ? dict.Get("tly").AsDouble() : dict.Get("tly").AsInt();
	float BLX = dict.Get("blx").is_double() ? dict.Get("blx").AsDouble() : dict.Get("blx").AsInt();
	float BLY = dict.Get("bly").is_double() ? dict.Get("bly").AsDouble() : dict.Get("bly").AsInt();
	float TRX = dict.Get("trx").is_double() ? dict.Get("trx").AsDouble() : dict.Get("trx").AsInt();
	float TRY = dict.Get("try").is_double() ? dict.Get("try").AsDouble() : dict.Get("try").AsInt();
	float BRX = dict.Get("brx").is_double() ? dict.Get("brx").AsDouble() : dict.Get("brx").AsInt();
	float BRY = dict.Get("bry").is_double() ? dict.Get("bry").AsDouble() : dict.Get("bry").AsInt();

	tl  = cv::Point2f(TLX, TLY);
	bl  = cv::Point2f(BLX, BLY);
	tr  = cv::Point2f(TRX, TRY);
	br  = cv::Point2f(BRX, BRY);
}

void Corners::setToDefault(cv::Mat &m) {
	tl = cv::Point2f(0, 0);
	tr = cv::Point2f(m.cols, 0);
	bl = cv::Point2f(0, m.rows);
	br = cv::Point2f(m.cols, m.rows);
}

pp::VarDictionary Corners::getAsVar() {
	pp::VarDictionary dict;
	dict.Set("tlx", round(tl.x));
	dict.Set("tly", round(tl.y));
	dict.Set("blx", round(bl.x));
	dict.Set("bly", round(bl.y));
	dict.Set("trx", round(tr.x));
	dict.Set("try", round(tr.y));
	dict.Set("brx", round(br.x));
	dict.Set("bry", round(br.y));
	return dict;
}

