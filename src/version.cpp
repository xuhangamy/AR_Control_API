#include <ardrone/version.h>
using whu::ardrone::api_version;

api_version::api_version() {}
api_version::~api_version() {}

api_version& api_version::create() {
	static api_version version;
	return version;
}
int api_version::get_major() const{
	return major;
}
int api_version::get_minor() const {
	return minor;
}
int api_version::get_patch() const {
	return patch;
}
std::string api_version::get_version() const {
	char tmp[12];
	sprintf_s(tmp, "%d.%d.%d", major, minor, patch);
	return std::string(tmp);
}