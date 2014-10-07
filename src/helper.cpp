#include <sstream>
#include <string>
#include <assert.h>
#include <iostream>
using namespace std;
// needed by net_* functions
#include <ardrone/os/win/inc.h>
#include <ardrone/basic/com_def.h>

namespace whu {
	namespace ardrone {

		int f32_int32_adjust(const float n) {
			assert(sizeof(int) == sizeof(float));
			const int* num = (int*)&n;
			return *num;
		}

		void net_prepare() {
			WSADATA wsaData;
			WSAStartup(MAKEWORD(2, 2), &wsaData);
		}

		void net_end() {
			WSACleanup();
		}


		string get_local_ip() {
			DWORD dwRetVal;
			HANDLE hHeap = GetProcessHeap();
			MIB_IPADDRTABLE *pIpTable = (MIB_IPADDRTABLE*)HeapAlloc(hHeap, 0, sizeof(MIB_IPADDRTABLE));
			DWORD dwSize = 0;
			in_addr ipaddr;
			ipaddr.S_un.S_addr = ntohl(pIpTable->table[1].dwAddr);
			char *strIpAddr = inet_ntoa(ipaddr);
			if (GetIpAddrTable(pIpTable, &dwSize, 0) == ERROR_INSUFFICIENT_BUFFER) {
				HeapFree(hHeap, 0, pIpTable);
				pIpTable = (MIB_IPADDRTABLE*)HeapAlloc(hHeap, 0, dwSize);
			}
			if (dwRetVal = GetIpAddrTable(pIpTable, &dwSize, 0) != NO_ERROR) {
				return "";

			}
			char ret[15];
			sprintf_s(ret, "%u.%u.%u.%u", \
				pIpTable->table[0].dwAddr & 0x000000FF, \
				(pIpTable->table[0].dwAddr & 0x0000FF00) >> 8, \
				(pIpTable->table[0].dwAddr & 0x00FF0000) >> 16, \
				(pIpTable->table[0].dwAddr & 0xFF000000) >> 24);
			/* release handle */
			HeapFree(hHeap, 0, pIpTable);
			CloseHandle(hHeap);
			return string(ret);
		}

		// check,but not handle mistakes
		void check_status(STATUS status, const string msg) {
			switch (status) {
			case TK_OK:
				cout << "ok:\t" << msg << endl;
				break;
			case TK_ERROR:
				cerr << "error:\t" << msg << endl;
				break;
			case TK_WARNING:
				cerr << "warning:\t" << msg << endl;
				break;
			case TK_SOCK_ERROR:
				cerr << "socket error:\t" << msg << endl;
				break;
			case TK_INVALID_SCK:
				cerr << "invalid socket:\t" << msg << endl;
				break;
			default:
				break;
			}
		}

		void* bootstrap_check(void* param) {

			const bool is_bootstrap = true;
			return (void*)&is_bootstrap;
		}

		void console_color_reset() {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		void console_color_set(unsigned short color) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		}
	}
}