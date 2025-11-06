#include<iostream>
#include "logger.h"
using namespace std;
int main() {
	log(INFO) << "Application started." << endl;
	// Your application code here
	log(INFO) << "Application finished." << endl;
	return 0;
}