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
#include "UIElement.h"
#include "Stretch.h"

namespace nb{
class ImageSource;
namespace gui{

class NB_API Image : public UIElement
{
public:
	Image();
	virtual ~Image() = default;

	Property_rw<shared_ptr<ImageSource>>	Source;				//Դ
	Property_rw<StretchE>					Stretch;			//������ʽ
	static DependencyProperty				SourceProperty();	//Դ����������
	static DependencyProperty				StretchProperty();	//������ʽ����������

	virtual void onRender(Viewport2D & drawContext) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	Size	m_availableSize;
};


}}
