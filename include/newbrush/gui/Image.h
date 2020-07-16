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

class ImageSource;
using ImageSourcePtr = std::shared_ptr<ImageSource>;
class NB_API Image : public UIElement
{
	RTTR_ENABLE(UIElement)

public:
	static DependencyPropertyPtr SourceProperty();	//Դ���������ԣ�ImageSourcePtr��
	static DependencyPropertyPtr StretchProperty();	//������ʽ���������ԣ�StretchE��

	Event<RoutedEventArgs>		ImageFailed;

protected:
	virtual void onRender(DrawingContextPtr dc) override;
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	static void onSourcePropertyChanged(DependencyObject *obj, const DependencyPropertyChangedEventArgs &args);
	static void onStretchPropertyChanged(DependencyObject *obj, const DependencyPropertyChangedEventArgs &args);

	Size			m_availableSize;
};

}
