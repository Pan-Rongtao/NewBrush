#pragma once
#include "newbrush/core/DependencyObject.h"
#include "newbrush/core/Size.h"
#include "newbrush/core/Rect.h"
#include "newbrush/media/Thickness.h"
#include "newbrush/gui/Style.h"
#include "newbrush/gui/VisualStateMachine.h"
#include "newbrush/core/RoutedEvent.h"
#include "newbrush/media/Transform.h"

namespace nb{
class Viewport2D;

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

class NB_API UIElement : public DependencyObject
{
	NB_OBJECT
public:
	UIElement();
	virtual ~UIElement() = default;

	static DependencyProperty					NameProperty();			//���ӵ��������ԣ�string��
	static DependencyProperty					VisibilityProperty();	//���ӵ��������ԣ�bool��
	static DependencyProperty					OpacityProperty();		//��͸���ȵ��������ԣ�float��
	static DependencyProperty					FocusableProperty();	//�Ƿ���ý�����������ԣ�bool��
	static DependencyProperty					IsFocusedProperty();	//Ԫ�ص�ǰ�Ƿ���н�����������ԣ�bool��ֻ��
	static DependencyProperty 					WidthProperty();		//�趨����������ԣ�float��
	static DependencyProperty 					HeightProperty();		//�趨�ߵ��������ԣ�float��
	static DependencyProperty 					MinWidthProperty();		//��С����������ԣ�float��
	static DependencyProperty 					MinHeightProperty();	//��С�ߵ��������ԣ�float��
	static DependencyProperty 					MaxWidthProperty();		//������������ԣ�float��
	static DependencyProperty 					MaxHeightProperty();	//���ߵ��������ԣ�float��
	static DependencyProperty 					DesiredSizeProperty();	//�����ߴ���������ԣ�Size��ֻ��
	static DependencyProperty 					ActualSizeProperty();	//ʵ�ʳߴ���������ԣ�Size��ֻ��
	static DependencyProperty 					RenderSizeProperty();	//��Ⱦ�ߴ���������ԣ�Size��ֻ��
	static DependencyProperty 					OffsetProperty();		//��Ը�ƫ�������������ԣ�float��δ֪
	static DependencyProperty 					MarginProperty();		//��Ե���������ԣ�Thickness��
	static DependencyProperty 					HorizontalAlignmentProperty();	//������뷽ʽ���������ԣ�HorizontalAlignmentE��
	static DependencyProperty 					VerticalAlignmentProperty();	//������뷽ʽ���������ԣ�VerticalAlignmentE��
	static DependencyProperty 					FlowDirectionProperty();		//������������ԣ�FlowDirectionE��
	static DependencyProperty 					StyleProperty();		//�����������ԣ�std::shared_ptr<Style>)
	static DependencyProperty 					StateMachineProperty();	//״̬�����������ԣ�std::shared_ptr<VisualStateMachine>��
	static DependencyProperty 					IsMouseOverProperty();	//����Ƿ���Ԫ���ϣ�bool��ֻ��
	static DependencyProperty 					RenderTransformProperty(); //�任����������(std::make_shared<Transform>())

	Event<EventArgs>							Initialized;
	Event<RoutedEventArgs>						Loaded;
	Event<RoutedEventArgs>						Unloaded;
	Event<SizeChangedEventArgs>					SizeChanged;

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

	static RoutedEvent							LoadedEvent();
	static RoutedEvent							UnloadedEvent();
	static RoutedEvent							SizeChangedEvent();
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

	virtual std::shared_ptr<UIElement> clone() const;

	//��ȡ�ӽڵ��������ʵ�ַ���0
	virtual uint32_t childrenCount() const;

	//��ȡ�ӽڵ㣬��ʵ���׳�std::out_of_range
	virtual UIElement *getChild(uint32_t index);

	void setParent(UIElement *element);
	UIElement *getParent();

	UIElement *getRoot();
	Point worldOffset() const;
	void updateLayout();

	void measure(const Size &availabelSize);
	void arrage(const Rect &finalRect);
	virtual void onRender(Viewport2D & drawContext);
	
	void addHandler(const RoutedEvent &event, const RoutedEventHandler &handler);
	void removeHandler(const RoutedEvent &event, const RoutedEventHandler &handler);
	void raiseEvent(std::shared_ptr<RoutedEventArgs> args);
	
	virtual bool hitTestCore(const Point &pt) const;
	
public:
	virtual Size measureOverride(const Size &availableSize);
	virtual Size arrangeOverride(const Size &finalSize);

protected:
	void addLogicalChild(std::shared_ptr<UIElement> child);
	void removeLogicalChild(std::shared_ptr<UIElement> child);

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args) override;
	virtual void onStyleChanged(std::shared_ptr<Style> oldStyle, std::shared_ptr<Style> newStyle);

