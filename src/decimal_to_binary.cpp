#include <cmath>
#include <limits>
#include <string>
#include "decimal_to_binary.h"

std::string decimalToBinary(const std::string& number, const int numberOfDecimalPlaces)
{
	int prePoint;
	double postPoint;
	seperate(number, prePoint, postPoint);
	const std::string prePointBinary = prePointToBinary(prePoint);
	if (numberOfDecimalPlaces == 0)
	{
		return prePointBinary;
	}
	else
	{
		const std::string postPointBinary = postPointToBinary(postPoint, numberOfDecimalPlaces);
		return prePointBinary + '.' + postPointBinary;
	}
}

void seperate(const std::string& inputNumber, int& prePoint, double& postPoint)
{
	prePoint = 0;
	postPoint = 0;
	int i = 0;
	while ((i < inputNumber.length() - 1) && (inputNumber[i + 1] != '.') && (inputNumber[i + 1] != ','))
	{
		i++;
	}
	for (int j = 0; j <= i; j++)
	{
		prePoint += (inputNumber[j] - '0') * pow(10, (i - j));
	}
	if (i + 1 == inputNumber.length())
	{
		return;
	}
	i += 2;
	int pos = 1;
	for (int j = i; j < inputNumber.length(); j++)
	{
		postPoint += (inputNumber[j] - '0') * pow(0.1, pos);
		pos++;
	}
	return;
}

std::string prePointToBinary(const int prePoint)
{
	if (prePoint == 0)
	{
		return "0";
	}
	double acc = 0;
	int i = 0;
	std::string result = "";
	while (pow(2, i) <= prePoint)
	{
		i++;
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

std::string postPointToBinary(const double postPoint, int numberOfDecimalPlaces)
{
	double acc = 0;
	bool numberOfDecimalPlacesSet = true;
	if (numberOfDecimalPlaces == -1)
	{
		numberOfDecimalPlaces = std::numeric_limits<int>::max();
		numberOfDecimalPlacesSet = false;
	}
	std::string result = "";
	double tolerance = std::numeric_limits<double>::epsilon();
	for (int i = 0; i < numberOfDecimalPlaces; i++)
	{
		// acc == postPoint
		if (acc < postPoint + tolerance && acc > postPoint - tolerance)
		{
			if (result.length() == 0)
			{
				result += '0';
			}
			if (numberOfDecimalPlacesSet)
			{
				int remainingZeros = numberOfDecimalPlaces - result.length();
				result += std::string(remainingZeros, '0');
			}
			break;
		}
		// acc + pow == postPoint
		if (acc + pow(0.5, i + 1) < postPoint + tolerance && acc + pow(0.5, i + 1) > postPoint - tolerance)
		{
			result += '1';
			if (numberOfDecimalPlacesSet)
			{
				int remainingZeros = numberOfDecimalPlaces - result.length();
				result += std::string(remainingZeros, '0');
			}
			break;
		}
		// acc + pow < postPoint
		if (acc + pow(0.5, i + 1) < postPoint)
		{
			result += '1';
			acc += pow(0.5, i + 1);
		}
		// acc + pow > postPoint
		else
		{
			result += '0';
		}
	}
	return result;
}