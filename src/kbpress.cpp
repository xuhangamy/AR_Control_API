#include <ardrone/os/win/inc.h>
namespace whu {
	bool key_press(int key) {
		if (GetKeyState(key) < 0) {
			return true;
		}
		return false;
	}
}