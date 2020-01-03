#include "media/ImageBrush.h"
#include "media/Bitmap.h"

using namespace nb;

ImageBrush::ImageBrush()
	: ImageBrush(nullptr)
{
}

ImageBrush::ImageBrush(std::shared_ptr<ImageSource> imgSource)
	: Source([&](std::shared_ptr<ImageSource> v) {set(SourceProperty(), v); }, [&]()->std::shared_ptr<ImageSource> & {return get<std::shared_ptr<ImageSource>>(SourceProperty()); })
{
	auto bm = imgSource->Bm();
	//����img->Bm()ʹ�õ���std::shared����ִ��Source =ʱ��������ImageBrush::SourceProperty()�е�std::make_shared<ImageSource>()����bm����Ϊnull
	//ʹ������ִ��Source = imgSource���bmΪnull��������Ŀǰ�޽⣬��ʱ�ñ���bm�����ķ�ʽ
	auto bmx = std::make_shared<Bitmap>(*bm);
	Source = imgSource;
	imgSource->Bm() = bmx;
}

DependencyProperty ImageBrush::SourceProperty()
{
	static auto dp = DependencyProperty::registerDependency<Brush, std::shared_ptr<ImageSource>>("Source", std::make_shared<ImageSource>());
	return dp;
}
