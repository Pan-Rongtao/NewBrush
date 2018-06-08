#pragma once
#include "system/String.h"
#include "gles/Display.h"
#include "gles/Configure.h"
#include "gles/Surface.h"
#include "gles/Context.h"

namespace nb{ namespace gl{ namespace egl
{
	//��ȡEgl�汾
	NB_EXPORT nb::System::String GetVersion();

	//��ȡ
	NB_EXPORT nb::System::String GetVendor(); 

	//��ʼ��
	NB_EXPORT void Initialize(const Display &display);

	//��ȡ��ǰ��ʾ�豸
	NB_EXPORT const Display &GetCurrentDisplay();

	//����egl����
	NB_EXPORT void SetConfigure(const Configure &configure);

	//��ȡegl����
	NB_EXPORT const Configure &GetCurrentConfigure();

	//���õ�ǰ��Ⱦsurface��context
	NB_EXPORT void MakeCurrent(const Surface *onScreen, const Surface *offScreen, const Context *context);
	
	//
	NB_EXPORT void SwapBuffers(const Surface *surface);
}}}
