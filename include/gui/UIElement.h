#pragma once
#include "../core/Property.h"
#include "../core/DependencyObject.h"
#include "../core/Size.h"
#include "../core/Rect.h"
#include "../gui/Thickness.h"
#include "../gles/RenderObject.h"
#include "../gui/Style.h"
#include "../gui/VisualStateMachine.h"
#include "../core/RoutedEvent.h"

namespace nb{
	class Viewport2D;
}

namespace nb{
namespace gui{

enum class VisibilityE
{
	Hidden,		//��Ҫ��ʾ��Ԫ�أ����ǣ������ռ��е�Ԫ�ظ�ʽ�������Ű���Եȣ�
	Visible,	//��ʾ���
	Collapsed,	//��Ҫ��ʾԪ�أ����Ҳ�ϣ�����ı����ռ�
};

enum class HorizontalAlignmentE
{
	Left,
	Center,
	Right,
	Stretch,
};

enum class VerticalAlignmentE
{
	Top,
	Center,
	Bottom,
	Stretch,
};

enum class FlowDirectionE
{
	LeftToRight,
	RightToLeft,
};

enum class OrientationE
{
	Horizontal,
	Vertical,
};

class NB_API UIElement : public DependencyObject, public std::enable_shared_from_this<UIElement>
{
public:
	UIElement();
	virtual ~UIElement() = default;

	Property_rw<VisibilityE>					Visibility;				//����
	Property_rw<float>							Opacity;				//��͸����
	Property_rw<bool>							Focusable;				//�Ƿ���ý���
	Property_rw<bool>							IsFocused;				//�Ƿ���н���
	Property_rw<float>							Width;					//�趨��
	Property_rw<float>							Height;					//�趨��
	Property_rw<float>							MinWidth;				//��С��
	Property_rw<float>							MinHeight;				//��С��
	Property_rw<float>							MaxWidth;				//����
	Property_rw<float>							MaxHeight;				//����
	Property_r<Size>							DesiredSize;			//�����ߴ�
	Property_r<Size>							ActualSize;				//ʵ�ʳߴ�
	Property_rw<Size>							RenderSize;				//��Ⱦ�ߴ�
	Property_rw<Point>							Offset;					//��Ը�ƫ����
	Property_rw<Thickness>						Margin;					//��Ե
	Property_rw<HorizontalAlignmentE>			HorizontalAlignment;	//������뷽ʽ
	Property_rw<VerticalAlignmentE>				VerticalAlignment;		//������뷽ʽ
	Property_rw<FlowDirectionE>					FlowDirection;			//
	Property_r<shared_ptr<RenderObject>>		Renderer;				//��Ⱦ��
	Property_rw<shared_ptr<Style>>				style;					//���
	Property_rw<shared_ptr<VisualStateMachine>>	StateMachine;

	static DependencyProperty					VisibilityProperty();	//���ӵ���������
	static DependencyProperty					OpacityProperty();		//��͸���ȵ���������
	static DependencyProperty					FocusableProperty();	//�Ƿ���ý������������
	static DependencyProperty					IsFocusedProperty();	//�Ƿ���ý������������
	static DependencyProperty 					WidthProperty();		//�趨�����������
	static DependencyProperty 					HeightProperty();		//�趨�ߵ���������
	static DependencyProperty 					MinWidthProperty();		//��С�����������
	static DependencyProperty 					MinHeightProperty();	//��С�ߵ���������
	static DependencyProperty 					MaxWidthProperty();		//�������������
	static DependencyProperty 					MaxHeightProperty();	//���ߵ���������
	static DependencyProperty 					DesiredSizeProperty();	//�����ߴ����������
	static DependencyProperty 					ActualSizeProperty();	//ʵ�ʳߴ����������
	static DependencyProperty 					RenderSizeProperty();	//��Ⱦ�ߴ����������
	static DependencyProperty 					OffsetProperty();		//��Ը�ƫ��������������
	static DependencyProperty 					MarginProperty();		//��Ե����������
	static DependencyProperty 					HorizontalAlignmentProperty();	//������뷽ʽ����������
	static DependencyProperty 					VerticalAlignmentProperty();	//������뷽ʽ����������
	static DependencyProperty 					FlowDirectionProperty();		//
	static DependencyProperty 					RendererProperty();		//��Ⱦ�����������
	static DependencyProperty 					StyleProperty();		//������������
	static DependencyProperty 					StateMachineProperty();	//״̬������������

	void setParent(UIElement *element);
	UIElement *getRoot();
	Point worldOffset();
	void updateLayout();

	void measure(const Size &availabelSize);
	void arrage(const Rect &finalRect);
	virtual void onRender(Viewport2D & drawContext);

/*	void addHandler(const RoutedEvent &event, const RoutedEventHandler &handler);
	void removeHandler(const RoutedEvent &event, const RoutedEventHandler &handler);
	void raiseEvent(const RoutedEventArgs &args);*/
	
	struct MouseEnterArgs {};
	Event<MouseEnterArgs>							MouseEnter;

	struct MouseLeaveArgs {};
	Event<MouseLeaveArgs>							MouseLeave;

	struct MouseMoveArgs {};
	Event<MouseMoveArgs>							MouseMove;

	struct MouseDownArgs {};
	Event<MouseDownArgs>							MouseDown;

	struct MouseUpArgs {};
	Event<MouseUpArgs>								MouseUp;

	struct MouseLeftButtonDownArgs {};
	Event<MouseLeftButtonDownArgs>					MouseLeftButtonDown;

	struct MouseLeftButtonUpArgs {}; 
	Event<MouseLeftButtonUpArgs>					MouseLeftButtonUp;

	struct MouseRightButtonDownArgs {};
	Event<MouseRightButtonDownArgs>					MouseRightButtonDown;

	struct MouseRightButtonUpArgs {};
	Event<MouseRightButtonUpArgs>					MouseRightButtonUp;

	struct MouseWheelArgs {};
	Event<MouseWheelArgs>							MouseWheel;
	

public:
	virtual Size measureOverride(const Size &availableSize);
	virtual Size arrangeOverride(const Size &finalSize);
	virtual void onMouseEnter();
	virtual void onMouseLeave();
	virtual void onMouseDown();
	virtual void onMouseUp();
	virtual void onMouseLeftButtonDown();
	virtual void onMouseLeftButtonUp();
	virtual void onMouseRightButtonDown();
	virtual void onMouseRightButtonUp();
	virtual void onMouseMove();
	virtual void onMouseWheel(int delta);

protected:
	UIElement	*m_parent;

private:
	void onPropertyChanged(const PropertyChangedArgs &args);

//	std::map<size_t, std::vector<RoutedEventHandler>>	m_eventHandlers;
};

using UIElementPtr = std::shared_ptr<UIElement>;

}
}
