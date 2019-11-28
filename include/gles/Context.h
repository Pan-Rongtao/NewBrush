/*******************************************************
**	Context
**
**	��������
**		Context������OpenGL��Ⱦ�����ĵ����ݽṹ��
**	���԰������ΪOpenGL��Ⱦָ���
**
**		������
**
********************************************************/
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
	Context();
	~Context();

	//gl���
	void *handle() const;

	//����һ����Ⱦ��
	void queue(std::shared_ptr<RenderObject> renderObject);

	//����һ����Ⱦ��
	void dequeue(std::shared_ptr<RenderObject> renderObject);

	//��Ⱦ�����
	uint32_t renderObjectCount() const;

	//��Ⱦ��
	std::shared_ptr<RenderObject> renderObject(uint32_t index);

	//ִ����Ⱦ����
	void draw();

private:
	void												*m_handle;
	std::vector<std::shared_ptr<RenderObject>>	m_renderObjects;
};

}}
