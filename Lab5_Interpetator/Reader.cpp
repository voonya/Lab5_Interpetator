#include "Reader.h"

Reader::Reader(string filename) {
	this->filename = filename;
}

vector<string> Reader::readFile() {
	char buff[FILENAME_MAX];
	_getcwd(buff, FILENAME_MAX);
	string current_working_dir(buff);
	string line;
	string filePath = current_working_dir + "\\" + filename;
	vector<string> result;

	ifstream in(filePath);
	while (!in.eof()) {
		getline(in, line);

		for (size_t pos = 0; pos < line.length(); pos++) {
			if (line[pos] == ' ') line.erase(pos, 1);
		}

		line.erase(line.length()-1, 1);
		result.push_back(line);
	}

	return result;
}