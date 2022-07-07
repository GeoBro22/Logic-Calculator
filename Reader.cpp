#include "Reader.h"

Reader::Reader(Hierarchy* p_object, string name) :
	Hierarchy(p_object, name)
{
	this->classNumber = 2;
}

void Reader::signalPrintReadyTree(string& text)
{
	text = "";
}
void Reader::signalFormingVariables(string& text)
{
	text = infixNotation;
}

void Reader::signalPrintVariables(string& text)
{
	text = "Values: " + variables;
}

void Reader::signalFormingPolish(string& text)
{
	text = infixNotation;
}

void Reader::signalVariablesCalc(string& text)
{
	text = varCalc;
}

void Reader::handlerReadFormula(string text)
{
	getline(cin, infixNotation);
	if (infixNotation == ".")
		exit(0);
	//cout << endl;
	if (infixNotation == "SHOWTREE")
	{
		this->emitSignal(SIGNAL_D(Reader::signalPrintReadyTree), text);
		exit(0);
	}
	if (infixNotation[infixNotation.length()-1]!='.')
		infixNotation += ".";
}

void Reader::handlerReadVariables(string text)
{
	string str;
	getline(cin, str);
	for (int i = 0; i < text.length(); i++)
	{
		if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
		{
			for (int j = 0; j < text.length(); j++)
			{
				if (text[i] == str[j])
				{
					text[i + 4] = str[j + 4];
				}
			}
		}
	}
	varCalc = text;
	for (int i = 0; i < text.length(); i++)
	{
		if (text[i] == '1')
		{
			str = text.substr(0, i);
			str += "true";
			if (i != text.length() - 1)
				str += text.substr(i + 1);
			text = str;
		}
		else if (text[i] == '0')
		{
			str = text.substr(0, i);
			str += "false";
			if (i != text.length() - 1)
				str += text.substr(i + 1);
			text = str;
		}
	}
	variables = text;
	this->emitSignal(SIGNAL_D(Reader::signalVariablesCalc), text);

}
