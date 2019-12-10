#pragma once
#include <vector>
#include "../core/Def.h"
#include "../gles/Camera.h"

namespace nb {
	
class Camera;
class RenderObject;
class NB_API Viewport2D
{
public:
	//����һ����Ⱦ��
	void queue(std::shared_ptr<RenderObject> renderObject);

	//��Ⱦ������Ⱦ��
	void draw();

private:
	std::shared_ptr<Camera>						m_camera;
	std::vector<std::shared_ptr<RenderObject>>	m_renderObjects;
};

}