#ifndef _TK_NAVDATA_COMMON_H_
#define _TK_NAVDATA_COMMON_H_

#include "navdata_tag.h"
#include "../basic/type.h"
#include "../basic/math.h"
using namespace whu;

#define NAVDATA_HEADER 0X55667788 // 数据消息头
#define NAVDATA_MAX_SIZE 4096 // 数据最大长度
#define NAVDATA_MAX_CUSTOM_TIME_SAVE 20 // 最大的超时时间


#define NAVDATA_OPTION_MASK(option) (1<<(option))
#define NAVDATA_OPTION_FULL_MASK ((1<<NAVDATA_NUM_TAGS)-1)

// NUMBER OF TRACKERS FOR EACH TRACKING
#define NB_CORNER_TRACKERS_WIDTH    5      /* number of trackers in width of current picture */
#define NB_CORNER_TRACKERS_HEIGHT   4      /* number of trackers in height of current picture */
#define DEFAULT_NB_TRACKERS_WIDTH    (NB_CORNER_TRACKERS_WIDTH+1)// + NB_BLOCK_TRACKERS_WIDTH)
#define DEFAULT_NB_TRACKERS_HEIGHT   (NB_CORNER_TRACKERS_HEIGHT+1)// + NB_BLOCK_TRACKERS_HEIGHT)

#define NB_NAVDATA_DETECTION_RESULTS 4

namespace whu {
	namespace ardrone {
		typedef enum {
			GYRO_X = 0,
			GYRO_Y = 1,
			GYRO_Z = 2,
			NB_GYROS = 3
		} def_gyro_t;

		/**
		 * @brief 加速度相关常数
		 */
		typedef enum {
			ACC_X = 0,
			ACC_Y = 1,
			ACC_Z = 2,
			NB_ACCS = 3
		} def_acc_t;
		/**
		 * @brief 速度相关常数
		 */
		typedef struct _velocities_t {
			float32_t x;
			float32_t y;
			float32_t z;
		} velocities_t;


		/**
		 * @brief navdata option,可能是用于预处理，得到tag和size
		 * @attention options和checksum有不同的id
		 * 可以直接读取最后vision后面的数据到navdata_option中判断其类型，然后
		 * 决定是用checksum来处理还是一般的options
		 */
		typedef struct _navdata_option_t {
			uint16_t tag; /**< 标签，id */
			uint16_t size; /**< 大小 */
			byte_t data[1]; /**< 数据，这里不需要读取完整的数据 */
		} navdata_option_t;

		/**
		 * @brief 一条navigation的数据结构,不包含校验和
		 */
		typedef struct _navdata_t {
			uint32_t header; /**< 数据头 */
			uint32_t ardrone_state; /**< ardrone的状态信息 */
			uint32_t sequence; /**< 序列编号 */
			bool_t vision_defined; /**< 是否使用vision */
			navdata_option_t options[1]; /**< 各种选项,和可以用于辨别是checksum还是options */
		} navdata_t;

		/**
		 * @brief navdata demo数据包
		 */
		typedef struct _navdata_demo_t {
			uint16_t tag; /*!< 标签（id） */
			uint16_t size; /*!< 大小 */
			uint32_t ctrl_state; /*!< control的状态 */
			uint32_t vbat_flying_precentage; /*!< 。。。 */

			float32_t theta; /*!< theta角 */
			float32_t phi; /*!< phi角 */
			float32_t psi; /*!< psi */

			int32_t altitude; /*!< 高度 */

			float32_t vx; /*!< x方向速度 */
			float32_t vy; /*!< y方向速度 */
			float32_t vz; /*!< z方向速度 */

			uint32_t num_frames; /**< 视频帧数 */

			// 这后面还有一些数据,已经过时
			// 不要读取，直接根据这个option大小确定下一个option的位置

		} navdata_demo_t;

		/**
		 * @brief navdata的校验和
		 */
		typedef struct navdata_cks_t {
			uint16_t tag; /*!< 标签，id */
			uint16_t size; /*!< 大小 */
			uint32_t cks; /*!< 校验数据 */
		} navdata_cks_t;

		typedef struct _navdata_time_t {
			uint16_t  tag; /*!< 标签 */
			uint16_t  size; /*!< 大小 */
			uint32_t  time;  /*!< 32位整型，11个重要的位表示秒，剩下的21个位表示毫秒 */
		} navdata_time_t;

