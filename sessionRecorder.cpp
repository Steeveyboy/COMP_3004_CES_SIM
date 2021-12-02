#include <iostream>
#include <string>
#include <vector>
#include "sessionRecorder.h"
#include "record.h"
using namespace std;

sessionRecorder::sessionRecorder() {
	numRecords = 0;


}

void sessionRecorder::makeRecord(int fq, int pwr, int dur){
	cout<<fq<<"	"<<pwr<<"	"<<dur<<endl;
	record *rec = new record(fq, pwr, dur, numRecords, "date");

}
