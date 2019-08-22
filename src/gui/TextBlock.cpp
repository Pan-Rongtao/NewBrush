#include "gui/TextBlock.h"
#include <codecvt>
#include "media/Font.h"
#include "gles/Quadrangle.h"
#include "gles/GlyphFactory.h"
#include "gles/Context.h"
#include "gles/Model.h"
#include "gles/Material.h"
#include "gles/Texture2D.h"
#include "gles/GlyphBunch.h"

using namespace nb;
using namespace nb::gl;
using namespace nb::gui;

TextBlock::TextBlock()
	: TextBlock("")
{
}

TextBlock::TextBlock(const std::string & text)
	: Text([&](std::string v) {set(TextProperty(), v); }, [&]() {return get<std::string>(TextProperty()); })
	, Background([&](shared_ptr<Brush> v) {set(BackgroundProperty(), v); }, [&]() {return get<shared_ptr<Brush>>(BackgroundProperty()); })
	, Font([&](shared_ptr<nb::Font> v) {set(FontProperty(), v); }, [&]() {return get<shared_ptr<nb::Font>>(FontProperty()); })
	, FontSize([&](float v) {set(FontSizeProperty(), v); }, [&]() {return get<float>(FontSizeProperty()); })
	, FontWeight([&](int v) {set(FontWeightProperty(), v); }, [&]() {return get<int>(FontWeightProperty()); })
	, Foreground([&](Color v) {set(ForegroundProperty(), v); }, [&]() {return get<Color>(ForegroundProperty()); })
	, LineHeight([&](float v) {set(LineHeightProperty(), v); }, [&]() {return get<float>(LineHeightProperty()); })
	, CharSpacing([&](float v) {set(CharSpacingProperty(), v); }, [&]() {return get<float>(CharSpacingProperty()); })
	, Padding([&](Thickness v) {set(PaddingProperty(), v); }, [&]() {return get<Thickness>(PaddingProperty()); })
	, TextAlignment([&](TextAlignmentE v) {set(TextAlignmentProperty(), v); }, [&]() {return get<TextAlignmentE>(TextAlignmentProperty()); })
	, TextTrimming([&](TextTrimmingE v) {set(TextTrimmingProperty(), v); }, [&]() {return get<TextTrimmingE>(TextTrimmingProperty()); })
	, TextWrapping([&](TextWrappingE v) {set(TextWrappingProperty(), v); }, [&]() {return get<TextWrappingE>(TextWrappingProperty()); })
	, TextDecoration([&](TextDecorationE v) {set(TextWrappingProperty(), v); }, [&]() {return get<TextDecorationE>(TextWrappingProperty()); })
	, m_glyphBunch(std::make_shared<GlyphBunch>())
{
	Text = text;
	Renderer()->setModel(m_glyphBunch);
	Renderer()->setMaterial(std::make_shared<Material>(Programs::glpy()));
	Renderer()->material()->textures().push_back(std::make_shared<Texture2D>(GlyphFactory::getGlyph(Font(), L'a')->texureId));
	PropertyChanged += [&](const PropertyChangedArgs &arg) {
		auto c = any_cast<Color>(arg.value);
		Renderer()->storage()->set("fontColor", glm::vec4(c.redF(), c.greenF(), c.blueF(), c.alphaF()));
	};
	Renderer()->storage()->set("fontColor", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

DependencyProperty TextBlock::TextProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, std::string>("Text");
	return dp;
}

DependencyProperty TextBlock::BackgroundProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, shared_ptr<Brush>>("Background");
	return dp;
}

DependencyProperty TextBlock::FontProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, shared_ptr<nb::Font>>("Font", Fonts::getFont(Fonts::SimSun));
	return dp;
}

DependencyProperty TextBlock::FontSizeProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, float>("FontSize");
	return dp;
}

DependencyProperty TextBlock::FontWeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, int>("FontWeight");
	return dp;
}

DependencyProperty TextBlock::ForegroundProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, Color>("Foreground");
	return dp;
}

DependencyProperty TextBlock::LineHeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, float>("LineHeight");
	return dp;
}

DependencyProperty TextBlock::CharSpacingProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, float>("CharSpacing");
	return dp;
}

DependencyProperty TextBlock::PaddingProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, Thickness>("Padding");
	return dp;
}

DependencyProperty TextBlock::TextAlignmentProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, TextAlignmentE>("TextAlignment", TextAlignmentE::Center);
	return dp;
}

DependencyProperty TextBlock::TextTrimmingProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, TextTrimmingE>("TextTrimming", TextTrimmingE::None);
	return dp;
}

DependencyProperty TextBlock::TextWrappingProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, TextWrappingE>("TextWrapping", TextWrappingE::NoWrap);
	return dp;
}

DependencyProperty TextBlock::TextDecorationProperty()
{
	static auto dp = DependencyProperty::registerDependency<TextBlock, TextDecorationE>("TextDecoration", TextDecorationE::Baseline);
	return dp;
}

Size TextBlock::measureOverride(const Size & availableSize)
{
	return Size(availableSize.width() - Padding().left() - Padding().right(), availableSize.height() - Padding().top() - Padding().bottom());
}

Size TextBlock::arrangeOverride(const Size & finalSize)
{
	switch (TextWrapping())
	{
	case TextWrappingE::NoWrap:
	{
		Size sz = GlyphMetrics::measureGlyphAltas(Font(), Text(), CharSpacing(), LineHeight(), TextWrappingE::NoWrap, -1);
		return sz;
	}
	case TextWrappingE::Wrap:
	{
		Size sz = GlyphMetrics::measureGlyphAltas(Font(), Text(), CharSpacing(), LineHeight(), TextWrappingE::Wrap, finalSize.width());
		return sz;
	}
	case TextWrappingE::WrapWithOverflow:
		break;
	default:
		break;
	}
	return Size();
}

void TextBlock::onTextChanged(const std::string & _old, const std::string & _new)
{
	auto x = 0.0f;// Offset().x();
	auto y = 0.0f;// Offset().y();
	m_glyphBunch->arrage(Font(), x, y, Text(), CharSpacing(), LineHeight(), TextWrapping(), ActualSize().width());
}

void TextBlock::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	auto offset = worldOffset();
	auto x = offset.x();
	auto y = offset.y();
	m_glyphBunch->arrage(Font(), x, y, Text(), CharSpacing(), LineHeight(), TextWrapping(), ActualSize().width());
	drawContext->queue(Renderer());
}
