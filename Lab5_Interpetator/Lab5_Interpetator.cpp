#include "Interpretator.h"

int main()
{
	cout << " Input the filename: ";
	string filename;  cin >> filename;
	Interpretator inter;
	float result = inter.interpretate(filename);
	cout << " The result is: " << result;
	return 0;
}

