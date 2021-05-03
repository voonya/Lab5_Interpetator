#include <vector>
#include <fstream>
#include <direct.h>
#include <io.h>
#include <string>
#include <iostream>
using namespace std;

class Reader {
private:
	string filename;
public:
	Reader(string);
	vector<string> readFile();
};