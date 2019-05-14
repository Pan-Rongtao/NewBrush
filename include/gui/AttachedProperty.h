#pragma once
#include <string>
#include "core/Any.h"
#include "UIElement.h"

namespace nb{ namespace gui{

class AttachedProperties
{
public:
	//ע��һ���������ԣ�����������Ѵ��ڣ���ֻ�޸�����ֵ
	//element��Ŀ��Ԫ��
	//property_name��������
	//property_v������ֵ
	static void registerAttached(std::shared_ptr<UIElement> element, const std::string &property_name, const core::Any &property_v);

	//��ѯ��������ֵ�������ѯ������������һ���յ�Any
	//element��Ŀ��Ԫ��
	//property_name��������
	static core::Any findAttached(std::shared_ptr<UIElement> element, const std::string &property_name);

private:
	static std::map<std::shared_ptr<UIElement>, std::map<std::string, core::Any>>	m_attProperties;
};


}}