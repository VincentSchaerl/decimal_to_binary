#pragma once
#include <iostream>

using std::string;

const extern string DEFAULT_NUMBER_OF_DECIMAL_PLACES;

double charToDouble(const char c);
string decimalToBinary(const string* const data);
void evaluateInput(const string& input, string* data);
bool isNumberValid(const string& number);
bool isUnsignedInt(const string& numberOfDecimals);
string postPointToBinary(const double postPoint, const int numberOfDecimals);
string prePointToBinary(const double prePoint);
void seperate(const string& input, double* seperatedInputNumber);