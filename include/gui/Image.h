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
#include "Control.h"
#include "ImageSource.h"
#include "Stretch.h"

namespace nb{ namespace Gui{

class Image_Internal;
class NB_EXPORT Image : public Control
{
	NB_OBJECT_TYPE_DECLARE();

public:
	//Դ����
	NB_X_OBJECT_PROPERTY_DECLARE(Source, nb::Media::ImageSource);
	//����ģʽ����
	NB_OBJECT_ENUM_PROPERTY_DECLARE(Stretch, nb::Media::Stretch);

	nb::System::Size GetPixcelSize() const;

public:
	//����һ��Image��ԴΪ�գ�����ģʽΪUniform
	Image();

	//����һ��Image��ԴΪsource������ģʽΪUniform
	Image(const nb::Media::ImageSourcePtr &source);

	//����һ��Image��ԴΪsource������ģʽΪstretch
	Image(const nb::Media::ImageSourcePtr &source, nb::Media::Stretch stretch);
	~Image();

	IElementRender *GetElementRender() const;

protected:
	virtual System::Size MeasureOverride(const System::Size &availableSize);
	virtual System::Size ArrangeOverride(const System::Size &finalSize);

public:
	Image(const Image &other); //hp��ʱ��Ϊ���е�
private:
	void operator = (const Image &other);

	void OnSourceChanged(Core::PropertyValueChangedEventArgs &args);

private:
	Image_Internal	*m_internal;
};

typedef nbObjectPtrDerive<Image, ControlPtr> ImagePtr;

}}
