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
	//获取Egl版本
	NB_API std::string getVersion();

	//获取
	NB_API std::string getVendor(); 

	//初始化
	//dispay：显示对象
	NB_API void initialize(std::shared_ptr<Display> display);

	//获取当前显示设备
	NB_API std::shared_ptr<Display> getDisplay();

	//设置配置
	NB_API void setConfigure(std::shared_ptr<Configure> configure);

	//获取egl设置
	NB_API std::shared_ptr<Configure> getConfigure();

	//设置摄像机
	NB_API void setCamera(std::shared_ptr<Camera> camera);

	//获取摄像机
	NB_API std::shared_ptr<Camera> getCamera();

	//设置投影
	NB_API void setProjection(std::shared_ptr<Projection> projection);

	//获取投影
	NB_API std::shared_ptr<Projection> getProjection();

	//设置当前渲染surface和context
	NB_API void makeCurrent(std::shared_ptr<Surface> onScreen, std::shared_ptr<Surface> offScreen, std::shared_ptr<Context> context);

	//获取onScreen/offScreen
	NB_API std::shared_ptr<Surface> getOnScreenSurface();
	NB_API std::shared_ptr<Surface> getOffScreenSurface();

	//获取Context
	NB_API std::shared_ptr<Context> getContext();
	
	//执行缓冲
	NB_API void swapBuffers(const Surface *surface);

	//设置视口大小
	NB_API void viewport(int x, int y, unsigned int width, unsigned height);

}}
