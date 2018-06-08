/*******************************************************
**	Model2D
**
**	2Dģ��
**	
**	2Dģ��������һ��ÿ�����㶼����ͬһz��ȵ�ģ��
**	��ʹģ���ж�ÿ�����㶼�����˲�һ����z��ȣ�ʹ��Position3D��Ϊλ���������ͣ�
**	Ҳ�ὲÿ�����������һ����z���	
**		
**		������
**	
********************************************************/

#pragma once
#include "Model.h"

namespace nb{ namespace gl{ namespace Gles{


class NB_EXPORT Model2D : public Model
{
public:
	//����һ��2Dģ�ͣ��������Ϊ0.0
	Model2D(int nVertexCount, nb::System::EnumFlags<Model::VertexAttributesType> flags);

	//����һ��2Dģ�ͣ��������Ϊz
	Model2D(int nVertexCount, nb::System::EnumFlags<Model::VertexAttributesType> flags, float z);

public:
	void SetZ(float z);

	//��ȡz���
	float GetZ() const;


};

}}}