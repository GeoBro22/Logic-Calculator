#ifndef __CONVERTER_H
#define __CONVERTER_H
#include "Hierarchy.h"
#include <stack>

class Converter : public Hierarchy
{
public:
	Converter(Hierarchy* p_object, string name = "");
	int priority(string alpha);
	void handlerFormingPolish(string text);
	void signalPrintPolish(string& text);
	void signalCalculate(string& text);
private:
	string polishNotation;
};
#endif
