/*
 * Preferences.cpp
 *
 *  Created on: 17 Apr 2015
 *      Author: Shravan
 */

#include "Preferences.h"

Preferences::Preferences() {
	prefs[Options::RHO_VAL_NO] = 250;
	prefs[Options::THETA_RESOLUTION] = CV_PI / 180.0;
	prefs[Options::MIN_LINE_LENGTH_FRAC] = 30;
	prefs[Options::MEDIAN_BLUR_SIZE] = 7.0;
	prefs[Options::MIN_ANGLE] = CV_PI / 32.0;
	prefs[Options::MORPH_GRADIENT_SIZE] = 3.0;
	prefs[Options::VOTE_THRESHOLD] = 100;
	prefs[Options::CLUSTER_BOUND] = 200;
}

Preferences::~Preferences() {
}

void Preferences::set(Options k, double v) {
	prefs[k] = v;
}

double Preferences::get(Options k) {
	return prefs[k];
}
