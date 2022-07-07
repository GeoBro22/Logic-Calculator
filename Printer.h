#ifndef __PRINTER_H
#define __PRINTER_H
#include "Hierarchy.h"

class Printer : public Hierarchy
{
public:
	Printer(Hierarchy* p_object, string name = "");
	void handlerPrintVariables(string text);
	void handlerPrintPolish(string text);
	void handlerPrintResult(string text);
};
#endif
