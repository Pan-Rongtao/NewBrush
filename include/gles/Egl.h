#pragma once
#include <string>
#include "Context.h"
#include "Camera.h"
#include "Projection.h"

namespace nb{ namespace gl
{
	//���������
	NB_API void setCamera(std::shared_ptr<Camera> camera);

	//��ȡ�����
	NB_API std::shared_ptr<Camera> getCamera();

	//����ͶӰ
	NB_API void setProjection(std::shared_ptr<Projection> projection);

	//��ȡͶӰ
	NB_API std::shared_ptr<Projection> getProjection();
		
	//�����ӿڴ�С
	NB_API void viewport(int x, int y, unsigned int width, unsigned height);

}}
