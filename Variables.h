#ifndef __VARIABLSE_H
#define __VARIABLES_H
#include "Hierarchy.h"

class Variables : public Hierarchy
{
public:
	Variables(Hierarchy* p_object, string name = "");
	void handlerFormingVariables(string text);
	void signalReadVariables(string& text);
private:
	string variables = "";
};
#endif
