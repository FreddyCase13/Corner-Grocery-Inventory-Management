#include "Validator.h"
#include <stdexcept>

Validator::Validator(int min, int max) {

	if (min > max) {
		throw std::invalid_argument("Min is not smaller than max");
	}
	this->minValue = min;
	this->maxValue = max;
}

// validates if minValue is less than maxValue.
bool Validator::isValid(int value) {


	if (value >= minValue && value <= maxValue) {   // **  if else statement that checks if minValue is 
		return true;								// **  less than maxValue. If true, will return true.
	}
	else {   // returns false
		return false;
	}
}

// returns minValue.
int Validator::getMinValue() {

	return minValue;
}

// returns maxValue
int Validator::getMaxValue() {   // returns maxValue

	return maxValue;
}
