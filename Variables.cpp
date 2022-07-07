#include "Variables.h"

Variables::Variables(Hierarchy* p_object, string name) :
	Hierarchy(p_object, name)
{
	this->classNumber = 3;
}

void Variables::signalReadVariables(string& text)
{
	text = variables;
}

void Variables::handlerFormingVariables(string text)
{
	bool flg;
	variables = "";
	text = " " + text;
	for (int i = 1; i < text.length(); i++)
	{
		flg = true;
		if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z' && (text[i + 1] == ' ' || text[i + 1] == '.') && text[i - 1] == ' '))
		{
			for (int j = 0; j < variables.length(); j++)
			{
				if (variables[j] == text[i])
				{
					flg = false;
					break;
				}
			}
			if (flg)
			{
				variables += text[i];
				variables += " =   ";
			}
		}
	}
	variables = variables.substr(0, variables.length() - 1);
	for (int i = 0; i < variables.length(); i++)
	{
		if ((variables[i] >= 'a' && variables[i] <= 'z') || (variables[i] >= 'A' && variables[i] <= 'Z'))
		{
			int min = i;
			for (int j = i + 1; j < variables.length(); j++)
			{
				if (((variables[j] >= 'a' && variables[j] <= 'z') || (variables[j] >= 'A' && variables[j] <= 'Z')) && (variables[min] > variables[j]))
				{
					min = j;
				}
			}

			char tmp;
			tmp = variables[i];
			variables[i] = variables[min];
			variables[min] = tmp;
		}
	}
	this->emitSignal(SIGNAL_D(Variables::signalReadVariables), text);
}
