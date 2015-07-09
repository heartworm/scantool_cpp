/*
 * Processor.cpp
 *
 *  Created on: 17 Apr 2015
 *      Author: Shravan
 */

#include "Processor.h"

//static member initialisation
bool Processor::isRunning = false;
std::queue<pp::VarDictionary> Processor::queue;

void Processor::run(pp::Instance *instance) { //in c++ "this" is a pointer, shouldn't need to delete it.
	instance->PostMessage("Thread's running!");
	isRunning = true;
	while (isRunning) {
		while (!queue.empty()) {
			instance->PostMessage("Processor got a job");
			try {
				pp::VarDictionary item = queue.front();
				queue.pop();
				ImageCommand cmd(item);
				instance->PostMessage(cmd.getOutput());
			} catch (const InvalidCmdException &e) {
				pp::VarDictionary err;
				err.Set("command", "error");
				err.Set("type", "InvalidCmdException");
				err.Set("what", e.what());
				instance->PostMessage(err);
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	isRunning = false;
}

void Processor::tryToStop() {
	isRunning = false;
}

void Processor::addMessage(pp::VarDictionary message) {
	queue.push(message);
}
