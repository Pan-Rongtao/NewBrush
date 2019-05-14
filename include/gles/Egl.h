#pragma once
#include <string>
#include "Display.h"
#include "Configure.h"
#include "Surface.h"
#include "Context.h"

namespace nb{ namespace gl
{
	//��ȡEgl�汾
	NB_API std::string getVersion();

	//��ȡ
	NB_API std::string getVendor(); 

	//��ʼ��
	NB_API void initialize(const Display &display);

	//��ȡ��ǰ��ʾ�豸
	NB_API const Display &getCurrentDisplay();

	//����egl����
	NB_API void setConfigure(const Configure &configure);

	//��ȡegl����
	NB_API const Configure &getCurrentConfigure();

	//���õ�ǰ��Ⱦsurface��context
	NB_API void makeCurrent(std::shared_ptr<Surface> onScreen, std::shared_ptr<Surface> offScreen, std::shared_ptr<Context> context);
	
	//
	NB_API void swapBuffers(const Surface *surface);

	//�����ӿڴ�С
	NB_API void Viewport(int x, int y, unsigned int width, unsigned height);

}}
