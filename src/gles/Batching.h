/******************************************************************************

* Copyright (c) 2017���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-03

* ��Ҫ����: Batching
				
				������������������������Ⱦ����Ⱦ���������ݽṹ��
				�������ƹ���Ⱦ���Draw��������������Ⱦ�������һ����
				���ݸ�GPU���ﵽ����DrawCall��Ŀ�ģ��Ӷ��������

* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include <vector>

namespace nb{namespace gl{namespace Gles{

class RenderObject;
class Batching
{
public:
	//����һ��������
	Batching();
	~Batching();

	//�ӹ�һ����Ⱦ��
	void Charge(RenderObject *renderObject);

	//����һ����Ⱦ��
	void Eject(RenderObject *renderObject);

	//����һ����Ⱦ���ģ������
	void UpdateModel(RenderObject *renderObject);

	//��Ⱦ��ĸ���
	int GetObjectsCount() const;

	//��ȡ�±�Ϊindex����Ⱦ��
	const RenderObject *GetRenderObejct(int index) const;

	//��ѯ��Ⱦ��������±�
	//����Ҳ���������-1
	int Find(RenderObject *renderObject);

	//����
	void Draw() const;

private:
	Batching(const Batching &other);
	void operator = (const Batching &other);

	std::vector<RenderObject *>		m_ChargedRenderObjects;
	std::vector<float>				m_ModelsDatas;
	std::vector<unsigned short>		m_ModelsIndicesSequence;
	int								m_nActualIndicesCount;
};

}}}