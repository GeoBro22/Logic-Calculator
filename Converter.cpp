#include "Converter.h"

Converter::Converter(Hierarchy* p_object, string name) :
	Hierarchy(p_object, name)
{
	this->classNumber = 4;
}

void Converter::signalPrintPolish(string& text)
{
	text = "Polish Notation: " + polishNotation;
}

void Converter::signalCalculate(string& text)
{
	text = polishNotation;
}

void Converter::handlerFormingPolish(string text)
{
	int i = 0;
	string postfix = "";
	stack <string> s;
	while (text[i] != '.')
	{
		if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z' && (text[i + 1] == ' ' || text[i + 1] == '.')))
		{
			postfix += text[i];
			postfix += " ";
			i++;
		}
		else if (text[i] == '(')
		{
			s.push("(");
			i++;
		}
		else if (text[i] == ')')
		{
			while (s.top() != "(")
			{
				postfix += s.top() + " ";
				s.pop();
			}
			s.pop();
			i++;
		}
		else if (text[i] != ' ')
		{
			int j;
			if (text[i] == 'O' || text[i] == '=')
				j = 2;
			else
				j = 3;
			while (!s.empty() && priority(text.substr(i, j)) <= priority(s.top()))
			{
				postfix += s.top() + " ";
				s.pop();
			}
			s.push(text.substr(i, j));
			i += j;
		}
		else
			i++;
	}
	while (!s.empty())
	{
		postfix += s.top() + " ";
		s.pop();
	}
	polishNotation = postfix.substr(0, postfix.length() - 1);
	this->emitSignal(SIGNAL_D(Converter::signalPrintPolish), text);
	this->emitSignal(SIGNAL_D(Converter::signalCalculate), text);
}

int Converter::priority(string alpha)
{
	if (alpha == "NOT")
		return 5;
	if (alpha == "AND")
		return 4;
	if (alpha == "OR" || alpha == "XOR")
		return 3;
	if (alpha == "=>")
		return 2;
	if (alpha == "<=>")
		return 1;
	return 0;
}
