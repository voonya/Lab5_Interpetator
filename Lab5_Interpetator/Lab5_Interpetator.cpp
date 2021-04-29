#include "Interpretator.h"

int main()
{
	//cout << " Input the filename: ";
	//string filename;  cin >> filename;
	//Interpretator inter;
	//float result = inter.interpretate(filename);
	//cout << " The result is: " << result;
	TreeCreator tree;
	tree.parseLine("3+4*2/(1-5)^2^3");
	return 0;
}

