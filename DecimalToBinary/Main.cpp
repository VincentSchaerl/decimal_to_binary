#include "Functions.h"
#include <string>

using std::cin;
using std::cout;

int main()
{
	string input;
	while (true)
	{
		getline(cin, input);
		string data[3];
		evaluateInput(input, data);
		if (data[0] == "invalid")
		{
			cout << "Invalid input\n\n";
			continue;
		}
		if (data[0] == "terminate")
		{
			break;
		}
		cout << decimalToBinary(data) << "\n\n";
	}
	return 0;
}