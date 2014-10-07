#ARDrone API 

AR.Drone四轴飞行器的控制API，目前只支持windows平台，不过你可以通过部分代码，让它可以在linux等平台运行。

##include目录一览

* at，AT指令相关数据结构定义
* basic，基础定义，包括一些基本类型重定义，基本结构体，及其他。
* navdata，飞行数据相关结构体与类定义。
* net，网络相关。
* os，与平台相关的代码。
* video，视频流相关。

##其他
整个项目的命名空间有两个，一个是`whu`，还有一个是`ardrone`，ardrone是在whu下面的一个子空间。

你可以通过使用`using namespace whu::ardrone;`来访问ardrone命名空间。

凡是和ardrone有关系的都放在ardrone命名空间，否则处于whu命名空间。

##使用说明
项目可以使用vs编译，这里也提供了windows平台的makefile，双击build.exe即可，如果提示没有lib文件夹，就在根目录下新建一个吧。

只用包含ardrone.h头文件就可以使用，但是不要忘了链接编译好的静态链接库。

具体的一些demo可以见test_src，有些demo可能由于版本问题，不能正常运行了。具体见test_src的readme文件。

##作者
tkorays <tkorays@hotmail.com>

weibo: http://weibo.com/tkorays

#Date 
6/6/2014
