#pragma once

#include <iostream>
#include <openvr.h>
#include <openvr_math.h>
#include <vrinputemulator.h>
#include <vrinputemulator_types.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <stdio.h>
#include <process.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#include <Shlobj.h>
#include <thread>

extern FILE* gLogFile;
#define LOG(x, ...) if (gLogFile) fprintf(gLogFile, x, __VA_ARGS__); \
					printf(x, __VA_ARGS__); \
					fflush(gLogFile);

const float kHeadTranslateSpeed = 5e-5f;
//8e-7
const float kHeadRotateSpeed = 5e-5f;

const int kAxisX = 0;
const int kAxisY = 1;
const int kAxisZ = 2;

const vr::HmdVector3d_t kLeftPositionOffset = { -0.2, -0.3, -0.6 };
const vr::HmdVector3d_t kRightPositionOffset = { 0.2, -0.3, -0.6 };

const int kButtonPacketOffset = 7;
