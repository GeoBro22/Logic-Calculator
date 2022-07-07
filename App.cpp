#include "App.h"

App::App(Hierarchy* p_object) :
	Hierarchy(p_object)
{
	this->classNumber = 1;
}
void App::hierarchyBuild()
{
	setName("System");
	Hierarchy* readerObj, * variablesObj, * converterObj, * printerObj, * calcObj;
	readerObj = new Reader(this, "Reader");
	calcObj = new Calculation(this, "Calculation");
	variablesObj = new Variables(calcObj, "Variables");
	converterObj = new Converter(this, "Converter");
	printerObj = new Printer(this, "Printer");
	this->setConnection(SIGNAL_D(App::signalReadFormula), readerObj, HANDLER_D(Reader::handlerReadFormula));
	readerObj->setConnection(SIGNAL_D(Reader::signalPrintReadyTree), this, HANDLER_D(App::handlerPrintReadyTree));
	readerObj->setConnection(SIGNAL_D(Reader::signalPrintVariables), printerObj, HANDLER_D(Printer::handlerPrintVariables));
	readerObj->setConnection(SIGNAL_D(Reader::signalFormingPolish), converterObj, HANDLER_D(Converter::handlerFormingPolish));
	readerObj->setConnection(SIGNAL_D(Reader::signalFormingVariables), variablesObj, HANDLER_D(Variables::handlerFormingVariables));
	readerObj->setConnection(SIGNAL_D(Reader::signalVariablesCalc), calcObj, HANDLER_D(Calculation::handlerVariablesCalc));
	variablesObj->setConnection(SIGNAL_D(Variables::signalReadVariables), readerObj, HANDLER_D(Reader::handlerReadVariables));
	converterObj->setConnection(SIGNAL_D(Converter::signalPrintPolish), printerObj, HANDLER_D(Printer::handlerPrintPolish));
	converterObj->setConnection(SIGNAL_D(Converter::signalCalculate), calcObj, HANDLER_D(Calculation::handlerCalculate));
	calcObj->setConnection(SIGNAL_D(Calculation::signalPrintResult), printerObj, HANDLER_D(Printer::handlerPrintResult));
}

int App::execApp()
{
	this->setReadyForAll(1);
	Hierarchy* readerObj;
	readerObj = searchByName("Reader");
	string text;
	cout << "Logical Calculator" << endl;
	cout << "Hello! We are glad to see you in our Logical Calculator. We belive, that this program will be useful for you ;)" << endl<<"By GeoBro22 and IKoRettl"<<endl << endl;
	while (true)
	{
		cout << "Enter your logical expression for solution(enter '.' to leave or enter 'SHOWTREE to print hierarchy tree and to leave): ";
		this->emitSignal(SIGNAL_D(App::signalReadFormula), text);
		cout << "Enter the values of the variables(example - a = 1 b = 1...) : ";
		readerObj->emitSignal(SIGNAL_D(Reader::signalFormingVariables), text);
		readerObj->emitSignal(SIGNAL_D(Reader::signalPrintVariables), text);
		readerObj->emitSignal(SIGNAL_D(Reader::signalFormingPolish), text);
	}
	return 0;
}

void App::signalReadFormula(string& text)
{
	text = "";
}

void App::handlerPrintReadyTree(string text)
{
	this->printReadyTree();
}
