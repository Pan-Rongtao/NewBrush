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

class RenderObject;
class NB_API Image : public UIElement
{
	NB_STATIC_MOUDULE(Image)
public:
	Image();
	virtual ~Image() = default;

	static DependencyProperty	SourceProperty();	//Դ���������ԣ�std::shared_ptr<ImageSource>��
	static DependencyProperty	StretchProperty();	//������ʽ���������ԣ�StretchE��

	Event<RoutedEventArgs>		ImageFailed;

protected:
	virtual void onRender(Viewport2D & drawContext) override;
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	static void onSourcePropertyChanged(DependencyObject *obj, DependencyPropertyChangedEventArgs *args);
	static void onStretchPropertyChanged(DependencyObject *obj, DependencyPropertyChangedEventArgs *args);

	Size							m_availableSize;
	std::shared_ptr<RenderObject>	m_renderObj;
};

}
