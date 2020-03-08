#pragma once
#include <vector>
#include <typeindex>
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/gui/Setter.h"
#include "newbrush/gui/Trigger.h"

namespace nb{

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

	void attach(UIElement * uie);

	void handlePropertyChanged(UIElement * uie, const DependencyProperty &dp, const Var &v);
	
	struct StyleDataTriggerArgs { std::shared_ptr<DataTrigger> dataTrigger; };
	Event<StyleDataTriggerArgs> StyleDataTrigger;
	struct StyleMultiDataTriggerArgs { std::shared_ptr<MultiDataTrigger> multiDataTrigger; };
	Event<StyleMultiDataTriggerArgs> StyleMultiDataTrigger;

private:
	void checkTargetType(UIElement * uie);
	//void onBingingDataChanged(const Binding::BindDataChangedEventArgs & args);

	std::type_index				m_targetType;
	std::vector<SetterBasePtr>	m_setters;
	std::vector<TriggerBasePtr>	m_triggers;
	bool	m_handlingPropertyChanged;
};

}