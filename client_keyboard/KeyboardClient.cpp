
#include "KeyboardClient.h"

KeyboardClient::KeyboardClient()
	: virtual_left_id_(0),
	  virtual_right_id_(0),
	  openvr_left_id_(0),
	  openvr_right_id_(0)
{
	memset(&controller_state_, 0, sizeof(controller_state_));
	memset(&hmd_offset_, 0, sizeof(hmd_offset_));
	memset(&hmd_pose, 0, sizeof(hmd_pose[vr::k_unMaxTrackedDeviceCount]));
	hmd_offset_.worldFromDriverRotationOffset = { 1.0, 0.0, 0.0, 0.0 };
	hmd_offset_.driverFromHeadRotationOffset = { 1.0, 0.0, 0.0, 0.0 };
	hmd_offset_.deviceRotationOffset = { 1.0, 0.0, 0.0, 0.0 };
}

KeyboardClient::~KeyboardClient()
{}

void __cdecl KeyboardClient::ListenerWrapper(void* p)
{
	static_cast<KeyboardClient*>(p)->KeyboardEventListener();
}

void KeyboardClient::KeyboardEventListener()
{
	hmd_offset_.offsetsEnabled = true;

	try {
		input_emulator_.connect();
	}
	catch (std::exception& e) {
		LOG(e.what());
	}
	if (run) {

		input_emulator_.enableDeviceOffsets(vr::k_unTrackedDeviceIndex_Hmd, true);

		virtual_left_id_ = input_emulator_.addVirtualDevice(vrinputemulator::VirtualDeviceType::TrackedController, "virtual_left_controller", true);
		input_emulator_.setVirtualDeviceProperty(virtual_left_id_, vr::Prop_DeviceClass_Int32, (int32_t)vr::TrackedDeviceClass_Controller);
		input_emulator_.setVirtualDeviceProperty(virtual_left_id_, vr::Prop_DeviceIsWireless_Bool, (bool)1);
		input_emulator_.setVirtualDeviceProperty(virtual_left_id_, vr::Prop_SupportedButtons_Uint64, (uint64_t)12884901895);
		input_emulator_.setVirtualDeviceProperty(virtual_left_id_, vr::Prop_Axis0Type_Int32, (int32_t)vr::k_eControllerAxis_TrackPad);
		input_emulator_.setVirtualDeviceProperty(virtual_left_id_, vr::Prop_Axis1Type_Int32, (int32_t)vr::k_eControllerAxis_Trigger);
		input_emulator_.setVirtualDeviceProperty(virtual_left_id_, vr::Prop_TrackingFirmwareVersion_String, std::string("1465809478 htcvrsoftware@firmware-win32 2016-06-13 FPGA 1.6/0/0 VRC 1465809477 Radio 1466630404"));
		input_emulator_.setVirtualDeviceProperty(virtual_left_id_, vr::Prop_HardwareRevision_String, std::string("product 129 rev 1.5.0 lot 2000/0/0 0"));
		input_emulator_.setVirtualDeviceProperty(virtual_left_id_, vr::Prop_HardwareRevision_Uint64, (uint64_t)2164327680);
		input_emulator_.setVirtualDeviceProperty(virtual_left_id_, vr::Prop_FirmwareVersion_Uint64, (uint64_t)1465809478);		
		input_emulator_.setVirtualDeviceProperty(virtual_left_id_, vr::Prop_RenderModelName_String, std::string("vr_controller_vive_1_5"));
		input_emulator_.setVirtualDeviceProperty(virtual_left_id_, vr::Prop_ManufacturerName_String, std::string("HTC"));
		input_emulator_.setVirtualDeviceProperty(virtual_left_id_, vr::Prop_ModelNumber_String, std::string("Vive Controller MV"));
		input_emulator_.setVirtualDeviceProperty(virtual_left_id_, vr::Prop_IconPathName_String, std::string("icon"));
		input_emulator_.setVirtualDeviceProperty(virtual_left_id_, vr::Prop_NamedIconPathDeviceOff_String, std::string("{htc}controller_status_off.png"));
		input_emulator_.setVirtualDeviceProperty(virtual_left_id_, vr::Prop_NamedIconPathDeviceSearching_String, std::string("{htc}controller_status_searching.gif"));
		input_emulator_.setVirtualDeviceProperty(virtual_left_id_, vr::Prop_NamedIconPathDeviceSearchingAlert_String, std::string("{htc}controller_status_searching_alert.gif"));
		input_emulator_.setVirtualDeviceProperty(virtual_left_id_, vr::Prop_NamedIconPathDeviceReady_String, std::string("{htc}controller_status_ready.png"));
		input_emulator_.setVirtualDeviceProperty(virtual_left_id_, vr::Prop_NamedIconPathDeviceReadyAlert_String, std::string("{htc}controller_status_ready_alert.png"));
		input_emulator_.setVirtualDeviceProperty(virtual_left_id_, vr::Prop_NamedIconPathDeviceNotReady_String, std::string("{htc}controller_status_error.png"));
		input_emulator_.setVirtualDeviceProperty(virtual_left_id_, vr::Prop_NamedIconPathDeviceStandby_String, std::string("{htc}controller_status_standby.png"));
		input_emulator_.setVirtualDeviceProperty(virtual_left_id_, vr::Prop_NamedIconPathDeviceAlertLow_String, std::string("{htc}controller_status_ready_low.png"));
		input_emulator_.publishVirtualDevice(virtual_left_id_);

		virtual_right_id_ = input_emulator_.addVirtualDevice(vrinputemulator::VirtualDeviceType::TrackedController, "virtual_right_controller", true);
		input_emulator_.setVirtualDeviceProperty(virtual_right_id_, vr::Prop_DeviceClass_Int32, (int32_t)vr::TrackedDeviceClass_Controller);
		input_emulator_.setVirtualDeviceProperty(virtual_right_id_, vr::Prop_DeviceIsWireless_Bool, (bool)1);
		input_emulator_.setVirtualDeviceProperty(virtual_right_id_, vr::Prop_SupportedButtons_Uint64, (uint64_t)12884901895);
		input_emulator_.setVirtualDeviceProperty(virtual_right_id_, vr::Prop_Axis0Type_Int32, (int32_t)vr::k_eControllerAxis_TrackPad);
		input_emulator_.setVirtualDeviceProperty(virtual_right_id_, vr::Prop_Axis1Type_Int32, (int32_t)vr::k_eControllerAxis_Trigger);
		input_emulator_.setVirtualDeviceProperty(virtual_right_id_, vr::Prop_TrackingFirmwareVersion_String, std::string("1465809478 htcvrsoftware@firmware-win32 2016-06-13 FPGA 1.6/0/0 VRC 1465809477 Radio 1466630404"));
		input_emulator_.setVirtualDeviceProperty(virtual_right_id_, vr::Prop_HardwareRevision_String, std::string("product 129 rev 1.5.0 lot 2000/0/0 0"));
		input_emulator_.setVirtualDeviceProperty(virtual_right_id_, vr::Prop_HardwareRevision_Uint64, (uint64_t)2164327680);
		input_emulator_.setVirtualDeviceProperty(virtual_right_id_, vr::Prop_FirmwareVersion_Uint64, (uint64_t)1465809478);
		input_emulator_.setVirtualDeviceProperty(virtual_right_id_, vr::Prop_RenderModelName_String, std::string("vr_controller_vive_1_5"));
		input_emulator_.setVirtualDeviceProperty(virtual_right_id_, vr::Prop_ManufacturerName_String, std::string("HTC"));
		input_emulator_.setVirtualDeviceProperty(virtual_right_id_, vr::Prop_ModelNumber_String, std::string("Vive Controller MV"));
		input_emulator_.setVirtualDeviceProperty(virtual_right_id_, vr::Prop_IconPathName_String, std::string("icon"));
		input_emulator_.setVirtualDeviceProperty(virtual_right_id_, vr::Prop_NamedIconPathDeviceOff_String, std::string("{htc}controller_status_off.png"));
		input_emulator_.setVirtualDeviceProperty(virtual_right_id_, vr::Prop_NamedIconPathDeviceSearching_String, std::string("{htc}controller_status_searching.gif"));
		input_emulator_.setVirtualDeviceProperty(virtual_right_id_, vr::Prop_NamedIconPathDeviceSearchingAlert_String, std::string("{htc}controller_status_searching_alert.gif"));
		input_emulator_.setVirtualDeviceProperty(virtual_right_id_, vr::Prop_NamedIconPathDeviceReady_String, std::string("{htc}controller_status_ready.png"));
		input_emulator_.setVirtualDeviceProperty(virtual_right_id_, vr::Prop_NamedIconPathDeviceReadyAlert_String, std::string("{htc}controller_status_ready_alert.png"));
		input_emulator_.setVirtualDeviceProperty(virtual_right_id_, vr::Prop_NamedIconPathDeviceNotReady_String, std::string("{htc}controller_status_error.png"));
		input_emulator_.setVirtualDeviceProperty(virtual_right_id_, vr::Prop_NamedIconPathDeviceStandby_String, std::string("{htc}controller_status_standby.png"));
		input_emulator_.setVirtualDeviceProperty(virtual_right_id_, vr::Prop_NamedIconPathDeviceAlertLow_String, std::string("{htc}controller_status_ready_low.png"));
		input_emulator_.publishVirtualDevice(virtual_right_id_);

		auto pose_l = input_emulator_.getVirtualDevicePose(virtual_left_id_);
		if (pose_l.deviceIsConnected != true) {
			pose_l.deviceIsConnected = true;
			pose_l.poseIsValid = true;
			input_emulator_.setVirtualDevicePose(virtual_left_id_, pose_l);
		}
		auto pose_r = input_emulator_.getVirtualDevicePose(virtual_right_id_);
		if (pose_r.deviceIsConnected != true) {
			pose_r.deviceIsConnected = true;
			pose_r.poseIsValid = true;
			input_emulator_.setVirtualDevicePose(virtual_right_id_, pose_r);
		}
		//for (int id = 0; id < vr::k_unMaxTrackedDeviceCount; id++) {
		//	auto device_class = vr::VRSystem()->GetTrackedDeviceClass(id);
		//	if (device_class != vr::TrackedDeviceClass_Invalid) {
		//		vr::ETrackedPropertyError pError;
		//		char serial[1028] = { '\0' };
		//		vr::VRSystem()->GetStringTrackedDeviceProperty(id, vr::Prop_SerialNumber_String, serial, 1028, &pError);
		//		char manufacturer[1028] = { '\0' };
		//		vr::VRSystem()->GetStringTrackedDeviceProperty(id, vr::Prop_ManufacturerName_String, manufacturer, 1028, &pError);
		//		char model[1028] = { '\0' };
		//		vr::VRSystem()->GetStringTrackedDeviceProperty(id, vr::Prop_ModelNumber_String, model, 1028, &pError);
		//		std::string device_clas_str;
		//		if (device_class == vr::TrackedDeviceClass_HMD) {
		//			device_clas_str = "HMD";
		//		}
		//		else if (device_class == vr::TrackedDeviceClass_Controller) {
		//			device_clas_str = "Controller";
		//		}
		//		else {
		//			device_clas_str = "Others";
		//		}
		//		std::string log = "All Device " + std::to_string(id) + " [" + device_clas_str + "]: " + manufacturer + " - " + model
		//			+ " [" + serial + "]\n";

		//		LOG(log.c_str());
		//	}
		//}

		//int deviceCount = input_emulator_.getVirtualDeviceCount();
		//for (int i = 0; i < deviceCount; ++i) {
		//	auto deviceInfo = input_emulator_.getVirtualDeviceInfo(i);
		//	std::string deviceType;
		//	switch (deviceInfo.deviceType) {
		//	case vrinputemulator::VirtualDeviceType::TrackedController:
		//		deviceType = "TrackedController";
		//		break;
		//	default:
		//		deviceType = "Unknown";
		//		break;
		//	}
		//	std::string openVRIdStr;
		//	if (deviceInfo.openvrDeviceId == vr::k_unTrackedDeviceIndexInvalid) {
		//		openVRIdStr = "<none>";
		//	}
		//	else {
		//		if (deviceInfo.deviceSerial == "virtual_left_controller") {
		//			openvr_left_id_ = deviceInfo.openvrDeviceId;
		//		}
		//		else if (deviceInfo.deviceSerial == "virtual_right_controller") {
		//			openvr_right_id_ = deviceInfo.openvrDeviceId;
		//		}
		//		openVRIdStr = std::to_string(deviceInfo.openvrDeviceId);
		//	}
		//	std::string log = "Virtual Device " + std::to_string(i) + " [" + deviceType + "]: Serial " + deviceInfo.deviceSerial + ", OpenVR Id " + openVRIdStr + "\n";
		//	LOG(log.c_str());
		//}
	}

	while (run)
	{
		short turn_up = GetAsyncKeyState(VK_F1) & 0x8000;
		short turn_left = GetAsyncKeyState(VK_F3) & 0x8000;
		short turn_down = GetAsyncKeyState(VK_F2) & 0x8000;
		short turn_right = GetAsyncKeyState(VK_F4) & 0x8000;

		short up = GetAsyncKeyState(VK_F5) & 0x8000;
		short down = GetAsyncKeyState(VK_F6) & 0x8000;
		short left = GetAsyncKeyState(VK_F7) & 0x8000;
		short right = GetAsyncKeyState(VK_F8) & 0x8000;
		short forward = GetAsyncKeyState(VK_F9) & 0x8000;
		short back = GetAsyncKeyState(VK_F10) & 0x8000;

		short stick_up = GetAsyncKeyState(VK_NUMPAD8) & 0x8000;
		short stick_down = GetAsyncKeyState(VK_NUMPAD5) & 0x8000;
		short stick_left = GetAsyncKeyState(VK_NUMPAD4) & 0x8000;
		short stick_right = GetAsyncKeyState(VK_NUMPAD6) & 0x8000;

		short dpad_up = GetAsyncKeyState(VK_NUMPAD2) & 0x8000;
		short dpad_down = GetAsyncKeyState(VK_NUMPAD0) & 0x8000;
		short dpad_left = GetAsyncKeyState(VK_NUMPAD1) & 0x8000;
		short dpad_right = GetAsyncKeyState(VK_NUMPAD3) & 0x8000;

		short trigger = GetAsyncKeyState(VK_CONTROL) & 0x8000;
		short side_button = GetAsyncKeyState(VK_SHIFT) & 0x8000;

		short menu = GetAsyncKeyState(VK_MENU) & 0x8000;

		if (turn_up && !turn_down)
			UpdateHMDOrientationOffset(kAxisX, kHeadRotateSpeed);
		else if (turn_down && !turn_up)
			UpdateHMDOrientationOffset(kAxisX, -kHeadRotateSpeed);
		if (turn_left && !turn_right)
			UpdateHMDOrientationOffset(kAxisY, kHeadRotateSpeed);
		else if (turn_right && !turn_left)
			UpdateHMDOrientationOffset(kAxisY, -kHeadRotateSpeed);

		if (up && !down)
			UpdateHMDPositionOffset(0, kHeadTranslateSpeed, 0);
		else if (down && !up)
			UpdateHMDPositionOffset(0, -kHeadTranslateSpeed, 0);
		if (left && !right)
			UpdateHMDPositionOffset(-kHeadTranslateSpeed, 0, 0);
		else if (right && !left)
			UpdateHMDPositionOffset(kHeadTranslateSpeed, 0, 0);
		if (forward && !back)
			UpdateHMDPositionOffset(0, 0, -kHeadTranslateSpeed);
		else if (back && !forward)
			UpdateHMDPositionOffset(0, 0, kHeadTranslateSpeed);
			

		if (menu) {
			controller_state_.ulButtonPressed |= vr::ButtonMaskFromId(vr::k_EButton_ApplicationMenu);
			controller_state_.unPacketNum = vr::k_EButton_ApplicationMenu;
		}
		else {
			controller_state_.ulButtonPressed &= ~vr::ButtonMaskFromId(vr::k_EButton_ApplicationMenu);
			controller_state_.unPacketNum = vr::k_EButton_ApplicationMenu + kButtonPacketOffset;
		}

		if (side_button) {
			controller_state_.ulButtonPressed |= vr::ButtonMaskFromId(vr::k_EButton_Grip);
			controller_state_.unPacketNum = vr::k_EButton_Grip;
		}
		else {
			controller_state_.ulButtonPressed &= ~vr::ButtonMaskFromId(vr::k_EButton_Grip);
			controller_state_.unPacketNum = vr::k_EButton_Grip + kButtonPacketOffset;
		}

		if (stick_up && !stick_down) {
			controller_state_.rAxis[0].y = 0.9f;
			controller_state_.ulButtonTouched |= vr::ButtonMaskFromId(vr::k_EButton_DPad_Up);
			controller_state_.ulButtonTouched |= vr::ButtonMaskFromId(vr::k_EButton_SteamVR_Touchpad);
			controller_state_.unPacketNum = vr::k_EButton_DPad_Up;
		}
		else if (stick_down && !stick_up) {
			controller_state_.rAxis[0].y = -0.9f;
			controller_state_.ulButtonTouched |= vr::ButtonMaskFromId(vr::k_EButton_DPad_Down);
			controller_state_.ulButtonTouched |= vr::ButtonMaskFromId(vr::k_EButton_SteamVR_Touchpad);
			controller_state_.unPacketNum = vr::k_EButton_DPad_Down;
		}
		else if (!stick_up || !stick_down) {
			controller_state_.rAxis[0].y = 0.1f;
			controller_state_.ulButtonTouched &= ~vr::ButtonMaskFromId(vr::k_EButton_DPad_Up);
			controller_state_.ulButtonTouched &= ~vr::ButtonMaskFromId(vr::k_EButton_DPad_Down);
			controller_state_.ulButtonTouched &= ~vr::ButtonMaskFromId(vr::k_EButton_SteamVR_Touchpad);
			controller_state_.unPacketNum = vr::k_EButton_DPad_Up + vr::k_EButton_DPad_Down;
		}
		if (stick_left && !stick_right) {
			controller_state_.rAxis[0].x = -0.9f;
			controller_state_.ulButtonTouched |= vr::ButtonMaskFromId(vr::k_EButton_DPad_Left);
			controller_state_.ulButtonTouched |= vr::ButtonMaskFromId(vr::k_EButton_SteamVR_Touchpad);
			controller_state_.unPacketNum = vr::k_EButton_DPad_Left;
		}
		else if (stick_right && !stick_left) {
			controller_state_.rAxis[0].x = 0.9f;
			controller_state_.ulButtonTouched |= vr::ButtonMaskFromId(vr::k_EButton_DPad_Right);
			controller_state_.ulButtonTouched |= vr::ButtonMaskFromId(vr::k_EButton_SteamVR_Touchpad);
			controller_state_.unPacketNum = vr::k_EButton_DPad_Right;
		}
		else if (!stick_left || !stick_right) {
			controller_state_.rAxis[0].x = 0.1f;
			controller_state_.ulButtonTouched &= ~vr::ButtonMaskFromId(vr::k_EButton_DPad_Left);
			controller_state_.ulButtonTouched &= ~vr::ButtonMaskFromId(vr::k_EButton_DPad_Right);
			controller_state_.ulButtonTouched &= ~vr::ButtonMaskFromId(vr::k_EButton_SteamVR_Touchpad);
			controller_state_.unPacketNum = vr::k_EButton_DPad_Left + vr::k_EButton_DPad_Right;
		}

		if (dpad_up && !dpad_down) {
			controller_state_.ulButtonPressed |= vr::ButtonMaskFromId(vr::k_EButton_DPad_Up);
			controller_state_.ulButtonPressed |= vr::ButtonMaskFromId(vr::k_EButton_SteamVR_Touchpad);
			controller_state_.unPacketNum = vr::k_EButton_DPad_Up + kButtonPacketOffset;
		}
		else if (dpad_down && !dpad_up) {
			controller_state_.ulButtonPressed |= vr::ButtonMaskFromId(vr::k_EButton_DPad_Down);
			controller_state_.ulButtonPressed |= vr::ButtonMaskFromId(vr::k_EButton_SteamVR_Touchpad);
			controller_state_.unPacketNum = vr::k_EButton_DPad_Down + kButtonPacketOffset;
		}
		else if (!dpad_up || !dpad_down) {
			controller_state_.ulButtonPressed &= ~vr::ButtonMaskFromId(vr::k_EButton_DPad_Up);
			controller_state_.ulButtonPressed &= ~vr::ButtonMaskFromId(vr::k_EButton_DPad_Down);
			controller_state_.ulButtonPressed &= ~vr::ButtonMaskFromId(vr::k_EButton_SteamVR_Touchpad);
			controller_state_.unPacketNum = vr::k_EButton_DPad_Up + vr::k_EButton_DPad_Down + kButtonPacketOffset;
		}
		if (dpad_left && !dpad_right) {
			controller_state_.ulButtonPressed |= vr::ButtonMaskFromId(vr::k_EButton_DPad_Left);
			controller_state_.ulButtonPressed |= vr::ButtonMaskFromId(vr::k_EButton_SteamVR_Touchpad);
			controller_state_.unPacketNum = vr::k_EButton_DPad_Left + kButtonPacketOffset;
		}
		else if (dpad_right && !dpad_left) {
			controller_state_.ulButtonPressed |= vr::ButtonMaskFromId(vr::k_EButton_DPad_Right);
			controller_state_.ulButtonPressed |= vr::ButtonMaskFromId(vr::k_EButton_SteamVR_Touchpad);
			controller_state_.unPacketNum = vr::k_EButton_DPad_Right + kButtonPacketOffset;
		}
		else if (!dpad_left || !dpad_right) {
			controller_state_.ulButtonPressed &= ~vr::ButtonMaskFromId(vr::k_EButton_DPad_Left);
			controller_state_.ulButtonPressed &= ~vr::ButtonMaskFromId(vr::k_EButton_DPad_Right);
			controller_state_.ulButtonPressed &= ~vr::ButtonMaskFromId(vr::k_EButton_SteamVR_Touchpad);
			controller_state_.unPacketNum = vr::k_EButton_DPad_Left + vr::k_EButton_DPad_Right + kButtonPacketOffset;
		}

		if (trigger) {
			controller_state_.rAxis[1].x = 0.96f;
			controller_state_.ulButtonPressed |= vr::ButtonMaskFromId(vr::k_EButton_SteamVR_Trigger);
			controller_state_.unPacketNum = vr::k_EButton_SteamVR_Trigger;
		}
		else {
			controller_state_.rAxis[1].x = 0.0f;
			controller_state_.ulButtonPressed &= ~vr::ButtonMaskFromId(vr::k_EButton_SteamVR_Trigger);
			controller_state_.unPacketNum = vr::k_EButton_SteamVR_Trigger + kButtonPacketOffset;
		}
		
		SetDevicesPose();
		SetControllersState();
	}

	input_emulator_.disconnect();
	_endthread();
}

