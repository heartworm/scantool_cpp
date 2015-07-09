/*
 * MainInstance.cpp
 *
 *  Created on: 17 Apr 2015
 *      Author: Shravan
 */

#include "MainInstance.h"

bool MainInstance::Init(uint32_t argc, const char* argn[], const char* argv[]) {
	//procThread = std::thread(Processor::run, this);
	return true;
}

void MainInstance::HandleMessage(const pp::Var &message) {
	if (message.is_dictionary()) {	
		PostMessage("Got a dictionary!");
		//Processor::addMessage();
		
		pp::VarDictionary item(message);
		try {
			ImageCommand cmd(item);
			PostMessage(cmd.getOutput());
		} catch (const InvalidCmdException &e) {
			pp::VarDictionary err;
			err.Set("command", "error");
			err.Set("type", "InvalidCmdException");
			err.Set("what", e.what());
			PostMessage(err);
		}
	} else PostMessage("Wasn't a dictionary");
}


