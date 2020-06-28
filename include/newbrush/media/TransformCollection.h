/*******************************************************
**	TransformCollection
**
*��ʾ�ɰ��������������ʵ�Transform ����ļ��ϡ�
**
********************************************************/

#pragma once
#include "newbrush/media/Transform.h"

namespace nb {

using TransformPtr = std::shared_ptr<Transform>;
class NB_API TransformCollection : public Transform
{
public:
	TransformCollection();
	TransformCollection(std::vector<TransformPtr> collection);
	TransformCollection(size_t capacity);

	//��ȡTransformCollection �а���������
	size_t count();

	//��Transform ��ӵ� TransformCollection��ĩβ
	void add(TransformPtr value);

	//��TransformCollection ���Ƴ������
	void clear();

	//ȷ��TransformCollection�Ƿ����ָ����Transform��
	bool contains(TransformPtr value);

	//ȷ��TransformCollection��ָ���������������ҵ��˸����Ϊ value ������������Ϊ -1��
	int indexOf(TransformPtr value);

	//��Transform ����TransformCollection�е�ָ����������
	void insert(size_t index, TransformPtr value);

	//��TransformCollection���Ƴ�ָ����Transform�ĵ�һ��ƥ���
	bool remove(TransformPtr value);

	//�Ƴ�ָ����������Transform��
	void removeAt(size_t index);

	TransformPtr getItem(size_t i);

private:
	std::vector<TransformPtr> m_collection;
};

}