	virtual void onDragEnter(const DragEventArgs &args);
	virtual void onDragLeave(const DragEventArgs &args);
	virtual void onDragOver(const DragEventArgs &args);
	virtual void onDrop(const DragEventArgs &args);
	virtual void onGotFocus(const RoutedEventArgs &args);
	virtual void onGotKeyboardFocus(const KeyboardFocusChangedEventArgs &args);
	virtual void onGotMouseCapture(const MouseEventArgs &args);
	virtual void onGotTouchCapture(const TouchEventArgs &args);
	virtual void onKeyDown(const KeyEventArgs &args);
	virtual void onKeyUp(const KeyEventArgs &args);
	virtual void onLostFocus(const RoutedEventArgs &args);
	virtual void onLostKeyboardFocus(const KeyboardFocusChangedEventArgs &args);
	virtual void onLostMouseCapture(const MouseEventArgs &args);
	virtual void onLostTouchCapture(const TouchEventArgs &args);
	virtual void onMouseEnter(const MouseEventArgs &args);
	virtual void onMouseLeave(const MouseEventArgs &args);
	virtual void onMouseDown(const MouseButtonEventArgs &args);
	virtual void onMouseUp(const MouseButtonEventArgs &args);
	virtual void onMouseLeftButtonDown(const MouseButtonEventArgs &args);
	virtual void onMouseLeftButtonUp(const MouseButtonEventArgs &args);
	virtual void onMouseRightButtonDown(const MouseButtonEventArgs &args);
	virtual void onMouseRightButtonUp(const MouseButtonEventArgs &args);
	virtual void onMouseMove(const MouseEventArgs &args);
	virtual void onMouseWheel(const MouseWheelEventArgs &args);
	virtual void onTouchDown(const TouchEventArgs &args);
	virtual void onTouchEnter(const TouchEventArgs &args);
	virtual void onTouchLeave(const TouchEventArgs &args);
	virtual void onTouchMove(const TouchEventArgs &args);
	virtual void onTouchUp(const TouchEventArgs &args);
	//preview
	virtual void onPreviewDragEnter(const DragEventArgs &args);
	virtual void onPreviewDragLeave(const DragEventArgs &args);
	virtual void onPreviewDragOver(const DragEventArgs &args);
	virtual void onPreviewDrop(const DragEventArgs &args);
	virtual void onPreviewGotKeyboardFocus(const KeyboardFocusChangedEventArgs &args);
	virtual void onPreviewKeyDown(const KeyEventArgs &args);
	virtual void onPreviewKeyUp(const KeyEventArgs &args);
	virtual void onPreviewLostKeyboardFocus(const KeyboardFocusChangedEventArgs &args);
	virtual void onPreviewMouseDown(const MouseButtonEventArgs &args);
	virtual void onPreviewMouseUp(const MouseButtonEventArgs &args);
	virtual void onPreviewMouseLeftButtonDown(const MouseButtonEventArgs &args);
	virtual void onPreviewMouseLeftButtonUp(const MouseButtonEventArgs &args);
	virtual void onPreviewMouseRightButtonDown(const MouseButtonEventArgs &args);
	virtual void onPreviewMouseRightButtonUp(const MouseButtonEventArgs &args);
	virtual void onPreviewMouseMove(const MouseButtonEventArgs &args);
	virtual void onPreviewMouseWheel(const MouseWheelEventArgs &args);
	virtual void onPreviewTouchDown(const TouchEventArgs &args);
	virtual void onPreviewTouchEnter(const TouchEventArgs &args);
	virtual void onPreviewTouchLeave(const TouchEventArgs &args);
	virtual void onPreviewTouchMove(const TouchEventArgs &args);
	virtual void onPreviewTouchUp(const TouchEventArgs &args);

private:
	enum Flags
	{
		IsMouseOverCache,
		IsLeftButtonDownCache,
		IsRightButtonDownCache,
		Flags_Max = 32,
	};

	void changedLogicParent(UIElement* parent);
	void onMouseMoveThunk(const MouseEventArgs &e, const Point &pt);
	void onMouseButtonThunk(const MouseButtonEventArgs &e, const Point &pt);

	UIElement	*m_parent;
	std::map<size_t, std::vector<RoutedEventHandler>>	m_eventHandlers;
	std::bitset<Flags_Max>	m_flags;
	Size m_lastMesaaeAvailabelSize;
	bool m_measureInProgress;

	friend class Window;
	friend class UIElementCollection;
};

using UIElementPtr = std::shared_ptr<UIElement>;

}