void KeyboardClient::UpdateHMDOrientationOffset(int axis, float speed)
{
	vr::HmdQuaternion_t temp_quat;
	switch (axis)
	{
	case kAxisX:
		temp_quat = vrmath::quaternionFromRotationX(speed);
		break;
	case kAxisY:
		temp_quat = vrmath::quaternionFromRotationY(speed);
		break;
	case kAxisZ:
		temp_quat = vrmath::quaternionFromRotationZ(speed);
		break;
	default:
		break;
	}
	hmd_offset_.deviceRotationOffset = hmd_offset_.deviceRotationOffset * temp_quat;
}

void KeyboardClient::UpdateHMDPositionOffset(float x_speed, float y_speed, float z_speed)
{
	hmd_offset_.deviceTranslationOffset.v[0] += x_speed;
	hmd_offset_.deviceTranslationOffset.v[1] += y_speed;
	hmd_offset_.deviceTranslationOffset.v[2] += z_speed;
}

//void KeyboardClient::SetControllersState(vr::EVRButtonId button_id, vrinputemulator::ButtonEventType event_type)
//{
//	input_emulator_.openvrButtonEvent(event_type, openvr_left_id_, button_id, 0.0);
//	input_emulator_.openvrButtonEvent(event_type, openvr_right_id_, button_id, 0.0);
//	//input_emulator_.setVirtualControllerState(virtual_left_id_, controller_state_);
//	//input_emulator_.setVirtualControllerState(virtual_right_id_, controller_state_);
//}

