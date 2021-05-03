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

		line.erase(remove(line.begin(), line.end(), ' '), line.end());
		line.erase(remove(line.begin(), line.end(), '\t'), line.end());

		line.erase(line.length()-1, 1);
		cout << line << endl;
		result.push_back(line);
	}

	return result;
}