#pragma once
#include <vector>
#include <typeindex>
#include "newbrush/gui/Setter.h"
#include "newbrush/gui/Trigger.h"

namespace nb{
namespace gui{

class UIElement;
class NB_API Style
{
public:
	//����һ���յ���ʽ
	Style();

	//����һ��Ŀ������ΪtargetType����ʽ
	Style(std::type_index targetType);
	
	//Ŀ������
	void setTargetType(std::type_index targetType);
	std::type_index targetType() const;

	//����������
	std::vector<SetterBasePtr> &setters();

	//����������
	std::vector<TriggerBasePtr> &triggers();

	
private:
	std::type_index				m_targetType;
	std::vector<SetterBasePtr>	m_setters;
	std::vector<TriggerBasePtr>	m_triggers;

};

class NB_API StyleHelpler
{
public:
	static void updateStyle(UIElement *uie, std::shared_ptr<Style> oldStyle, std::shared_ptr<Style> newStyle);

private:
	static void processSetters(UIElement * uie, std::shared_ptr<Style> style);
	static void processTriggers(UIElement * uie, std::shared_ptr<Style> style);
};

}
}