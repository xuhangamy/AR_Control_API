#include <ardrone/version.h>
#include <iostream>
#include <string>
using namespace whu::ardrone;
using namespace std;

#pragma comment(lib,"Lib.lib")

int main(int argc, char** argv) {
	api_version_r version = api_version::create();
	cout << "major:" << version.get_major() << endl;
	cout << "minor:" << version.get_minor() << endl;
	cout << "patch:" << version.get_patch() << endl;
	cout << "version:" << version.get_version() << endl;
	return 0;
}