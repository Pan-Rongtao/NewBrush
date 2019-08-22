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
namespace gui{

class ImageSource;
class NB_API Image : public UIElement
{
public:
	Image();
	virtual ~Image() = default;

	Property_rw<shared_ptr<ImageSource>>	Source;				//Դ
	Property_rw<StretchE>					Stretch;			//������ʽ
	static const DependencyProperty			SourceProperty();	//Դ����������
	static const DependencyProperty			StretchProperty();	//������ʽ����������

	virtual void onRender(std::shared_ptr<gl::Context> drawContext) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	Size	m_availableSize;
};


}}
