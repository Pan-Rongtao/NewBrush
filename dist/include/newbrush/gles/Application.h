#pragma once
#include "../core/Def.h"

namespace nb{ namespace gl{

class NB_API Application
{
public:
	//����һ��Application����
	//�쳣����ι���
	Application();
	virtual ~Application();

	//����
	int run();

protected:
	//��ʼ��
	virtual void InitializeOverride();

	//��Ⱦǰ
	virtual void PreRenderOverride();

	//��Ⱦ��
	virtual void PostRenderOverride();

	//����
	virtual void IdledOverride();


private:
	void initialize();
	void render();
};

}}
