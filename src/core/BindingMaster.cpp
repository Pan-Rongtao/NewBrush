#include "newbrush/core/BindingMaster.h"
#include "newbrush/core/DependencyObject.h"
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/core/DataContext.h"
#include "newbrush/core/Binding.h"

using namespace nb;

//ÿ��bindingʵ�����Զ�Ӧ���obj-property
//source��path��ͬ�Ĳ�ͬbindingʵ�����ֱ��Ӧ��ͬobj-property
//���map�������������˽�����ܲ�����ѣ��������ܿ����Ż�
std::map<BindingPtr, BindingMaster::ObjectPropertysContainer>	BindingMaster::g_bindingmap;

void BindingMaster::addBinding(DependencyObjectPtr target, DependencyPropertyPtr dp, BindingPtr bd)
{
	if (!bd)
	{
		nbThrowException(std::invalid_argument, "bd is nullptr.");
	}

	auto source = bd->source();
	if (!source)
	{
		nbThrowException(std::invalid_argument, "bd's source is nullptr.");
	}

	auto path = bd->path();
	auto dataNode = source->lookup(path);
	if (!dataNode)
	{
		nbThrowException(std::runtime_error, "bd's source has no path [%s]", path.data());
	}

	setToTarget(target, dp, dataNode->get());

	auto ret = g_bindingmap.insert({ bd, ObjectPropertysContainer{ std::make_pair(target, dp) } });
	//����ɹ�����ʾ��binding�����ڣ������binding�Ѿ��а󶨵����ԣ���Ҫ׷�Ӷ�Ӧ��ϵ����
	if (ret.second)
	{
		bd->BindDataChanged += [bd](const Binding::BindDataChangedEventArgs &args) {
			auto iterFind = g_bindingmap.find(bd);
			for (auto const &objPropertyPair : iterFind->second)
			{
				auto target = objPropertyPair.first;
				auto dp = objPropertyPair.second;
				setToTarget(target, dp, args.value);
			}
		};
	}
	else
	{
		ret.first->second.push_back({target, dp});
	}
}

void BindingMaster::setToTarget(DependencyObjectPtr target, DependencyPropertyPtr dp, const var &value)
{
	try {
		target->setValue(dp, value);
	}
	catch (...) {
		nbThrowException(std::logic_error, "binding data type[%s] is unmatched with target property type[%s]", value.get_type().get_name().data(), dp->propertyType().get_name().data());
	}
}
