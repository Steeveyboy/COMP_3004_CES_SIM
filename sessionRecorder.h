#ifndef SESSIONRECORDER_H
#define SESSIONRECORDER_H

#include <iostream>
#include <string>
#include <vector>
#include "record.h"
#include <fstream>
/* Class Purpose: stores sessions in a vector and reads into a text file
 * Data Members:
 *      int numRecords;
        std::vector<record*> records;
        std::string filepath = "/home/student/CES-Simulation/COMP_3004_CES_SIM/records.txt";
        std::string date;
 *
 * Class Functions:
 *      void storeRecords();
        void initRecords();
        void printRecords();
        std::vector<record*> getHistory();
        void deleteRecord(int);
        void makeRecord(std::string, std::string, int, std::string, std::string);
 */
class sessionRecorder {

    private:
        //IMPORTANT: Please adjust the filepath to your records.txt absolute filepath, to ensure the records are stored.
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