void KeyboardClient::SetControllersState()
{
	input_emulator_.setVirtualControllerState(virtual_left_id_, controller_state_);
	//input_emulator_.setVirtualControllerState(virtual_right_id_, controller_state_);
}

//void KeyboardClient::SetControllersAxis(vr::EVRButtonId axis_id)
//{
//	//switch(axis_id) {
//	//case vr::k_EButton_SteamVR_Trigger:
//	//	input_emulator_.openvrAxisEvent(openvr_left_id_, axis_id, controller_state_.rAxis[1]);
//	//	input_emulator_.openvrAxisEvent(openvr_right_id_, axis_id, controller_state_.rAxis[1]);
//	//	break;
//	//case vr::k_EButton_SteamVR_Touchpad:
//	//	input_emulator_.openvrAxisEvent(openvr_left_id_, axis_id, controller_state_.rAxis[0]);
//	//	input_emulator_.openvrAxisEvent(openvr_right_id_, axis_id, controller_state_.rAxis[0]);
//	//	break;
//	//default:
//	//	break;
//	//}
//	
//	input_emulator_.setVirtualControllerState(virtual_left_id_, controller_state_);
//	input_emulator_.setVirtualControllerState(virtual_right_id_, controller_state_);
//}

void KeyboardClient::SetDevicesPose()
{
	input_emulator_.setDriverTranslationOffset(vr::k_unTrackedDeviceIndex_Hmd, hmd_offset_.deviceTranslationOffset);
	input_emulator_.setDriverRotationOffset(vr::k_unTrackedDeviceIndex_Hmd, hmd_offset_.deviceRotationOffset);

	//input_emulator_.setWorldFromDriverRotationOffset(hmd_id_, hmd_offset_.deviceRotationOffset);
	//input_emulator_.setWorldFromDriverTranslationOffset(hmd_id_, hmd_offset_.deviceTranslationOffset);

	//input_emulator_.setDriverFromHeadRotationOffset(hmd_id_, hmd_offset_.deviceRotationOffset);
	//input_emulator_.setDriverFromHeadTranslationOffset(hmd_id_, hmd_offset_.deviceTranslationOffset);

	vr::HmdQuaternion_t hmd_quat= vrmath::quaternionFromRotationMatrix(hmd_pose[0].mDeviceToAbsoluteTracking);

	vr::HmdVector3d_t temp_left_position_offset = vrmath::quaternionRotateVector(hmd_quat, kLeftPositionOffset);
	auto pose_l = input_emulator_.getVirtualDevicePose(virtual_left_id_);
	pose_l.vecPosition[0] = temp_left_position_offset.v[0] + hmd_pose[0].mDeviceToAbsoluteTracking.m[0][3];
	pose_l.vecPosition[1] = temp_left_position_offset.v[1] + hmd_pose[0].mDeviceToAbsoluteTracking.m[1][3];
	pose_l.vecPosition[2] = temp_left_position_offset.v[2] + hmd_pose[0].mDeviceToAbsoluteTracking.m[2][3];
	pose_l.qRotation = hmd_quat;
	pose_l.poseIsValid = true;
	pose_l.result = vr::TrackingResult_Running_OK;
	input_emulator_.setVirtualDevicePose(virtual_left_id_, pose_l);

	vr::HmdVector3d_t temp_right_position_offset = vrmath::quaternionRotateVector(hmd_quat, kRightPositionOffset);
	auto pose_r = input_emulator_.getVirtualDevicePose(virtual_right_id_);
	pose_r.vecPosition[0] = temp_right_position_offset.v[0] + hmd_pose[0].mDeviceToAbsoluteTracking.m[0][3];
	pose_r.vecPosition[1] = temp_right_position_offset.v[1] + hmd_pose[0].mDeviceToAbsoluteTracking.m[1][3];
	pose_r.vecPosition[2] = temp_right_position_offset.v[2] + hmd_pose[0].mDeviceToAbsoluteTracking.m[2][3];
	pose_r.qRotation = hmd_quat;
	pose_r.poseIsValid = true;
	pose_r.result = vr::TrackingResult_Running_OK;
	input_emulator_.setVirtualDevicePose(virtual_right_id_, pose_r);
}
