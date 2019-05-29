/*******************************************************
**	Application
**
**	app��
**		Application�ṩGL�ĳ�ʼ��������Display��Configure��
**	��app���к���ѭ���������е���Ⱦ�������Ⱦ
**
**		������
**
********************************************************/
#pragma once
#include "../core/Def.h"

namespace nb{ namespace gl{

class Display;
class Configure;
class NB_API Application
{
public:
	//����һ��Application����
	//display����ʾ���������ָ����ʹ��Ĭ�ϵ�display
	//configure�����ö��������ָ����ʹ��Ĭ�ϵ�configure
	//�쳣����ι���
	Application(std::shared_ptr<Display> display = nullptr, std::shared_ptr<Configure> configure = nullptr);
	virtual ~Application() = default;

	//����
	int run();

protected:
	//��Ⱦǰ
	virtual void preRender()	{}

	//��Ⱦ��
	virtual void postRender()	{}

private:
	void render();
};

}}
