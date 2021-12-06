#include <iostream>
#include <string>
#include <vector>
#include "sessionRecorder.h"
#include "record.h"
#include <sstream>
using namespace std;

sessionRecorder::sessionRecorder() {
	numRecords = 0;
	initRecords();
}

void sessionRecorder::initRecords(){

	ifstream infile(filepath, ios::in);

    string line;

    int duration, id, curr;
    string freq, date, wave;
    cout<<"Collecting records"<<endl;
//infile >> freq >> curr >> duration >> wave >> date >> id
    while(getline(infile, line, '\n')){
        stringstream ss(line);
        ss >> freq >> curr >> duration >> wave >> date >> id;
        cout<<"Co"<<endl;
        record *r = new record(freq, curr, duration, wave, id, date);
		records.push_back(r);
	}
    infile.close();
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
        cout<<r->freq<<"	"<<r->current<<"	"<<r->date<<endl;
	}
}

void sessionRecorder::makeRecord(string fq, string curr, int dur, string date, string wave){
	//cout<<fq<<"	"<<pwr<<"	"<<dur<<"	"<<records.size()<<endl;
    record *rec = new record(fq, curr, dur, wave, records.size(), date);
	records.push_back(rec);
	cout<<records[records.size()-1]->freq<<endl;
	//storeRecords();
	numRecords++;
}

void sessionRecorder::storeRecords(){
    ofstream fh;
    fh.open(filepath);

    //QFile fl(filepath);
    //fl.open(QIODevice::WriteOnly);
    //QTextStream textStream(fl);

    cout<<"writing to "<<filepath<<endl;
	//fh.open("records.txt", ios::out | ios::trunc);
	record *r;
	for(int i=0; i<records.size(); i++){
		r = records[i];
        cout<<r->freq<<"	"<<r->current<<"	"<<r->duration<<"	"<<r->waveform<<"	"<<r->date<<"	"<<r->id<<endl;
        //textStream <<r->freq<<"	"<<r->current<<"	"<<r->duration<<"	"<<r->waveform<<"	Date"<<"	"<<r->id<<endl;
        fh<<r->freq<<"	"<<r->current<<"	"<<r->duration<<"	"<<r->waveform<<"   "<<r->date<<"	"<<r->id<<endl;
	}
	fh.close();
}

sessionRecorder::~sessionRecorder(){
	storeRecords();
	//fh.close();
	cout<<records.size()<<endl;
}
