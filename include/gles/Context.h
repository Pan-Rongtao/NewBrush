#pragma once
#include "../core/Def.h"
#include <vector>

namespace nb{ namespace gl{

class Configure;
class RenderObject;
class NB_API Context
{
public:
	//����һ��Context��ʹ������configure
	Context(std::shared_ptr<Configure> configure);
	~Context();

	//gl���
	void *handle() const;

	//����һ����Ⱦ��
	void queue(std::shared_ptr<nb::gl::RenderObject> renderObject);

	//����һ����Ⱦ��
	void dequeue(std::shared_ptr<nb::gl::RenderObject> renderObject);

	//
	int renderObjectCount() const;

	//��Ⱦ��
	std::shared_ptr<nb::gl::RenderObject> renderObject(uint32_t index);

	//ִ����Ⱦ����
	void draw();

private:
	void												*m_handle;
	std::vector<std::shared_ptr<nb::gl::RenderObject>>	m_renderObjects;
};

}}
