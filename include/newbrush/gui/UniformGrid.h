#pragma once
#include "newbrush/gui/Panel.h"

namespace nb {

class NB_API UniformGrid : public Panel
{
	RTTR_ENABLE(Panel)
public:
	UniformGrid();

	static DependencyPropertyPtr RowsProperty();			//��������������
	static DependencyPropertyPtr ColumnsProperty();		//��������������
	static DependencyPropertyPtr FirstColumnProperty();	//��һ�пհ������������ԣ�����ʽָ����Colums����Ч��������ڵ���ColumsҲ��Ч��

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	std::pair<int, int> calcRowsColums() const;
};

}