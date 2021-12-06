#include <iostream>
#include <string>
#include <vector>
#include "sessionRecorder.h"
#include "record.h"
using namespace std;

sessionRecorder::sessionRecorder() {
	numRecords = 0;
	initRecords();
}

void sessionRecorder::initRecords(){
	ifstream infile(filepath, ios::in);
	int freq, powerLev, duration, id;
	string date, wave;
	while(infile >> freq >> powerLev >> duration >> wave >> date >> id){
		record *r = new record(freq, powerLev, duration, wave, id, date);
		records.push_back(r);
	}
}

std::vector<record*> sessionRecorder::getHistory(){
	return records;
}

void sessionRecorder::deleteRecord(int searchId){
	int i;
	for(i=0; i<records.size(); i++){
		if(records[i]->id == searchId){
			records.erase(records.begin() + i);
		}
	}
	for(i; i<records.size(); i++){
		records[i]->id = records[i]->id -1;
	}
}

void sessionRecorder::printRecords(){
	record *r;
	for(int i=0; i<records.size(); i++){
		r = records[i];
		cout<<r->freq<<"	"<<r->powerLevel<<"	"<<r->date<<endl;
	}
}

void sessionRecorder::makeRecord(int fq, int pwr, int dur, string wave){
	//cout<<fq<<"	"<<pwr<<"	"<<dur<<"	"<<records.size()<<endl;
	record *rec = new record(fq, pwr, dur, wave, records.size(), "date");
	records.push_back(rec);
	cout<<records[records.size()-1]->freq<<endl;
	//storeRecords();
	numRecords++;
}

void sessionRecorder::storeRecords(){
	fstream fh;
	fh.open("records.txt");
	//fh.open("records.txt", ios::out | ios::trunc);
	record *r;
	for(int i=0; i<records.size(); i++){
		r = records[i];
		cout<<r->freq<<"	"<<r->powerLevel<<"	"<<r->duration<<"	"<<r->waveform<<"	Date"<<"	"<<r->id<<endl;
		fh<<r->freq<<"	"<<r->powerLevel<<"	"<<r->duration<<"	"<<r->waveform<<"	Date"<<"	"<<r->id<<endl;
	}
	fh.close();
}

sessionRecorder::~sessionRecorder(){
	storeRecords();
	//fh.close();
	cout<<records.size()<<endl;
}