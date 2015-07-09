/*
 * MainInstance.h
 *
 *  Created on: 17 Apr 2015
 *      Author: Shravan
 */

#ifndef MAININSTANCE_H_
#define MAININSTANCE_H_

#include <ppapi/cpp/instance.h>
#include <thread>
#include "Processor.h"

class MainInstance: public pp::Instance {
public:
	explicit MainInstance(PP_Instance instance) : pp::Instance(instance) {
		//procThread = std::thread(Processor::run, this);
	}
	virtual ~MainInstance() {}

	virtual bool Init(uint32_t argc, const char* argn[], const char* argv[]);
	virtual void HandleMessage(const pp::Var &message);
private:
	//std::thread procThread;
};

#endif /* MAININSTANCE_H_ */
