#pragma once
#include <string>
#include "Display.h"
#include "Configure.h"
#include "Surface.h"
#include "Context.h"
#include "Camera.h"
#include "Projection.h"

namespace nb{ namespace gl
{
	//��ȡEgl�汾
	NB_API std::string getVersion();

	//��ȡ
	NB_API std::string getVendor(); 

	//��ʼ��
	//dispay����ʾ����
	//configure��egl����
	NB_API void initialize(std::shared_ptr<Display> display, std::shared_ptr<Configure> configure);
	NB_API bool hasInitialized();

	//��ȡ��ǰ��ʾ�豸
	NB_API std::shared_ptr<Display> getDisplay();

	//��ȡegl����
	NB_API std::shared_ptr<Configure> getConfigure();

	//���������
	NB_API void setCamera(std::shared_ptr<Camera> camera);

	//��ȡ�����
	NB_API std::shared_ptr<Camera> getCamera();

	//����ͶӰ
	NB_API void setProjection(std::shared_ptr<Projection> projection);

	//��ȡͶӰ
	NB_API std::shared_ptr<Projection> getProjection();

	//���õ�ǰ��Ⱦsurface��context
	NB_API void makeCurrent(std::shared_ptr<Surface> onScreen, std::shared_ptr<Surface> offScreen, std::shared_ptr<Context> context);
	
	//ִ�л���
	NB_API void swapBuffers(const Surface *surface);

	//�����ӿڴ�С
	NB_API void viewport(int x, int y, unsigned int width, unsigned height);

}}
