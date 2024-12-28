#pragma once

#include <string>

std::string decimalToBinary(const std::string& number, const int numberOfDecimalPlaces);
void seperate(const std::string& inputNumber, int& prePoint, double& postPoint);
std::string prePointToBinary(const int prePoint);
std::string postPointToBinary(const double postPoint, int numberOfDecimalPlaces);