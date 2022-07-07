#include "Printer.h"

Printer::Printer(Hierarchy* p_object, string name) :
	Hierarchy(p_object, name)
{
	this->classNumber = 5;
}

void Printer::handlerPrintVariables(string text)
{
	cout << text << endl;
}
void Printer::handlerPrintPolish(string text)
{
	cout << text << endl;
}
void Printer::handlerPrintResult(string text)
{
	cout << text << endl;
}
