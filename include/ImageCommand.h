/*
 * ImageCommand.h
 *
 *  Created on: 17 Apr 2015
 *      Author: Shravan
 */

#ifndef IMAGECOMMAND_H_
#define IMAGECOMMAND_H_

#include <math.h>
#include "ppapi/cpp/var.h"
#include "ppapi/cpp/var_array_buffer.h"
#include "ppapi/cpp/var_dictionary.h"
#include "opencv2/core/core.hpp"
#include "InvalidCmdException.h"
#include "CornerFinder.h"
#include "Corners.h"
#include "KeystoneProcessor.h"

using string = std::string;

class ImageCommand {
public:
	ImageCommand(pp::VarDictionary message);

	pp::VarDictionary getOutput();

private:
	static Preferences prefs;

	int32_t number;
	int32_t id;
	cv::Mat image;
	string command;
	Corners corners;
};

#endif /* IMAGECOMMAND_H_ */
