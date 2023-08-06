#include "Functions.h"
#include <string>

const string DEFAULT_NUMBER_OF_DECIMAL_PLACES = "10";

double charToDouble(const char c)
{
	switch (c)
	{
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	}
}

string decimalToBinary(const string* const data)
{
	const int numberOfDecimals = stoi(data[2]);
	double seperatedInputNumber[2];
	seperate(data[1], seperatedInputNumber);
	const string prePoint = prePointToBinary(seperatedInputNumber[0]);
	if (numberOfDecimals == 0)
	{
		return prePoint;
	}
	else
	{
		const string postPoint = postPointToBinary(seperatedInputNumber[1], numberOfDecimals);
		return prePoint + '.' + postPoint;
	}
}

// evaluates input and stores the information in string[3] data:
// data[0]: "invalid" | "terminate" | "valid"
// data[1]: number to be converted
// data[2]: number of decimal places
// A valid input consists of the number to be converted which can be an unsigned integer or decimal (with point or comma),
// and an optional unsigned integer specifying the number of decimal places, seperated from the number to be converted by one space.
void evaluateInput(const string& input, string* data)
{
	// [0] "terminate"
	if (input == "end" || input == "exit" || input == "quit" || input == "terminate")
	{
		data[0] = "terminate";
		return;
	}
	// [0] "invalid" (if number of spaces > 1)
	string number = input; // number to be converted
	string numberOfDecimals = input; // number of decimal places
	int spacePosition = -1;
	int spaces = 0;
	for (int i = 0; i < input.length(); ++i)
	{
		if (input[i] == ' ')
		{
			spacePosition = i;
			++spaces;
		}
	}
	if (spaces > 1 || spacePosition == 0 || spacePosition == input.length() - 1)
	{
		data[0] = "invalid";
		return;
	}
	else if (spaces == 1) // seperate number and numberOfDecimals
	{
		number.erase(spacePosition, input.length() - spacePosition);
		numberOfDecimals.erase(0, spacePosition + 1);
	}
	else
	{
		numberOfDecimals = "";
	}
	// [0] "invalid"
	if (!isNumberValid(number))
	{
		data[0] = "invalid";
		return;
	}
	if (!isUnsignedInt(numberOfDecimals))
	{
		data[0] = "invalid";
		return;
	}
	// [0] "valid"
	data[0] = "valid";
	// [1]
	data[1] = number;
	// [2]
	if (numberOfDecimals == "")
	{
		if (isUnsignedInt(data[1]))
		{
			data[2] = "0";
		}
		else
		{
			data[2] = DEFAULT_NUMBER_OF_DECIMAL_PLACES;
		}
	}
	else
	{
		data[2] = numberOfDecimals;
	}
	return;
}

// The number is valid if there is at most one point or one comma (but not at the first or last position) and all other characters are digits.
bool isNumberValid(const string& number)
{
	int commasAndPoints = 0;
	for (int i = 0; i < number.length(); ++i)
	{
		if (number[i] == '.' || number[i] == ',')
		{
			++commasAndPoints;
		}
	}
	if (commasAndPoints > 1 || number[0] == '.' || number[0] == ',' || number[number.size() - 1] == '.' || number[number.size() - 1] == ',')
	{
		return false;
	}
	for (int i = 0; i < number.size(); ++i)
	{
		if (number[i] != '.' && number[i] != ',' && !isdigit(number[i]))
		{
			return false;
		}
	}
	return true;
}

bool isUnsignedInt(const string& numberOfDecimals)
{
	for (int i = 0; i < numberOfDecimals.length(); ++i)
	{
		if (!isdigit(numberOfDecimals[i]))
		{
			return false;
		}
	}
	return true;
}

string postPointToBinary(const double postPoint, const int numberOfDecimals)
{
	double acc = 0;
	string result;
	for (int i = 0; i < numberOfDecimals; ++i)
	{
		if (acc + pow(0.5, i + 1) <= postPoint)
		{
			result += '1';
			acc += pow(0.5, i + 1);
		}
		else
		{
			result += '0';
		}
	}
	return result;
}

string prePointToBinary(const double prePoint)
{
	if (prePoint == 0)
	{
		return "0";
	}
	double acc = 0;
	int i = 0;
	string result;
	while (pow(2, i) <= prePoint)
	{
		++i;
	}
	for (int j = i - 1; j >= 0; j--)
	{
		if (acc + pow(2, j) <= prePoint)
		{
			result += '1';
			acc += pow(2, j);
		}
		else
		{
			result += '0';
		}
	}
	return result;
}

// seperates the numbers before and after the decimal point
void seperate(const string& inputNumber, double* seperatedInputNumber)
{
	seperatedInputNumber[0] = 0;
	seperatedInputNumber[1] = 0;
	int i = 0;
	while ((i < inputNumber.length() - 1) && (inputNumber[i + 1] != '.') && (inputNumber[i + 1] != ','))
	{
		++i;
	}
	for (int j = 0; j <= i; ++j)
	{
		seperatedInputNumber[0] += charToDouble(inputNumber[j]) * pow(10, (i - j));
	}
	if (i + 1 == inputNumber.length())
	{
		return;
	}
	i += 2;
	int pos = 1;
	for (int j = i; j < inputNumber.length(); ++j)
	{
		seperatedInputNumber[1] += charToDouble(inputNumber[j]) * pow(0.1, pos);
		++pos;
	}
	return;
}