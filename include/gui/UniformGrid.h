#pragma once
#include "Panel.h"

namespace nb {
namespace gui{

class NB_API UniformGrid : public Panel
{
public:
	UniformGrid();

	core::Property_rw<int32_t>		Rows;		//����
	core::Property_rw<int32_t>		Columns;	//����
	core::Property_rw<int32_t>		FirstColumn;//��һ����ǰ���հ׵�Ԫ������������ʽָ����Colums����Ч��������ڵ���ColumsҲ��Ч

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;

private:
	std::pair<int, int> calcRowsColums() const;
};

}
}