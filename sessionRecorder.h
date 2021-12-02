#ifndef SESSIONRECORDER_H
#define SESSIONRECORDER_H

#include <iostream>
#include <string>
#include <vector>
#include "record.h"

class sessionRecorder {


	private:
		int numRecords;
		std::vector<record*> records;
		std::string filepath = "records.txt";
		std::string date; //possibly an ENUM

	public:
		sessionRecorder();
		void makeRecord(int, int, int);

};

#endif
