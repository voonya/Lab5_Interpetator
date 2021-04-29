#include "Interpretator.h"
#include <vector>
#include <fstream>
#include <direct.h>
#include <io.h>
#include <string>

class Reader {
private:
	string filename;
public:
	Reader(string);
	vector<string> readFile();
};