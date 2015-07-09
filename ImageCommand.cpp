/*
 * ImageCommand.cpp
 *
 *  Created on: 17 Apr 2015
 *      Author: Shravan
 */

#include "ImageCommand.h"

Preferences ImageCommand::prefs; //initalise static members

ImageCommand::ImageCommand(pp::VarDictionary message) {
	int width = 0;
	int height = 0;
	
	//initialise command variable
	if (message.HasKey("command")) {
		if (!message.Get("command").is_string()) throw InvalidCmdException("Command key 'command' is not a string!");
		command = message.Get("command").AsString();
	} else throw InvalidCmdException("Command key 'command' doesn't exist!");
	
	//initialise all image properties into variables
	if (message.HasKey("image")) {
		if (!message.Get("image").is_dictionary()) throw InvalidCmdException("Command key 'image' is not a Dictionary/Object!");
		pp::VarDictionary imgDict(message.Get("image"));
		
		//initialise corners variable
		if (imgDict.HasKey("corners")) {
			if (!imgDict.Get("corners").is_dictionary()) throw InvalidCmdException("Command key 'command' is not a Dictionary/Object!");
			corners = Corners(pp::VarDictionary(imgDict.Get("corners")));
		} else throw InvalidCmdException("Command key 'corners' doesn't exist!");

		//initialise hash variable - changed to unique id
		if (imgDict.HasKey("id")) {
			if (imgDict.Get("id").is_double()) {
				id = round(imgDict.Get("id").AsDouble());
			} else if (imgDict.Get("id").is_int()) {
				id = imgDict.Get("id").AsInt();
			} else throw InvalidCmdException("Command key 'id' is not a number!");
		} else throw InvalidCmdException("Command key 'id' doesn't exist!");
		
		
		if (imgDict.HasKey("number")) {
			if (imgDict.Get("number").is_double()) {
				number = round(imgDict.Get("number").AsDouble());
			} else if (imgDict.Get("number").is_int()) {
				number = imgDict.Get("number").AsInt();
			} else throw InvalidCmdException("Command key 'number' is not a number!");
		} else throw InvalidCmdException("Command key 'number' doesn't exist!");
		
		if (imgDict.HasKey("width")) {
			if (imgDict.Get("width").is_double()) {
				width = round(imgDict.Get("width").AsDouble());
			} else if (imgDict.Get("width").is_int()) {
				width = imgDict.Get("width").AsInt();
			} else throw InvalidCmdException("Command key 'width' is not a number!");
		} else throw InvalidCmdException("Command key 'width' doesn't exist!");
		
		if (imgDict.HasKey("height")) {
			if (imgDict.Get("height").is_double()) {
				height = round(imgDict.Get("height").AsDouble());
			} else if (imgDict.Get("height").is_int()) {
				height = imgDict.Get("height").AsInt();
			} else throw InvalidCmdException("Command key 'height' is not a number!");
		} else throw InvalidCmdException("Command key 'height' doesn't exist!");
		
		
		if (imgDict.HasKey("data")) {
			if (!imgDict.Get("data").is_array_buffer()) throw InvalidCmdException("Command key 'data' is not an ArrayBuffer!");
				pp::VarArrayBuffer arrBuf(imgDict.Get("data"));
				void* data = arrBuf.Map(); //get pointer to start of contiguous bytes (array);
				//If the pp::VarDictionary goes completely out of scope, array will likely be deallocated!
				image = cv::Mat(height, width, CV_8UC4, data); //accepts rows, cols instead of width, height
				//ArrayBuffer from HTML5 Canvas is RGBA, so 4 channels, 8bit unsigned each
		} else throw InvalidCmdException("Command key 'data' doesn't exist!");				
		
	} else throw InvalidCmdException("Command key 'image' doesn't exist!");
}

/* ImageCommand::ImageCommand(pp::VarDictionary message) {
	int width = 0;
	int height = 0;
	
	
	if (!message.HasKey("command")) {
		
	}


	if (!message.Get("command").is_string()) throw InvalidCmdException("Command key 'command' is not a string!");
	if (!message.Get("image").is_dictionary()) throw InvalidCmdException("Command key 'image' is not a Dictionary/Object!");

	pp::VarDictionary imgDict(message.Get("image"));

	if (!imgDict.Get("corners").is_dictionary()) throw InvalidCmdException("Command key 'command' is not a Dictionary/Object!");
	if (!imgDict.Get("hash").is_string()) throw InvalidCmdException("Command key 'uid' is not a string!");
	if (!imgDict.Get("data").is_array_buffer()) throw InvalidCmdException("Command key 'data' is not an ArrayBuffer!");

	if (imgDict.Get("number").is_double()) {
		number = round(imgDict.Get("number").AsDouble());
	} else if (imgDict.Get("number").is_int()) {
		number = imgDict.Get("number").AsInt();
	} else throw InvalidCmdException("Command key 'number' is not a number!");

	if (imgDict.Get("width").is_double()) {
		width = round(imgDict.Get("width").AsDouble());
	} else if (imgDict.Get("width").is_int()) {
		width = imgDict.Get("width").AsInt();
	} else throw InvalidCmdException("Command key 'width' is not a width!");

	if (imgDict.Get("height").is_double()) {
		height = round(imgDict.Get("height").AsDouble());
	} else if (imgDict.Get("height").is_int()) {
		height = imgDict.Get("height").AsInt();
	} else throw InvalidCmdException("Command key 'height' is not a height!");

	corners = Corners(pp::VarDictionary(imgDict.Get("corners")));
	command = imgDict.Get("command").AsString();
	hash = imgDict.Get("hash").AsString();

	pp::VarArrayBuffer arrBuf(imgDict.Get("data"));
	void* data = arrBuf.Map(); //get pointer to start of contiguous bytes (array);
	//If the pp::VarDictionary goes completely out of scope, array will likely be deallocated!
	image = cv::Mat(height, width, CV_8UC4, data); //accepts rows, cols instead of width, height
	//ArrayBuffer from HTML5 Canvas is RGBA, so 4 channels, 8bit unsigned each
}
 */
pp::VarDictionary ImageCommand::getOutput() {
	if (command == "corners") {
		try {
			corners = CornerFinder::findCorners(image, prefs);

			pp::VarDictionary imgDict;
			imgDict.Set("number", number);
			imgDict.Set("id", id);
			imgDict.Set("cornersStatus", "SUCCESS");
			imgDict.Set("corners", corners.getAsVar());

			pp::VarDictionary dict;
			dict.Set("command", "update");
			dict.Set("image", imgDict);

			return dict;

		} catch (CornerFinder::CornersNotFoundException &e) {
			pp::VarDictionary imgDict;
			imgDict.Set("number", number);
			imgDict.Set("id", id);
			imgDict.Set("cornersStatus", "FAILED");
			imgDict.Set("cornersErr", e.what());

			pp::VarDictionary dict;
			dict.Set("command", "update");
			dict.Set("image", imgDict);
			
			return dict;
		}
	} else throw InvalidCmdException("Command key 'command' doesn't make sense: " + command);
	return pp::VarDictionary(); //silence the warning.
}


