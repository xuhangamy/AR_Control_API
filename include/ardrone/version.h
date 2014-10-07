/**
* @file version.h
*
* @brief API版本
*
* @author tkorays
* @date 2014-06-06
* @since 1.1.0
*
* 该API相关的类与函数
*
* Copyright 2014.All rights reserved.
*/

#ifndef _TK_ARDRONE_VERSION_H_
#define _TK_ARDRONE_VERSION_H_

#include <string>

/** 
 * @brief api的版本信息
 */
namespace whu {
namespace ardrone {
	class api_version {
	private:
		int major = 1;
		int minor = 1;
		int patch = 0;
		api_version();
		~api_version();
		api_version(const api_version&);
		const api_version& operator=(const api_version&);
	public:
		static api_version& create();
		int get_major() const;
		int get_minor() const;
		int get_patch() const;
		std::string get_version() const;
	};

	typedef api_version& api_version_r;
}
}



#endif // _TK_ARDRONE_VERSION_H_