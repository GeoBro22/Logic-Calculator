#include "Hierarchy.h"

using namespace std;

Hierarchy::Hierarchy(Hierarchy* p_object, string name)
{
	this->name = name;
	parent_object = p_object;
	if (p_object)
	{
		p_object->subordinate_objects.push_back(this);
	}
}

void Hierarchy::setName(string name)
{
	this->name = name;
}
string Hierarchy::getName()
{
	return name;
}

void Hierarchy::printReadyTree(int level)
{
	cout << getName();
	if (ready != 0)
		cout << " is ready";
	else
		cout << " is not ready";
	for (int i = 0; i < subordinate_objects.size(); i++)
	{
		cout << endl;
		for (int j = 0; j < level; j++)
		{
			cout << " ";
		}
		subordinate_objects[i]->printReadyTree(level + 4);
	}
}


int Hierarchy::getReady()
{
	return ready;
}

void Hierarchy::setReady(int ready)
{
	if ((parent_object == nullptr) || (parent_object != nullptr && parent_object->getReady() != 0))
	{
		if (ready == 0)
		{
			for (int i = 0; i < subordinate_objects.size(); i++)
			{
				subordinate_objects[i]->setReady(0);
			}
		}
		this->ready = ready;
	}
}

Hierarchy* Hierarchy::searchByName(string name)
{
	if (this->name == name)
		return this;
	for (int i = 0; i < subordinate_objects.size(); i++)
	{
		Hierarchy* child = subordinate_objects[i]->searchByName(name);
		if (child != nullptr)
			return child;
	}
	return nullptr;
}


void Hierarchy::setConnection(TYPE_SIGNAL signalMethod, Hierarchy* handler, TYPE_HANDLER handlerMethod)
{
	for (int i = 0; i < connections.size(); i++)
	{
		if (connections[i].signalMethod == signalMethod && connections[i].handlerMethod == handlerMethod)
			return;
	}

	connectionStruct connection;
	connection.signalMethod = signalMethod;
	connection.handler = handler;
	connection.handlerMethod = handlerMethod;
	connections.push_back(connection);
}

void Hierarchy::deleteConnection(TYPE_SIGNAL signalMethod, Hierarchy* handler, TYPE_HANDLER handlerMethod)
{
	for (int i = 0; i < connections.size(); i++)
	{
		if (connections[i].signalMethod == signalMethod && connections[i].handlerMethod == handlerMethod)
		{
			connections.erase(connections.begin() + i);
			return;
		}
	}
}

void Hierarchy::emitSignal(TYPE_SIGNAL signalMethod, string& text)
{
	if (this->getReady() == 0)
		return;
	if (connections.empty())
		return;
	(this->*signalMethod)(text);

	for (int i = 0; i < connections.size(); i++)
	{
		if (connections[i].signalMethod == signalMethod && connections[i].handler->getReady() != 0)
			(connections[i].handler->*(connections[i].handlerMethod))(text);
	}
}

int Hierarchy::getClassNumber()
{
	return classNumber;
}

void Hierarchy::setReadyForAll(int ready)
{
	this->setReady(ready);
	for (int i = 0; i < subordinate_objects.size(); i++)
	{
		subordinate_objects[i]->setReadyForAll(ready);
	}
}

Hierarchy::~Hierarchy()
{
	for (int i = 0; i < subordinate_objects.size(); i++)
	{
		delete subordinate_objects[i];
	}
}
