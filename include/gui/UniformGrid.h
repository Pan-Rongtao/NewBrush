#pragma once
#include "Panel.h"

namespace nb {
namespace gui{

class UniformGrid : public Panel
{
public:
	core::Property_rw<uint32_t>		Rows;		//����
	core::Property_rw<uint32_t>		Columns;	//����
	core::Property_rw<uint32_t>		FirstColumn;//��һ����ǰ���հ׵�Ԫ������

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;

};

}
}