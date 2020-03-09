/*******************************************************
**	Image
**
**	
**	
**		�ṩ��ʾͼƬ��һ�ֻ����ؼ�
**			
**
**		������
**	
********************************************************/
#pragma once
#include "newbrush/gui/UIElement.h"
#include "newbrush/gui/Stretch.h"

namespace nb{
class ImageSource;
class RenderObject;
class NB_API Image : public UIElement
{
public:
	Image();
	virtual ~Image() = default;

	static DependencyProperty				SourceProperty();	//Դ���������ԣ�std::shared_ptr<ImageSource>��
	static DependencyProperty				StretchProperty();	//������ʽ����������

	virtual void onRender(Viewport2D & drawContext) override;

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args) override;

	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	Size							m_availableSize;
	std::shared_ptr<RenderObject>	m_renderObj;
};

}
