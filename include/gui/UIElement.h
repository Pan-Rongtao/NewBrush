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

	Event<DependencyPropertyChangedEventArgs>	IsEnableChanged;
	Event<DependencyPropertyChangedEventArgs>	IsHitTestVisibleChanged;
	Event<DependencyPropertyChangedEventArgs>	IsVisibleChanged;
	Event<EventArgs>							LayoutUpdated;
	Event<MouseEventArgs>						GotMouseCapture;
	Event<MouseEventArgs>						LostMouseCapture;
	Event<TouchEventArgs>						GotTouchCapture;
	Event<TouchEventArgs>						LostTouchCapture;
	Event<DependencyPropertyChangedEventArgs>	FocusableChanged;
	Event<RoutedEventArgs>						LostFocus;
	Event<RoutedEventArgs>						GotFocus;
	Event<DragEventArgs>						PreviewDragEnter;
	Event<DragEventArgs>						DragEnter;
	Event<DragEventArgs>						PreviewDragLeave;
	Event<DragEventArgs>						DragLeave;
	Event<DragEventArgs>						PreviewDragOver;
	Event<DragEventArgs>						DragOver;
	Event<DragEventArgs>						PreviewDrop;
	Event<DragEventArgs>						Drop;
	Event<DependencyPropertyChangedEventArgs>	IsKeyboardFocusedChanged;
	Event<KeyboardFocusChangedEventArgs>		PreviewGotKeyboardFocus;
	Event<KeyboardFocusChangedEventArgs>		GotKeyboardFocus;
	Event<KeyboardFocusChangedEventArgs>		PreviewLostKeyboardFocus;
	Event<KeyboardFocusChangedEventArgs>		LostKeyboardFocus;
	Event<KeyEventArgs>							PreviewKeyDown;
	Event<KeyEventArgs>							KeyDown;
	Event<KeyEventArgs>							PreviewKeyUp;
	Event<KeyEventArgs>							KeyUp;
	Event<MouseEventArgs>						MouseEnter;
	Event<MouseEventArgs>						MouseLeave;
	Event<MouseButtonEventArgs>					PreviewMouseDown;
	Event<MouseButtonEventArgs>					MouseDown;
	Event<MouseButtonEventArgs>					PreviewMouseLeftButtonDown;
	Event<MouseButtonEventArgs>					MouseLeftButtonDown;
	Event<MouseButtonEventArgs>					PreviewMouseLeftButtonUp;
	Event<MouseButtonEventArgs>					MouseLeftButtonUp;
	Event<MouseEventArgs>						PreviewMouseMove;
	Event<MouseEventArgs>						MouseMove;
	Event<MouseButtonEventArgs>					PreviewMouseRightButtonDown;
	Event<MouseButtonEventArgs>					MouseRightButtonDown;
	Event<MouseButtonEventArgs>					PreviewMouseRightButtonUp;
	Event<MouseButtonEventArgs>					MouseRightButtonUp;
	Event<MouseButtonEventArgs>					PreviewMouseUp;
	Event<MouseButtonEventArgs>					MouseUp;
	Event<MouseWheelEventArgs>					PreviewMouseWheel;
	Event<MouseWheelEventArgs>					MouseWheel;
	Event<TouchEventArgs>						PreviewTouchEnter;
	Event<TouchEventArgs>						TouchEnter;
	Event<TouchEventArgs>						PreviewTouchLeave;
	Event<TouchEventArgs>						TouchLeave;
	Event<TouchEventArgs>						PreviewTouchDown;
	Event<TouchEventArgs>						TouchDown;
	Event<TouchEventArgs>						PreviewTouchMove;
	Event<TouchEventArgs>						TouchMove;
	Event<TouchEventArgs>						PreviewTouchUp;
	Event<TouchEventArgs>						TouchUp;

	static RoutedEvent							DragEnterEvent();
	static RoutedEvent							DragLeaveEvent();
	static RoutedEvent							DragOverEvent();
	static RoutedEvent							DropEvent();
	static RoutedEvent							GotFocusEvent();
	static RoutedEvent							GotKeyboardFocusEvent();
	static RoutedEvent							GotMouseCaptureEvent();
	static RoutedEvent							KeyDownEvent();
	static RoutedEvent							KeyUpEvent();
	static RoutedEvent							LostFocusEvent();
	static RoutedEvent							LostKeyboardFocusEvent();
	static RoutedEvent							LostMouseCaptureEvent();
	static RoutedEvent							LostTouchCaptureEvent();
	static RoutedEvent							MouseDownEvent();
	static RoutedEvent							MouseEnterEvent();
	static RoutedEvent							MouseLeaveEvent();
	static RoutedEvent							MouseLeftButtonDownEvent();
	static RoutedEvent							MouseLeftButtonUpEvent();
	static RoutedEvent							MouseMoveEvent();
	static RoutedEvent							MouseRightButtonDownEvent();
	static RoutedEvent							MouseRightButtonUpEvent();
	static RoutedEvent							MouseUpEvent();
	static RoutedEvent							MouseWheelEvent();
	static RoutedEvent							PreviewDragEnterEvent();
	static RoutedEvent							PreviewDragLeaveEvent();
	static RoutedEvent							PreviewDragOverEvent();
	static RoutedEvent							PreviewDropEvent();
	static RoutedEvent							PreviewGotKeyboardFocusEvent();
	static RoutedEvent							PreviewKeyDownEvent();
	static RoutedEvent							PreviewKeyUpEvent();
	static RoutedEvent							PreviewLostKeyboardFocusEvent();
	static RoutedEvent							PreviewMouseDownEvent();
	static RoutedEvent							PreviewMouseLeftButtonDownEvent();
	static RoutedEvent							PreviewMouseLeftButtonUpEvent();
	static RoutedEvent							PreviewMouseMoveEvent();
	static RoutedEvent							PreviewMouseRightButtonDownEvent();
	static RoutedEvent							PreviewMouseRightButtonUpEvent();
	static RoutedEvent							PreviewMouseUpEvent();
	static RoutedEvent							PreviewMouseWheelEvent();
	static RoutedEvent							PreviewTouchDownEvent();
	static RoutedEvent							PreviewTouchMoveEvent();
	static RoutedEvent							PreviewTouchUpEvent();
	static RoutedEvent							TouchDownEvent();
	static RoutedEvent							TouchEnterEvent();
	static RoutedEvent							TouchLeaveEvent();
	static RoutedEvent							TouchMoveEvent();
	static RoutedEvent							TouchUpEvent();

	void setParent(UIElement *element);
	UIElement *getRoot();
	Point worldOffset();
	void updateLayout();

	void measure(const Size &availabelSize);
	void arrage(const Rect &finalRect);
	virtual void onRender(Viewport2D & drawContext);
	template<class ArgsT>
	void addHandler(const RoutedEvent &event, const RoutedEventHandler<ArgsT> &handler)
	{
		if (event.argsType() != typeid(ArgsT))
			nbThrowException(std::logic_error, "[%s]'s args type should be [%s]", event.name().data(), event.argsType().name());
		m_eventHandlers[event.hash()].push_back(handler);
	}
	template<class ArgsT>
	void removeHandler(const RoutedEvent &event, const RoutedEventHandler<ArgsT> handler)
	{
		auto iter = m_eventHandlers.find(event.hash());
		if (iter != m_eventHandlers.end())
		{
			auto &handlers = iter->second;
			auto iterHandler = std::find(handlers.begin(), handlers.end(), handler);
			if (iterHandler != handlers.end())
				handlers.erase(iterHandler);
		}
	}
	template<class ArgsT>
	void raiseEvent(const ArgsT &args)
	{
		auto iter = m_eventHandlers.find(args.Event.hash());
		if (iter != m_eventHandlers.end())
		{
			for (auto &h : iter->second)
			{
				RoutedEventHandler<ArgsT> hxx(nullptr);
				try {
					auto hx = any_cast<RoutedEventHandler<ArgsT>>(h);
				}
				catch (...) {
					nbThrowException(std::logic_error, "[%s]'s args type should be [%s]", args.Event.name().data(), args.Event.argsType().name());
				}
				hx.invoke(args);
			}
		}
	}
	
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
