#pragma once
#include <vector>
#include <typeindex>
#include "../gui/Setter.h"
#include "../gui/Trigger.h"

namespace nb{
namespace gui{

class NB_API Style
{
public:
	//����һ���յ���ʽ
	Style();

	//����һ��Ŀ������ΪtargetType����ʽ
	Style(const std::type_index &targetType);
	
	//����һ��Ŀ������ΪtargetType����ʽ�����̳���baseOn
	Style(const std::type_index &targetType, std::shared_ptr<Style> baseOn);

	//Ŀ������
	void setTargetType(const std::type_index &targetType);
	std::type_index targetType() const;

	//�̳е���ʽ
	void setBaseOn(std::shared_ptr<Style> baseOn);
	std::shared_ptr<Style> baseOn() const;

	//����������
	std::vector<Setter> &setters();

	//����������
	std::vector<TriggerBase> &triggers();

	
private:
	std::type_index				m_targetType;
	std::shared_ptr<Style>		m_baseOn;
	std::vector<Setter>			m_setters;
	std::vector<TriggerBase>	m_triggers;

};

}
}