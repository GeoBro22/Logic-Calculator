#ifndef __READER_H
#define __READER_H
#include "Hierarchy.h"

class Reader : public Hierarchy
{
public:
	Reader(Hierarchy* p_object, string name = "");
	void handlerReadFormula(string text);
	void handlerReadVariables(string text);
	void signalFormingVariables(string& text);
	void signalPrintVariables(string& text);
	void signalFormingPolish(string& text);
	void signalVariablesCalc(string& text);
	void signalPrintReadyTree(string& text);
private:
	string infixNotation;
	string variables;
	string varCalc;
};
#endif
