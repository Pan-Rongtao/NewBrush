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
		size_t Count();

		//��Transform ��ӵ� TransformCollection��ĩβ
		void Add(std::shared_ptr<Transform> value);

		//��TransformCollection ���Ƴ������
		void Clear();

		//ȷ��TransformCollection�Ƿ����ָ����Transform��
		bool Contains(std::shared_ptr<Transform> value);

		//ȷ��TransformCollection��ָ���������������ҵ��˸����Ϊ value ������������Ϊ -1��
		int IndexOf(std::shared_ptr<Transform> value);

		//��Transform ����TransformCollection�е�ָ����������
		void Insert(size_t index, std::shared_ptr<Transform> value);

		//��TransformCollection���Ƴ�ָ����Transform�ĵ�һ��ƥ���
		bool Remove(std::shared_ptr<Transform> value);

		//�Ƴ�ָ����������Transform��
		void RemoveAt(size_t index);

		std::shared_ptr<Transform> GetItem(size_t i);

	private:
		std::vector<std::shared_ptr<Transform>> m_collection;
	};
}