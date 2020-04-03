/*******************************************************
**	TransformCollection
**
*��ʾ�ɰ��������������ʵ�Transform ����ļ��ϡ�
**
********************************************************/

#pragma once
#include "newbrush/media/Transform.h"

namespace nb {

	class NB_API TransformCollection : public Transform
	{
	public:
		TransformCollection();
		TransformCollection(std::vector<std::shared_ptr<Transform>> collection);
		TransformCollection(size_t capacity);

		//��ȡTransformCollection �а���������
		size_t count();

		//��Transform ��ӵ� TransformCollection��ĩβ
		void add(std::shared_ptr<Transform> value);

		//��TransformCollection ���Ƴ������
		void clear();

		//ȷ��TransformCollection�Ƿ����ָ����Transform��
		bool contains(std::shared_ptr<Transform> value);

		//ȷ��TransformCollection��ָ���������������ҵ��˸����Ϊ value ������������Ϊ -1��
		int indexOf(std::shared_ptr<Transform> value);

		//��Transform ����TransformCollection�е�ָ����������
		void insert(size_t index, std::shared_ptr<Transform> value);

		//��TransformCollection���Ƴ�ָ����Transform�ĵ�һ��ƥ���
		bool remove(std::shared_ptr<Transform> value);

		//�Ƴ�ָ����������Transform��
		void removeAt(size_t index);

		std::shared_ptr<Transform> getItem(size_t i);

	private:
		std::vector<std::shared_ptr<Transform>> m_collection;
	};
}