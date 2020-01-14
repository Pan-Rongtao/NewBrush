#pragma once
#include <map>
#include "../core/DependencyProperty.h"
#include "../gui/DataContext.h"

namespace nb{

class DependencyObject;
namespace gui{

class Binding;
class NB_API BindingMaster
{
public:
	//���һ����
	//target��Ŀ���������󣬿�����UIԪ�ػ��UIԪ��
	static void addBinding(std::shared_ptr<DependencyObject> target, const DependencyProperty &dp, std::shared_ptr<Binding> bd);

private:
	static void onBingingDataChanged(const DataContext::ValueChangedArgs & args);
	static void setToTarget(std::shared_ptr<DependencyObject> target, const DependencyProperty & dp, std::shared_ptr<DataContext> dataNode);

	static std::map<std::shared_ptr<Binding>, std::pair<std::shared_ptr<DependencyObject>, DependencyProperty>>	g_bindingmap;
};



}}