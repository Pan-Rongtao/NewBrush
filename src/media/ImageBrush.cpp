#include "newbrush/media/ImageBrush.h"
#include "newbrush/media/Bitmap.h"

using namespace nb;

ImageBrush::ImageBrush()
	: ImageBrush(nullptr)
{
}

ImageBrush::ImageBrush(std::shared_ptr<ImageSource> imgSource)
{
	auto bm = imgSource->getValue<std::shared_ptr<Bitmap>>(ImageSource::BmProperty());
	//����img->Bm()ʹ�õ���std::shared����ִ��Source =ʱ��������ImageBrush::SourceProperty()�е�std::make_shared<ImageSource>()����bm����Ϊnull
	//ʹ������ִ��Source = imgSource���bmΪnull��������Ŀǰ�޽⣬��ʱ�ñ���bm�����ķ�ʽ
	auto bmx = std::make_shared<Bitmap>(*bm);
	setValue(SourceProperty(), imgSource);
	imgSource->setValue(ImageSource::BmProperty(), bmx);
}

DependencyProperty ImageBrush::SourceProperty()
{
	static auto dp = DependencyProperty::registerDependency<Brush, std::shared_ptr<ImageSource>>("Source", std::make_shared<ImageSource>());
	return dp;
}
