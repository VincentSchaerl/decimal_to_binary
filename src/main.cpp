#include <iostream>
#include <string>
#include "decimal_to_binary.h"
#include "evaluate_input.h"

int main()
{
	std::string input;
	while (true)
	{
		getline(std::cin, input);
		Data data = evaluateInput(input);
		if (data.status == invalid)
		{
			std::cout << "Invalid input\n\n";
			continue;
		}
		if (data.status == terminate)
		{
			break;
		}
		std::cout << decimalToBinary(data.number, data.numberOfDecimalPlaces) << "\n\n";
	}
	return 0;
}