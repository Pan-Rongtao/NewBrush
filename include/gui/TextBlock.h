#pragma once
#include "../gui/UIElement.h"
#include "../gles/Model.h"
#include "../media/Font.h"
#include "../media/GlyphMetrics.h"

namespace nb{ namespace gl{
	class RenderObject;
	class GlyphBunch;
}}

namespace nb{
class Brush;
namespace gui{

enum class TextAlignmentE
{
	Left,
	Right,
	Center,
	Justify,
};

enum class TextTrimmingE
{
	None,
	CharacterEllipsis,
	WordEllipsis,
};

enum class TextDecorationE
{
	OverLine,
	Strikethrough,
	Baseline,
	Underline
};

class NB_API TextBlock : public UIElement
{
public:
	TextBlock();
	explicit TextBlock(const std::string &content);

	//fontstyle��ɶ��
	Property_rw<std::string>		Text;			//�ı�����
	Property_rw<shared_ptr<Brush>>	Background;		//����
	Property_rw<shared_ptr<Font>>	Font;			//����
	Property_rw<float>				FontSize;		//�����С
	Property_rw<int>				FontWeight;		//����Ȩ��
	Property_rw<Color>				Foreground;		//����ǰ��
	Property_rw<float>				LineHeight;		//�м��
	Property_rw<float>				CharSpacing;	//�ּ��
	Property_rw<Thickness>			Padding;		//�ھ�
	Property_rw<TextAlignmentE>		TextAlignment;	//�ı����з�ʽ
	Property_rw<TextTrimmingE>		TextTrimming;	//�ı��������
	Property_rw<TextWrappingE>		TextWrapping;	//�ı�����
	Property_rw<TextDecorationE>	TextDecoration;	//�ı�����

	static DependencyProperty		TextProperty();
	static DependencyProperty		BackgroundProperty();
	static DependencyProperty		FontProperty();
	static DependencyProperty		FontSizeProperty();
	static DependencyProperty		FontWeightProperty();
	static DependencyProperty		ForegroundProperty();
	static DependencyProperty		LineHeightProperty();
	static DependencyProperty		CharSpacingProperty();
	static DependencyProperty		PaddingProperty();
	static DependencyProperty		TextAlignmentProperty();
	static DependencyProperty		TextTrimmingProperty();
	static DependencyProperty		TextWrappingProperty();
	static DependencyProperty		TextDecorationProperty();


	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

	void onTextChanged(const std::string &_old, const std::string &_new);
	void onForegroundChanged(const Color &_old, const Color &_new);

	std::shared_ptr<gl::GlyphBunch>	m_glyphBunch;
};

}}
