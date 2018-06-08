#pragma once
#include <vector>

namespace nb{namespace gl{ namespace Gles{

class RenderObject;
class Batching;
class BatchingsDrawcalls
{
public:
	BatchingsDrawcalls();
	~BatchingsDrawcalls();

	//�ӹ�һ����Ⱦ��ڲ����Զ�����bathing�Ĳ���
	void Charge(RenderObject *renderObject);

	//����һ����Ⱦ��
	void Eject(RenderObject *renderObject);

	//��ѯһ����Ⱦ��
	RenderObject *Find(RenderObject *renderObject) const;

	//����һ����Ⱦ���ģ�����ݣ�����޴���Ⱦ��������κζ���
	void UpdateModel(RenderObject *renderObject);

	//����һ����Ⱦ��Ĳ��ʣ�����޴���Ⱦ��������κζ���
	void UpdateMaterial(RenderObject *renderObject);
	
	//��ȡbatching����
	int GetBatchingCount() const;

	//��ȡ��Ⱦ�����
	int GetRenderObjectCount() const;

	//ִ������batching�Ļ���
	void DoBatchingsDrawcalls();

private:

	std::vector<Batching *>		m_Batchings;
};

}}}
