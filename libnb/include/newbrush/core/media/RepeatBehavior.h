#pragma once
#include "newbrush/core/TimeSpan.h"

namespace nb{

class NB_API RepeatBehavior
{
public:
	//����һ������ѭ����
	//�쳣��std::out_of_range
	RepeatBehavior(float count);

	//����һ��ʱ��ѭ����
	//�쳣��tsΪ��ֵ
	RepeatBehavior(const TimeSpan &duration);

	//��������ѭ����
	static RepeatBehavior fromCount(float count);

	//����ʱ���ѭ����
	static RepeatBehavior fromDuration(const TimeSpan &duration);

	//��������ѭ����
	static RepeatBehavior forever();

	//�Ƿ�������ѭ��
	bool isForever() const;

	//��ȡѭ������
	//�쳣��std::logic_error������һ������ѭ����
	bool hasCount() const;
	float getCount() const;

	//��ȡʱ�䳤��
	//�������ʱ��ѭ����������false
	bool hasDuration() const;
	TimeSpan getDuration() const;

	bool operator ==(const RepeatBehavior &other) const;
	bool operator !=(const RepeatBehavior &other) const;

private:
	enum class Type : char
	{
		Counter,
		Duration,
		Forever,
	};

	Type		m_type;
	float		m_count;
	TimeSpan	m_duration;
};

}