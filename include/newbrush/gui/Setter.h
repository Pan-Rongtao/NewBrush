#pragma once
#include "newbrush/core/RoutedEvent.h"

namespace nb{

class UIElement;
class DependencyProperty;
using DependencyPropertyPtr = std::shared_ptr<DependencyProperty>;

class NB_API SetterBase
{
public:
	virtual void attach(UIElement* uie);

protected:
	SetterBase() = default;
	virtual ~SetterBase() = default;
};

class NB_API Setter : public SetterBase
{
public:
	Setter();
	Setter(DependencyPropertyPtr dp, const var &v);
	Setter(DependencyPropertyPtr dp, const var &v, const std::string &targetName);

	//���Ƶ�����
	//�쳣��std::invalid_argument��dpΪnullptr
	void setProperty(DependencyPropertyPtr dp);
	DependencyPropertyPtr property() const;

	//���Ƶ�ֵ
	//�쳣��std::invalid_argument��vΪ��
	void setValue(const var &v);
	const var &value() const;

	//���Ƶ�Ŀ������
	void setTargetName(const std::string &name);
	const std::string &targetName() const;

	virtual void attach(UIElement* uie) override;

private:
	std::string m_targetName; //Ŀ������
	DependencyPropertyPtr m_property;	//����
	var m_value;		//����ֵ
};

class NB_API EventSetter : public SetterBase
{
public:
	virtual void attach(UIElement* uie) override;

	RoutedEvent			event;
	RoutedEventHandler	handler;
};

using SetterBasePtr = std::shared_ptr<SetterBase>;

}
