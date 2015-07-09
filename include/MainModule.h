/*
 * MainModule.h
 *
 *  Created on: 17 Apr 2015
 *      Author: Shravan
 */

#ifndef MAINMODULE_H_
#define MAINMODULE_H_

#include "ppapi/cpp/module.h"
#include "MainInstance.h"

class MainModule : public pp::Module {
public:
	explicit MainModule() : pp::Module() {}
	virtual ~MainModule() {}

	virtual pp::Instance* CreateInstance(PP_Instance instance);
};

#endif /* MAINMODULE_H_ */
