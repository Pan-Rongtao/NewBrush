#pragma once
#include <map>
#include "../gui/Binding.h"
#include "../gui/DependencyObject.h"

namespace nb{
namespace gui{

class NB_API BindingMaster
{
public:
	//���һ����
	//target��Ŀ���������󣬿�����UIԪ�ػ��UIԪ��
	static void addBinding(DependencyObjectPtr target, const DependencyProperty &dp, BindingPtr bd);

private:
	static void onBingingDataChanged(const ValueDataBase::ValueChangedArgs & args);
	static std::map<BindingPtr, std::pair<DependencyObjectPtr, DependencyProperty>>	g_bindingmap;
};



}}