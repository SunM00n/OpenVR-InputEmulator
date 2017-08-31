
#include "Utils.h"

#include "KeyboardClient.h"

FILE* gLogFile = nullptr;

int main() {

	vr::EVRInitError peError;
	vr::VR_Init(&peError, vr::VRApplication_Background);
	if (peError != vr::VRInitError_None) {
		std::cout << "OpenVR Error: " << vr::VR_GetVRInitErrorAsEnglishDescription(peError) << std::endl;
		exit(-2);
	}

	CHAR log_path[MAX_PATH];

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, log_path)))
	{
		strcat_s(log_path, "\\VRInputEmulator");

		BOOL exists = PathFileExists(log_path);
		if (!exists)
			exists = CreateDirectory(log_path, NULL);

		strcat_s(log_path, "\\VRInputEmulator.txt");
		if (exists)
			fopen_s(&gLogFile, log_path, "w");
	}

	KeyboardClient* keyboard_client = new KeyboardClient();
	keyboard_client->run = true;
	_beginthread(&KeyboardClient::ListenerWrapper, 0, static_cast<void*>(keyboard_client));

	vr::VREvent_t vr_event;
	bool stop_loop = false;
	// Start a new loop thread for keyboard event listener
	while (!stop_loop) {
		if (vr::VRSystem()->PollNextEvent(&vr_event, sizeof(vr::VREvent_t))) {
			if (vr_event.eventType == vr::VREvent_Quit || vr_event.eventType == vr::VREvent_DriverRequestedQuit) {
				stop_loop = true;
				keyboard_client->run = false;
			}
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		vr::VRSystem()->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseRawAndUncalibrated, 0, keyboard_client->hmd_pose, 1);
	}
	//delete keyboard_client;
	fclose(gLogFile);
	delete keyboard_client;
	vr::VR_Shutdown();
	
	return 0;
}

