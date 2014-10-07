#ifndef _TK_KBPRESS_H_
#define _TK_KBPRESS_H_

#include "../os/win/inc.h"

namespace whu {
	typedef enum {
		KEY_UP = VK_UP,
		KEY_DOWN = VK_DOWN,
		KEY_LEFT = VK_LEFT,
		KEY_RIGHT = VK_RIGHT,
		KEY_SPACE = VK_SPACE, 
		KEY_RETURN = VK_RETURN,
		// 其他的键值和ASCII一致
	} KeyBoard;
	bool key_press(int key);
}


#endif // _TK_KBPRESS_H_