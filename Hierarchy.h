#ifndef HIERARCHY_H
#define HIERARCHY_H
#define SIGNAL_D(signal_f) (TYPE_SIGNAL) (&signal_f)
#define HANDLER_D(handler_f) (TYPE_HANDLER) (&handler_f)

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Hierarchy
{
public:
	typedef void (Hierarchy::* TYPE_SIGNAL) (string&);
	typedef void (Hierarchy::* TYPE_HANDLER) (string);
private:
	string name;
	int ready = 0;
	Hierarchy* parent_object = nullptr;
	vector <Hierarchy*> subordinate_objects;
	struct connectionStruct
	{
		TYPE_SIGNAL signalMethod;
		Hierarchy* handler;
		TYPE_HANDLER handlerMethod;
	};
	vector <connectionStruct> connections;
protected:
	int classNumber;
public:
	Hierarchy(Hierarchy* p_object, string name = "");
	~Hierarchy();
	void setName(string name);
	string getName();
	int getReady();
	void printReadyTree(int level = 4);
	void setReady(int ready);
	Hierarchy* searchByName(string name);
	void setConnection(TYPE_SIGNAL signalMethod, Hierarchy* handler, TYPE_HANDLER handlerMethod);
	void deleteConnection(TYPE_SIGNAL signalMethod, Hierarchy* handler, TYPE_HANDLER handlerMethod);
	void emitSignal(TYPE_SIGNAL signalMethod, string& text);
	int getClassNumber();
	void setReadyForAll(int ready);
};
#endif
