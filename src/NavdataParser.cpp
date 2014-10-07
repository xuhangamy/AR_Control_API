#include <ardrone/navdata/NavdataParser.h>
#include <ardrone/navdata/common.h>
#include <ardrone/navdata/state.h>
using whu::ardrone::NavdataParser;
#include <stdlib.h>
#include <iostream>
using namespace std;

NavdataParser::NavdataParser(const void* dt,int size){
	set_data(dt, size);
}

bool NavdataParser::set_data(const void* dt, int size){
	// 删除原有数据
	if (data){
		free(data);
		data = nullptr;
	}
	data = malloc(size);
	memcpy(data, dt, size);
	valid = true;
	return true;
}

bool NavdataParser::check_header(){
	if (!valid){ // 如果没有数据 
		return false;
	}
	const navdata_t* navdt = (navdata_t*)data; // 指向数据，获取header
	if (navdt->header!=NAVDATA_HEADER) {
		navdt = nullptr;
		return false;
	}
	navdt = nullptr;
	return true;
}

bool NavdataParser::check_vision() {
	if (!valid) { // 如果没有数据 
		return false;
	}
	const navdata_t* navdt = (navdata_t*)data; // 指向数据，获取vision
	if (navdt->vision_defined!=true_t) {
		navdt = nullptr;
		return false;
	}
	navdt = nullptr;
	return true;
}

bool NavdataParser::state_fly() {
	const navdata_t* navdt = (navdata_t*)data;
	return ardrone_get_mask(navdt->ardrone_state,ARDRONE_FLY_MASK)==true_t;
}

bool NavdataParser::state_video() {
	const navdata_t* navdt = (navdata_t*)data;
	return ardrone_get_mask(navdt->ardrone_state, ARDRONE_VIDEO_MASK) == true_t;
}

bool NavdataParser::state_vision() {
	const navdata_t* navdt = (navdata_t*)data;
	return ardrone_get_mask(navdt->ardrone_state, ARDRONE_VISION_MASK) == true_t;
}

bool NavdataParser::state_control() {
	const navdata_t* navdt = (navdata_t*)data;
	return ardrone_get_mask(navdt->ardrone_state, ARDRONE_CONTROL_MASK) == true_t;
}

bool NavdataParser::state_altitude() {
	const navdata_t* navdt = (navdata_t*)data;
	return ardrone_get_mask(navdt->ardrone_state, ARDRONE_ALTITUDE_MASK) == true_t;
}

bool NavdataParser::state_camera() {
	const navdata_t* navdt = (navdata_t*)data;
	return ardrone_get_mask(navdt->ardrone_state, ARDRONE_CAMERA_MASK) == true_t;
}

bool NavdataParser::state_comlost() {
	const navdata_t* navdt = (navdata_t*)data;
	return ardrone_get_mask(navdt->ardrone_state, ARDRONE_COM_LOST_MASK) == true_t;
}

//  Navdata demo : (0) All navdata, (1) only navdata demo
bool NavdataParser::state_navdata_demo() {
	const navdata_t* navdt = (navdata_t*)data;
	return ardrone_get_mask(navdt->ardrone_state, ARDRONE_NAVDATA_DEMO_MASK) == true_t;
}

bool NavdataParser::state_bootstrap() {
	const navdata_t* navdt = (navdata_t*)data;
	return ardrone_get_mask(navdt->ardrone_state, ARDRONE_NAVDATA_BOOTSTRAP) == true_t;
}

bool NavdataParser::state_com_watchdog() {
	const navdata_t* navdt = (navdata_t*)data;
	return ardrone_get_mask(navdt->ardrone_state, ARDRONE_COM_WATCHDOG_MASK) == true_t;
}

bool NavdataParser::state_emergency() {
	const navdata_t* navdt = (navdata_t*)data;
	return ardrone_get_mask(navdt->ardrone_state, ARDRONE_EMERGENCY_MASK) == true_t;
}

bool NavdataParser::read_option_list() {
	const navdata_t* navdt = (navdata_t*)data;
	const navdata_option_t* option = navdt->options;
	while (true) {
		if (option->tag==NAVDATA_DEMO_TAG) {
			const navdata_demo_t* demo = (navdata_demo_t*)option;
			idata.vx = demo->vx;
			idata.vy = demo->vy;
			idata.vz = demo->vz;
			idata.theta = demo->theta;
			idata.phi = demo->phi;
			idata.psi = demo->psi;
			idata.altitude = demo->altitude;
			idata.num_frames = demo->num_frames;
			idata.voltage = demo->vbat_flying_precentage;
			break;
		}
		if (option->tag==NAVDATA_CKS_TAG) {
			break;
		}
	}
	return true;
}