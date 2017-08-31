#pragma once

#include "Utils.h"

class KeyboardClient {
public:
	KeyboardClient();
	~KeyboardClient();

	static void __cdecl ListenerWrapper(void* p);

	bool run;
	vr::TrackedDevicePose_t hmd_pose[vr::k_unMaxTrackedDeviceCount];

private:
	vrinputemulator::VRInputEmulator input_emulator_;

	vrinputemulator::DeviceOffsets hmd_offset_;
	vr::VRControllerState_t controller_state_;

	int virtual_left_id_;
	int openvr_left_id_;

	int virtual_right_id_;
	int openvr_right_id_;

	void KeyboardEventListener();

	void SetDevicesPose();

	//void SetControllersState(vr::EVRButtonId button_id, vrinputemulator::ButtonEventType event_type);
	//void SetControllersAxis(vr::EVRButtonId axis_id);
	void SetControllersState();

	void UpdateHMDOrientationOffset(int axis, float speed);
	void UpdateHMDPositionOffset(float x_speed, float y_speed, float z_speed);
};