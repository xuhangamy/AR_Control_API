#ifndef _TK_ARDRONECLIENT_H_
#define _TK_ARDRONECLIENT_H_

#include "at/CommandId.h"
#include "at/ATCmdGenerator.h"
#include "basic/Mutex.h"
#include "basic/timer.h"
#include "net/UdpClient.h"


namespace whu {
	namespace ardrone {

		class ARDroneClient {
		private:
			
			CommandId& cmdid = CommandId::Create();
			UdpClient* atClient;
			UdpClient* navClient;
			
		public:
			
			ATCmdGenerator& atgen = ATCmdGenerator::Create(&cmdid);

			ARDroneClient();
			~ARDroneClient();

			bool InitARDrone();

			bool SendATCmd(std::string atgen_str);

			/**
			 * @brief �������ݣ����봦����,����ʱ���Զ����ô�����
			 * @breif ������dt_pack��ʾ��������Ϊdata_pack
			 */
			bool RecvData(void (*handle_func)(void* dt_pack)); 

			void RequestData();
		};
	}
}

#endif // _TK_ARDRONECLIENT_H_