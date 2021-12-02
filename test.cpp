#include <iostream>
#include <fstream>
#include "sessionRecorder.h"
using namespace std;

int main(){
	cout<<"starting"<<endl;
	// sessionRecorder *r = new sessionRecorder();
	// r->makeRecord(1, 1, 1);

	fstream fh;
	fh.open("records.txt");
	fh<<"record 1"<<endl;
	fh.close();

	cout<<"ending"<<endl;
	return 1;
}
