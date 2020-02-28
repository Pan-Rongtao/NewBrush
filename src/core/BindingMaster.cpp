#include "newbrush/core/BindingMaster.h"
#include "newbrush/core/DependencyObject.h"
#include "newbrush/core/Binding.h"

using namespace nb;

//ÿ��bindingʵ�����Զ�Ӧ���obj-property
//source��path��ͬ�Ĳ�ͬbindingʵ�����ֱ��Ӧ��ͬobj-property
//���map�������������˽�����ܲ�����ѣ��������ܿ����Ż�
std::map<std::shared_ptr<Binding>, BindingMaster::ObjectPropertysContainer >	BindingMaster::g_bindingmap;

void BindingMaster::addBinding(std::shared_ptr<DependencyObject> target, const DependencyProperty & dp, std::shared_ptr<Binding> bd)
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

void BindingMaster::setToTarget(std::shared_ptr<DependencyObject> target, const DependencyProperty & dp, const Var &value)
{
	try {
		target->set(dp, value);
	}
	catch (...) {
		nbThrowException(std::logic_error, "binding data type[%s] is unmatched with target property type[%s]", value.type().name(), dp.propertyType().name());
	}
}
