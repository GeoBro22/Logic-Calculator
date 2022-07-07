#ifndef __CALCULATION_H
#define __CALCULATION_H
#include "Hierarchy.h"
#include <stack>

class Calculation : public Hierarchy
{
public:
	Calculation(Hierarchy* p_object, string name = "");
	void handlerCalculate(string text);
	void handlerVariablesCalc(string text);
	void signalPrintResult(string& text);
private:
	string variables = "0000000000000000000000000000000000000000000000000000";
	string result;
};
#endif
