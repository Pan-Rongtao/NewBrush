#pragma once
#include <map>
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/core/DataContext.h"

namespace nb{

class Binding;
class NB_API BindingMaster
{
public:
	//���һ����
	//target��Ŀ���������󣬿�����UIԪ�ػ��UIԪ��
	static void addBinding(std::shared_ptr<DependencyObject> target, const DependencyProperty &dp, std::shared_ptr<Binding> bd);

private:
	static void setToTarget(std::shared_ptr<DependencyObject> target, const DependencyProperty & dp, const var &value);

	using ObjectPropertysContainer = std::vector<std::pair<std::shared_ptr<DependencyObject>, DependencyProperty>>;
	static std::map<std::shared_ptr<Binding>, ObjectPropertysContainer>	g_bindingmap;
};


}