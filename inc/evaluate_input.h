#pragma once

#include <string>

enum Status
{
    valid,
    invalid,
    terminate
};

struct Data
{
    Status status;
    std::string number;
    int numberOfDecimalPlaces;
};

Data evaluateInput(std::string& input);
bool isNumberValid(const std::string& number);
bool isUnsignedInt(const std::string& numberOfDecimalPlaces);