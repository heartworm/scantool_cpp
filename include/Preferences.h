/*
 * Preferences.h
 *
 *  Created on: 17 Apr 2015
 *      Author: Shravan
 */

#ifndef PREFERENCES_H_
#define PREFERENCES_H_

#include <map>
#include "opencv2/core/core.hpp"
#include "Options.h"

class Preferences {
public:
	Preferences();
	~Preferences();

	void set(Options k, double v);
	double get(Options k);
private:
	std::map < Options, double > prefs;
};


#endif /* PREFERENCES_H_ */
