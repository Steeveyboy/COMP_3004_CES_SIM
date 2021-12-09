#ifndef SESSIONRECORDER_H
#define SESSIONRECORDER_H

#include <iostream>
#include <string>
#include <vector>
#include "record.h"
#include <fstream>
/* Class Purpose: stores sessions in a vector and reads into a text file
*/
class sessionRecorder {

	private:
        //Adjust the filepath to your system, to ensure records are stored.
        std::string filepath = "/home/student/CES-Simulation/COMP_3004_CES_SIM/records.txt";

		int numRecords;
		std::vector<record*> records;
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