		typedef struct _navdata_raw_measures_t {
			uint16_t  tag;
			uint16_t  size;

			// +12 bytes
			uint16_t  raw_accs[NB_ACCS];    // filtered accelerometers
			int16_t   raw_gyros[NB_GYROS];  // filtered gyrometers
			int16_t   raw_gyros_110[2];     // gyrometers  x/y 110 deg/s
			uint32_t  vbat_raw;             // battery voltage raw (mV)
			uint16_t  us_debut_echo;
			uint16_t  us_fin_echo;
			uint16_t  us_association_echo;
			uint16_t  us_distance_echo;
			uint16_t  us_courbe_temps;
			uint16_t  us_courbe_valeur;
			uint16_t  us_courbe_ref;
			uint16_t  flag_echo_ini;
			// TODO:   uint16_t  frame_number; // from ARDrone_Magneto
			uint16_t  nb_echo;
			uint32_t  sum_echo;
			int32_t   alt_temp_raw;
			int16_t   gradient;
		} navdata_raw_measures_t;

		typedef struct _navdata_pressure_raw_t {
			uint16_t   tag;
			uint16_t   size;

			int32_t   up;
			int16_t   ut;
			int32_t   Temperature_meas;
			int32_t   Pression_meas;
		}navdata_pressure_raw_t;

		typedef struct _navdata_magneto_t {
			uint16_t   tag;
			uint16_t   size;

			int16_t   	mx;
			int16_t   	my;
			int16_t   	mz;
			vector31_t 	magneto_raw;       // magneto in the body frame, in mG
			vector31_t 	magneto_rectified;
			vector31_t 	magneto_offset;
			float32_t 	heading_unwrapped;
			float32_t 	heading_gyro_unwrapped;
			float32_t 	heading_fusion_unwrapped;
			char 			magneto_calibration_ok;
			uint32_t      magneto_state;
			float32_t 	magneto_radius;
			float32_t     error_mean;
			float32_t     error_var;

		}navdata_magneto_t;


		typedef struct _navdata_wind_speed_t {
			uint16_t   tag;
			uint16_t   size;

			float32_t wind_speed;			// estimated wind speed [m/s]
			float32_t wind_angle;			// estimated wind direction in North-East frame [rad] e.g. if wind_angle is pi/4, wind is from South-West to North-East
			float32_t wind_compensation_theta;
			float32_t wind_compensation_phi;
			float32_t state_x1;
			float32_t state_x2;
			float32_t state_x3;
			float32_t state_x4;
			float32_t state_x5;
			float32_t state_x6;
			float32_t magneto_debug1;
			float32_t magneto_debug2;
			float32_t magneto_debug3;
		} navdata_wind_speed_t;


		typedef struct _navdata_kalman_pressure_t {
			uint16_t   tag;
			uint16_t   size;

			float32_t offset_pressure;
			float32_t est_z;
			float32_t est_zdot;
			float32_t est_bias_PWM;
			float32_t est_biais_pression;
			float32_t offset_US;
			float32_t prediction_US;
			float32_t cov_alt;
			float32_t cov_PWM;
			float32_t cov_vitesse;
			bool_t    bool_effet_sol;
			float32_t somme_inno;
			bool_t    flag_rejet_US;
			float32_t u_multisinus;
			float32_t gaz_altitude;
			bool_t    Flag_multisinus;
			bool_t    Flag_multisinus_debut;
		} navdata_kalman_pressure_t;

		typedef struct navdata_zimmu_3000_t {
			uint16_t   tag;
			uint16_t   size;

			int32_t vzimmuLSB;
			float32_t vzfind;

		} navdata_zimmu_3000_t;

		typedef struct _navdata_phys_measures_t {
			uint16_t   tag;
			uint16_t   size;

			float32_t   accs_temp;
			uint16_t    gyro_temp;
			float32_t   phys_accs[NB_ACCS];
			float32_t   phys_gyros[NB_GYROS];
			uint32_t    alim3V3;              // 3.3volt alim [LSB]
			uint32_t    vrefEpson;            // ref volt Epson gyro [LSB]
			uint32_t    vrefIDG;              // ref volt IDG gyro [LSB]
		} navdata_phys_measures_t;
		typedef struct _navdata_gyros_offsets_t {
			uint16_t   tag;
			uint16_t   size;

			float32_t offset_g[NB_GYROS];
		} navdata_gyros_offsets_t;

		typedef struct _navdata_euler_angles_t {
			uint16_t   tag;
			uint16_t   size;

			float32_t   theta_a;
			float32_t   phi_a;
		} navdata_euler_angles_t;


