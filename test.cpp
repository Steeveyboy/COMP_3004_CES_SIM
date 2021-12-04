#include <iostream>

#include "sessionRecorder.h"
using namespace std;

int main(){
	cout<<"starting"<<endl;
	sessionRecorder *r = new sessionRecorder();
	// r->makeRecord(1, 1, 1);
	// r->makeRecord(2, 2, 2);
	// r->makeRecord(3, 3, 3);
	// r->makeRecord(4, 4, 4);
	// r->makeRecord(5, 3, 5);
	// r->makeRecord(7, 8, 9);
	delete r;
	cout<<"ending"<<endl;
	return 1;
}
