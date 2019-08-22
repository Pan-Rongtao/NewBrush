#pragma once
#include "Panel.h"

namespace nb {
namespace gui{

class NB_API UniformGrid : public Panel
{
public:
	UniformGrid();

	Property_rw<int>					Rows;					//����
	Property_rw<int>					Columns;				//����
	Property_rw<int>					FirstColumn;			//��һ����ǰ���հ׵�Ԫ������������ʽָ����Colums����Ч��������ڵ���ColumsҲ��Ч

	static const DependencyProperty		RowsProperty();			//��������������
	static const DependencyProperty		ColumnsProperty();		//��������������
	static const DependencyProperty		FirstColumnProperty();	//��һ�пհ�������������

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	std::pair<int, int> calcRowsColums() const;
};

}
}