		typedef struct _navdata_references_t {
			uint16_t   tag;
			uint16_t   size;

			int32_t   ref_theta;
			int32_t   ref_phi;
			int32_t   ref_theta_I;
			int32_t   ref_phi_I;
			int32_t   ref_pitch;
			int32_t   ref_roll;
			int32_t   ref_yaw;
			int32_t   ref_psi;

			float32_t vx_ref;
			float32_t vy_ref;
			float32_t theta_mod;
			float32_t phi_mod;

			float32_t k_v_x;
			float32_t k_v_y;
			uint32_t  k_mode;

			float32_t ui_time;
			float32_t ui_theta;
			float32_t ui_phi;
			float32_t ui_psi;
			float32_t ui_psi_accuracy;
			int32_t ui_seq;

		} navdata_references_t;


		typedef struct _navdata_trims_t {
			uint16_t   tag;
			uint16_t   size;

			float32_t angular_rates_trim_r;
			float32_t euler_angles_trim_theta;
			float32_t euler_angles_trim_phi;
		} navdata_trims_t;

		typedef struct _navdata_rc_references_t {
			uint16_t   tag;
			uint16_t   size;

			int32_t    rc_ref_pitch;
			int32_t    rc_ref_roll;
			int32_t    rc_ref_yaw;
			int32_t    rc_ref_gaz;
			int32_t    rc_ref_ag;
		} navdata_rc_references_t;


		typedef struct _navdata_pwm_t {
			uint16_t   tag;
			uint16_t   size;

			uint8_t     motor1;
			uint8_t     motor2;
			uint8_t     motor3;
			uint8_t     motor4;
			uint8_t	  sat_motor1;
			uint8_t	  sat_motor2;
			uint8_t	  sat_motor3;
			uint8_t	  sat_motor4;
			float32_t   gaz_feed_forward;
			float32_t   gaz_altitude;
			float32_t   altitude_integral;
			float32_t   vz_ref;
			int32_t     u_pitch;
			int32_t     u_roll;
			int32_t     u_yaw;
			float32_t   yaw_u_I;
			int32_t     u_pitch_planif;
			int32_t     u_roll_planif;
			int32_t     u_yaw_planif;
			float32_t   u_gaz_planif;
			uint16_t    current_motor1;
			uint16_t    current_motor2;
			uint16_t    current_motor3;
			uint16_t    current_motor4;
			//WARNING: new navdata (FC 26/07/2011)
			float32_t 	altitude_prop;
			float32_t 	altitude_der;
		} navdata_pwm_t;


		typedef struct _navdata_altitude_t {
			uint16_t   tag;
			uint16_t   size;

			int32_t   altitude_vision;
			float32_t altitude_vz;
			int32_t   altitude_ref;
			int32_t   altitude_raw;

			float32_t		obs_accZ;
			float32_t 	obs_alt;
			vector31_t 	obs_x;
			uint32_t 		obs_state;
			vector21_t	est_vb;
			uint32_t 		est_state;

		}  navdata_altitude_t;


		typedef struct _navdata_vision_raw_t {
			uint16_t   tag;
			uint16_t   size;

			float32_t vision_tx_raw;
			float32_t vision_ty_raw;
			float32_t vision_tz_raw;
		}  navdata_vision_raw_t;


		typedef struct _navdata_vision_t {
			uint16_t   tag;
			uint16_t   size;

			uint32_t   vision_state;
			int32_t    vision_misc;
			float32_t  vision_phi_trim;
			float32_t  vision_phi_ref_prop;
			float32_t  vision_theta_trim;
			float32_t  vision_theta_ref_prop;

			int32_t    new_raw_picture;
			float32_t  theta_capture;
			float32_t  phi_capture;
			float32_t  psi_capture;
			int32_t    altitude_capture;
			uint32_t   time_capture;     // time in TSECDEC format (see config.h)
			velocities_t body_v;

			float32_t  delta_phi;
			float32_t  delta_theta;
			float32_t  delta_psi;

			uint32_t  gold_defined;
			uint32_t  gold_reset;
			float32_t gold_x;
			float32_t gold_y;
		}  navdata_vision_t;


		typedef struct _navdata_vision_perf_t {
			uint16_t   tag;
			uint16_t   size;

			// +44 bytes
			float32_t  time_szo;
			float32_t  time_corners;
			float32_t  time_compute;
			float32_t  time_tracking;
			float32_t  time_trans;
			float32_t  time_update;
			float32_t  time_custom[NAVDATA_MAX_CUSTOM_TIME_SAVE];
		} navdata_vision_perf_t;


