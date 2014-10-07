#ifndef _TK_NAVDATA_PARSER_H_
#define _TK_NAVDATA_PARSER_H_

#include "../basic/type.h"
namespace whu{
	namespace ardrone {

		/**
		 * @brief 感兴趣data
		 */
		typedef struct Navdata_idata_{
			float32_t vx;
			float32_t vy;
			float32_t vz;
			float32_t theta;
			float32_t phi;
			float32_t psi;
			int32_t altitude;
			uint32_t num_frames;
			uint32_t voltage;
		}Navdata_idata; 
		/**
		 * @class NavdataParser NavdataParser.h ardrone/navdata/NavdataParser.h
		 * @brief 解析navdata数据
		 */
		class NavdataParser{
		private:
			bool valid = false;
			void* data = nullptr; /*!< 整个数据 */
			

		public:
			Navdata_idata idata;
			NavdataParser(const void* dt,int size);
			bool set_data(const void* dt, int size);
			bool check_header();
			bool check_vision();
			bool state_fly();
			bool state_video();
			bool state_vision();
			bool state_control();
			bool state_altitude();
			bool state_camera();
			bool state_comlost();
			bool state_navdata_demo();
			bool state_bootstrap();
			bool state_com_watchdog();
			bool state_emergency();

			bool read_option_list();
		};
	}
}

#endif // _TK_NAVDATA_PARSER_H_