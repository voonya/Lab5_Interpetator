#include "Interpretator.h"
#include "Reader.h"

int main()
{
	//cout << " Input the filename: ";
	//string filename;  cin >> filename;
	//Interpretator inter;
	//float result = inter.interpretate(filename);
	//cout << " The result is: " << result;
	TreeCreator tree;
	
	Reader reader("test.txt");
	vector<string> res;
	res = reader.readFile();

	tree.createTree(res);
	return 0;
}

