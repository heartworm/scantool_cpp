/*
 * InvalidCmdException.h
 *
 *  Created on: 17 Apr 2015
 *      Author: Shravan
 */

#ifndef INVALIDCMDEXCEPTION_H_
#define INVALIDCMDEXCEPTION_H_

class InvalidCmdException : public std::runtime_error {
public:
	InvalidCmdException(const std::string& msg) : runtime_error(msg) {};
	InvalidCmdException(const char* msg) : runtime_error(msg) {};
};

#endif /* INVALIDCMDEXCEPTION_H_ */
