/*
 * MainModule.cpp
 *
 *  Created on: 17 Apr 2015
 *      Author: Shravan
 */

#include "MainModule.h"

namespace pp {
	Module* CreateModule() {
		return new ::MainModule();
	}
}

pp::Instance* MainModule::CreateInstance(PP_Instance instance) {
	return new MainInstance(instance);
}
