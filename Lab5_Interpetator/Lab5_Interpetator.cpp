#include "Interpretator.h"
#include "Reader.h"

int main()
{
	//cout << " Input the filename: ";
	//string filename;  cin >> filename;
	//Interpretator inter;
	//float result = inter.interpretate(filename);
	//cout << " The result is: " << result;
	//TreeCreator tree;
	//tree.parseLine("((2.5*4])+2-5.1*3");
	Reader reader("text.txt");
	vector<string> res;
	res = reader.readFile();

	for (size_t i = 0; i < res.size(); i++)
		cout << res[i] << endl;
	return 0;
}

