#include "App.h"

using namespace std;

int main()
{
	App app_object(nullptr);
	app_object.hierarchyBuild();
	return app_object.execApp();
}