/*
 * Options.h
 *
 *  Created on: 17 Apr 2015
 *      Author: Shravan
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

enum class Options {
	//Outputter
	SAVE_LOCATION,

	//Corner Finder
	RHO_VAL_NO,
	THETA_RESOLUTION,
	MIN_LINE_LENGTH_FRAC,
	MAX_LINE_GAP_FRAC,
	VOTE_THRESHOLD,
	MEDIAN_BLUR_SIZE,
	MORPH_GRADIENT_SIZE,
	MIN_ANGLE,
	CLUSTER_BOUND,

	//Colour
	COLOUR_MODE,
	COLOUR_THRESH

};

#endif /* OPTIONS_H_ */
