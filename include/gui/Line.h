#pragma once
#include "../gui/Shape.h"

namespace nb{
namespace gl{
	class Line;
}}

namespace nb{
namespace gui{

class NB_API Line : public Shape
{
public:
	Line();
	virtual ~Line() = default;

	Property_rw<float>				X1;				//X1
	Property_rw<float>				X2;				//X2
	Property_rw<float>				Y1;				//Y1
	Property_rw<float>				Y2;				//Y2
	static const DependencyProperty	X1Property();	//X1����������
	static const DependencyProperty	X2Property();	//X2����������
	static const DependencyProperty	Y1Property();	//Y1����������
	static const DependencyProperty	Y2Property();	//Y2����������

	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

}}