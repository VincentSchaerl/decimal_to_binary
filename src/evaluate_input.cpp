#include <cctype>
#include <string>
#include "evaluate_input.h"

Data evaluateInput(std::string& input)
{
	Data data;
	while (input != "" && input[0] == ' ')
	{
		input.erase(0, 1);
	}
	while (input != "" && input[input.length() - 1] == ' ')
	{
		input.erase(input.length() - 1, 1);
	}
	// status: terminate
	if (input == "end" || input == "exit" || input == "quit" || input == "terminate")
	{
		data.status = terminate;
		return data;
	}
	// status: invalid
	if (input == "")
	{
		data.status = invalid;
		return data;
	}
	std::string number = "";
	std::string numberOfDecimalPlaces = "";
	int i = 0;
	while (i < input.length() && input[i] != ' ')
	{
		number += input[i];
		i++;
	}
	while (i < input.length() && input[i] == ' ')
	{
		i++;
	}
	while (i < input.length() && input[i] != ' ')
	{
		numberOfDecimalPlaces += input[i];
		i++;
	}
	if (input[i] == ' ') // more then two words
	{
		data.status = invalid;
		return data;
	}
	if (!isNumberValid(number))
	{
		data.status = invalid;
		return data;
	}
	if (!isUnsignedInt(numberOfDecimalPlaces))
	{
		data.status = invalid;
		return data;
	}
	// status: valid
	data.status = valid;
	// number
	data.number = number;
	// numberOfDecimalPlaces
	if (numberOfDecimalPlaces == "")
	{
		if (isUnsignedInt(data.number))
		{
			data.numberOfDecimalPlaces = 0;
		}
		else
		{
			data.numberOfDecimalPlaces = -1; // number of decimal places not specified -> as many decimal places as needed
		}
	}
	else
	{
		data.numberOfDecimalPlaces = stoi(numberOfDecimalPlaces);
	}
	return data;
}

bool isNumberValid(const std::string& number)
{
	int commasAndPoints = 0;
	for (int i = 0; i < number.length(); i++)
	{
		if (number[i] == '.' || number[i] == ',')
		{
			commasAndPoints++;
		}
	}
	if (commasAndPoints > 1 || number[0] == '.' || number[0] == ',' || number[number.size() - 1] == '.' || number[number.size() - 1] == ',')
	{
		return false;
	}
	for (int i = 0; i < number.size(); i++)
	{
		if (number[i] != '.' && number[i] != ',' && !isdigit(number[i]))
		{
			return false;
		}
	}
	return true;
}

bool isUnsignedInt(const std::string& numberOfDecimalPlaces)
{
	for (int i = 0; i < numberOfDecimalPlaces.length(); i++)
	{
		if (!isdigit(numberOfDecimalPlaces[i]))
		{
			return false;
		}
	}
	return true;
}