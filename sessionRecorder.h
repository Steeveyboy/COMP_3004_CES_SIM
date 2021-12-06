#ifndef SESSIONRECORDER_H
#define SESSIONRECORDER_H

#include <iostream>
#include <string>
#include <vector>
#include "record.h"
#include <fstream>

class sessionRecorder {


	private:
		int numRecords;
		std::vector<record*> records;
        std::string filepath = "/home/student/CES-Simulation/COMP_3004_CES_SIM/records.txt";
		std::string date; //possibly an ENUM
		void storeRecords();
		void initRecords();
		void printRecords();

	public:
		sessionRecorder();
		~sessionRecorder();
		std::vector<record*> getHistory();
		void deleteRecord(int);
        void makeRecord(std::string, std::string, int, std::string, std::string);

};

#endif
