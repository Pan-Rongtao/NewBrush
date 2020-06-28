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
#include "newbrush/media/Media.h"

namespace nb{

class RenderObject;
class ImageSource;
using RenderObjectPtr = std::shared_ptr<RenderObject>;
using ImageSourcePtr = std::shared_ptr<ImageSource>;
class NB_API Image : public UIElement
{
	RTTR_ENABLE(UIElement)
public:
	Image();
	virtual ~Image() = default;

	static DependencyPropertyPtr SourceProperty();	//Դ���������ԣ�ImageSourcePtr��
	static DependencyPropertyPtr StretchProperty();	//������ʽ���������ԣ�StretchE��

	Event<RoutedEventArgs>		ImageFailed;

protected:
	virtual void onRender(Viewport2D & drawContext) override;
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	static void onSourcePropertyChanged(DependencyObject *obj, DependencyPropertyChangedEventArgs *args);
	static void onStretchPropertyChanged(DependencyObject *obj, DependencyPropertyChangedEventArgs *args);

	Size			m_availableSize;
	RenderObjectPtr	m_renderObj;
};

}
