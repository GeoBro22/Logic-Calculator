#ifndef __APP_H
#define __APP_H
#include "Hierarchy.h"
#include "Reader.h"
#include "Variables.h"
#include "Calculation.h"
#include "Converter.h"
#include "Printer.h"
#include <stack>

class App : public Hierarchy
{
public:
	App(Hierarchy* p_object);
	void hierarchyBuild();
	int execApp();
	void signalReadFormula(string& text);
	void handlerPrintReadyTree(string text);
};
#endif
