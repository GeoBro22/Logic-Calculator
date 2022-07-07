#include "Calculation.h"

Calculation::Calculation(Hierarchy* p_object, string name) :
	Hierarchy(p_object, name)
{
	this->classNumber = 6;
}

void Calculation::handlerVariablesCalc(string text)
{
	for (int i = 0; i < text.length(); i += 6)
	{
		if (text[i] >= 'a' && text[i] <= 'z')
			variables[text[i] - 'a'] = text[i + 4];
		else if (text[i] >= 'A' && text[i] <= 'Z')
			variables[text[i] - 'A' + ('z' - 'a' + 1)] = text[i + 4];
	}
}

void Calculation::signalPrintResult(string& text)
{
	text = "Result: " + result;
	
}

void Calculation::handlerCalculate(string text)
{
	for (int i = 0; i < text.length(); i++)
	{
		if (text[i] >= 'a' && text[i] <= 'z')
			text[i] = variables[text[i] - 'a'];
		else if (text[i] >= 'A' && text[i] <= 'Z' && text[i + 1] == ' ')
			text[i] = variables[text[i] - 'A' + ('z' - 'a' + 1)];
	}
	stack <char> s;
	char fir, sec;
	for (int i = 0; i < text.length(); i++)
	{
		if (text[i] == '0' || text[i] == '1')
		{
			s.push(text[i]);
		}
		else if (text[i] == 'X')
		{
			fir = s.top();
			s.pop();
			sec = s.top();
			s.pop();
			if (fir != sec)
				s.push('1');
			else
				s.push('0');
			i += 3;
		}
		else if (text[i] == 'A')
		{
			fir = s.top();
			s.pop();
			sec = s.top();
			s.pop();
			if (fir == '0' || sec == '0')
				s.push('0');
			else
				s.push('1');
			i += 3;
		}
		else if (text[i] == 'O')
		{
			fir = s.top();
			s.pop();
			sec = s.top();
			s.pop();
			if (fir == '1' || sec == '1')
				s.push('1');
			else
				s.push('0');
			i += 2;
		}
		else if (text[i] == '=')
		{
			fir = s.top();
			s.pop();
			sec = s.top();
			s.pop();
			if (fir == '0' && sec == '1')
				s.push('0');
			else
				s.push('1');
			i += 2;
		}
		else if (text[i] == '<')
		{
			fir = s.top();
			s.pop();
			sec = s.top();
			s.pop();
			if (fir == sec)
				s.push('1');
			else
				s.push('0');
			i += 3;
		}
		else if (text[i] == 'N')
		{
			fir = s.top();
			s.pop();
			if (fir == '0')
				s.push('1');
			else
				s.push('0');
			i += 3;
		}
	}
	if (s.top() == '1')
		result = "true";
	else
		result = "false";
	this->emitSignal(SIGNAL_D(Calculation::signalPrintResult), text);
	cout << endl;
}
