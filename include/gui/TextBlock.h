#pragma once
#include "../gui/UIElement.h"
#include "../gui/Brush.h"
#include "../gles/Model.h"
#include "../media/Font.h"

namespace nb{ namespace gl{
	class RenderObject;
	class GlyphBunch;
}}

namespace nb{ namespace gui{

enum TextAlignmentE
{
	Left,
	Right,
	Center,
	Justify,
};

enum TextWrappingE
{
	NoWrap,
	Wrap,
	WrapWithOverflow,
};

enum TextTrimmingE
{
	None,
	CharacterEllipsis,
	WordEllipsis,
};

enum TextDecorationE
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
	nb::core::Property_rw<std::string>				Text;			//�ı�����
	nb::core::Property_rw<std::shared_ptr<Brush>>	Background;		//����
	nb::core::Property_rw<std::shared_ptr<media::Font>>	Font;			//����
	nb::core::Property_rw<double>					FontSize;		//�����С
	nb::core::Property_rw<int>						FontWeight;		//����Ȩ��
	nb::core::Property_rw<nb::core::Color>			Foreground;		//����ǰ��
	nb::core::Property_rw<double>					LineHeight;		//�м��
	nb::core::Property_rw<double>					CharSpacing;	//�ּ��
	nb::core::Property_rw<Thickness>				Padding;		//�ھ�
	nb::core::Property_rw<TextAlignmentE>			TextAlignment;	//�ı����з�ʽ
	nb::core::Property_rw<TextTrimmingE>			TextTrimming;	//�ı��������
	nb::core::Property_rw<TextWrappingE>			TextWrapping;	//�ı�����
	nb::core::Property_rw<TextDecorationE>			TextDecoration;	//�ı�����

	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext) override;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;

	std::shared_ptr<gl::GlyphBunch>	m_glyphBunch;
};

}}
