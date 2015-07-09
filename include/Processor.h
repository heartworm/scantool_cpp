/*
 * Processor.h
 *
 *  Created on: 17 Apr 2015
 *      Author: Shravan
 */

#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include <queue>
#include <thread>
#include <chrono>
#include "ppapi/cpp/var_dictionary.h"
#include "ppapi/cpp/instance.h"
#include "ImageCommand.h"
#include "InvalidCmdException.h"


class Processor {
public:
	static void tryToStop();
	static void addMessage(pp::VarDictionary message);
	static void run(pp::Instance *instance);
private:
	static bool isRunning;
	static std::queue<pp::VarDictionary> queue;
};

#endif /* PROCESSOR_H_ */