		typedef struct _navdata_trackers_send_t {
			uint16_t   tag;
			uint16_t   size;

			int32_t locked[DEFAULT_NB_TRACKERS_WIDTH * DEFAULT_NB_TRACKERS_HEIGHT];
			screen_point_t point[DEFAULT_NB_TRACKERS_WIDTH * DEFAULT_NB_TRACKERS_HEIGHT];
		} navdata_trackers_send_t;


		typedef struct _navdata_vision_detect_t {
			/* !! Change the function 'navdata_server_reset_vision_detect()' if this structure is modified !! */
			uint16_t   tag;
			uint16_t   size;

			uint32_t   nb_detected;
			uint32_t   type[NB_NAVDATA_DETECTION_RESULTS];
			uint32_t   xc[NB_NAVDATA_DETECTION_RESULTS];
			uint32_t   yc[NB_NAVDATA_DETECTION_RESULTS];
			uint32_t   width[NB_NAVDATA_DETECTION_RESULTS];
			uint32_t   height[NB_NAVDATA_DETECTION_RESULTS];
			uint32_t   dist[NB_NAVDATA_DETECTION_RESULTS];
			float32_t  orientation_angle[NB_NAVDATA_DETECTION_RESULTS];
			matrix33_t rotation[NB_NAVDATA_DETECTION_RESULTS];
			vector31_t translation[NB_NAVDATA_DETECTION_RESULTS];
			uint32_t   camera_source[NB_NAVDATA_DETECTION_RESULTS];
		}  navdata_vision_detect_t;

		typedef struct _navdata_vision_of_t {
			uint16_t   tag;
			uint16_t   size;

			float32_t   of_dx[5];
			float32_t   of_dy[5];
		}  navdata_vision_of_t;


		typedef struct _navdata_watchdog_t {
			uint16_t   tag;
			uint16_t   size;

			// +4 bytes
			int32_t    watchdog;
		} navdata_watchdog_t;

		typedef struct _navdata_adc_data_frame_t {
			uint16_t  tag;
			uint16_t  size;

			uint32_t  version;
			uint8_t   data_frame[32];
		} navdata_adc_data_frame_t;

		typedef struct _navdata_video_stream_t {
			uint16_t  tag;
			uint16_t  size;

			uint8_t 	quant;			// quantizer reference used to encode frame [1:31]
			uint32_t	frame_size;		// frame size (bytes)
			uint32_t	frame_number;	// frame index
			uint32_t	atcmd_ref_seq;  // atmcd ref sequence number
			uint32_t	atcmd_mean_ref_gap;	// mean time between two consecutive atcmd_ref (ms)
			float32_t atcmd_var_ref_gap;
			uint32_t	atcmd_ref_quality; // estimator of atcmd link quality

			// drone2
			uint32_t  out_bitrate;     // measured out throughput from the video tcp socket
			uint32_t  desired_bitrate; // last frame size generated by the video encoder

			// misc temporary data
			int32_t  data1;
			int32_t  data2;
			int32_t  data3;
			int32_t  data4;
			int32_t  data5;

			// queue usage
			uint32_t tcp_queue_level;
			uint32_t fifo_queue_level;

		} navdata_video_stream_t;

		typedef enum {
			NAVDATA_HDVIDEO_STORAGE_FIFO_IS_FULL = (1 << 0),
			NAVDATA_HDVIDEO_USBKEY_IS_PRESENT = (1 << 8),
			NAVDATA_HDVIDEO_USBKEY_IS_RECORDING = (1 << 9),
			NAVDATA_HDVIDEO_USBKEY_IS_FULL = (1 << 10)
		}_navdata_hdvideo_states_t;


		typedef struct _navdata_hdvideo_stream_t {
			uint16_t  tag;
			uint16_t  size;

			uint32_t hdvideo_state;
			uint32_t storage_fifo_nb_packets;
			uint32_t storage_fifo_size;
			uint32_t usbkey_size;         /*! USB key in kbytes - 0 if no key present */
			uint32_t usbkey_freespace;    /*! USB key free space in kbytes - 0 if no key present */
			uint32_t frame_number;        /*! 'frame_number' PaVE field of the frame starting to be encoded for the HD stream */
			uint32_t usbkey_remaining_time; /*! time in seconds */

		}  navdata_hdvideo_stream_t;


		typedef struct _navdata_games_t {
			uint16_t  tag;
			uint16_t  size;
			uint32_t  double_tap_counter;
			uint32_t  finish_line_counter;
		} navdata_games_t;

		typedef struct _navdata_wifi_t {
			uint16_t  tag;
			uint16_t  size;
			uint32_t link_quality;
		} navdata_wifi_t;

	}
}
#endif // _TK_NAVDATA_COMMON_H_