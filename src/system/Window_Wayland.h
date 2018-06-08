#pragma once
#include "system/Platform.h"

#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
#include <wayland-client.h>
#include <wayland-egl.h>
#include "NativeWindow.h"

namespace nb{ namespace System{

class Window;
class Window_Wayland : public NativeWindow
{
public:
	Window_Wayland(Window *pW);
	~Window_Wayland();

	virtual void SetCaption(const nb::System::String &caption);
	virtual nb::System::String GetCaption() const;

	virtual void SetRect(const nb::System::RectI &rect);
	virtual nb::System::RectI GetRect() const;

	virtual long GetWindowHandle();

	virtual void Pending();

private:
	//wl_registry global��Ϣ
	static void OnWaylandRegistryGlobal(void *data, struct wl_registry *wl_registry, uint32_t name, const char *interface, uint32_t version);

	//wl_seat capabilities��Ϣ
	static void OnWaylandSeatCapabilitties(void *data, struct wl_seat *wl_seat, uint32_t capabilities);

	//wl_pointer enter��leave��motion��button��axis��Ϣ
	static void OnWaylandPointerEnter(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface, wl_fixed_t surface_x, wl_fixed_t surface_y);
	static void OnWaylandPointerLeave(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface);
	static void OnWaylandPointerMotion(void *data, struct wl_pointer *wl_pointer, uint32_t time, wl_fixed_t surface_x, wl_fixed_t surface_y);
	static void OnWaylandPointerButton(void *data, struct wl_pointer *wl_pointer, uint32_t serial, uint32_t time, uint32_t button, uint32_t state);
	static void OnWaylandPointerAxis(void *data, struct wl_pointer *wl_pointer, uint32_t time, uint32_t axis, wl_fixed_t value);

	//wl_touch down��up��motion��cancel��Ϣ
	static void OnWaylandTouchDown(void *data, struct wl_touch *wl_touch, uint32_t serial, uint32_t time, struct wl_surface *surface, int32_t id, wl_fixed_t x, wl_fixed_t y);
	static void OnWaylandTouchUp(void *data, struct wl_touch *wl_touch, uint32_t serial, uint32_t time, int32_t id);
	static void OnWaylandTouchMotion(void *data, struct wl_touch *wl_touch, uint32_t time, int32_t id, wl_fixed_t x, wl_fixed_t y);
	static void OnWaylandTouchFrame(void *data, struct wl_touch *wl_touch);
	static void OnWaylandTouchCancel(void *data, struct wl_touch *wl_touch);

	//wl_keyboard ��Ϣ
	static void OnWaylandKeyEnter(void *data, struct wl_keyboard *wl_keyboard, uint32_t serial, struct wl_surface *surface, struct wl_array *keys);
	static void OnWaylandKeyLeave(void *data, struct wl_keyboard *wl_keyboard, uint32_t serial, struct wl_surface *surface);
	static void OnWaylandKey(void *data, struct wl_keyboard *wl_keyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state);


	//waylandȫ�ֶ���ֻ��ͨ��wl_registry_listener��Ϣ�л�ȡ
	struct Globals
	{
		Globals() : wlCompositor(NULL), wlShell(NULL), wlSeat(NULL) {}

		wl_compositor				*wlCompositor;				//���ںϳ�������������ȫ�ֶ���
		wl_shell					*wlShell;					//shellȫ�ֶ���
		wl_seat						*wlSeat;					//�豸������ȫ�ֶ���
	};
	struct SeatGroup
	{
		SeatGroup() : wlPointer(NULL), wlTouch(NULL), wlKeyboard(NULL) {}

		wl_pointer					*wlPointer;					//��ָ����
		wl_touch					*wlTouch;					//��㴥��
		wl_keyboard					*wlKeyboard;				//�����豸
	};
	struct Listeners
	{
		wl_registry_listener		wlRegistryListener;			//ȫ�ֶ������
		wl_seat_listener			wlSeatListener;				//�豸�������
		wl_pointer_listener			wlPointerListener;			//��ָ���ؼ���
		wl_touch_listener			wlTouchListener;			//��㴥������
		wl_keyboard_listener		wlKeyboardListener;			//���̼���
		wl_surface_listener			wlShellListener;			//shell����
		wl_shell_surface_listener	wlShellSurfaceListener;		//shell surface����
	};
	struct UserData
	{
		UserData() : windowEvent(NULL) {}

		Globals						wlGlobals;					//ȫ�ֶ���ṹ����Ϊuserdata����
		SeatGroup					wlSeatGroup;				//�豸��ṹ����Ϊuserdata����
		Listeners					wlListeners;				//�����ṹ
		WindowEvent *				windowEvent;
	};

	wl_display						*m_wlDisplay;				//wayland���������
	wl_registry						*m_wlRegistry;				//ȫ�ֶ���ע���
	wl_surface						*m_wlSurface;				//wayland surface
	wl_shell_surface				*m_wlShellSurface;			//wayland shell surface
	wl_egl_window					*m_wlWindow;				//wayland window��egl nativewindow��
	UserData						m_UserData;

	nb::System::String				m_Caption;
	nb::System::RectI				m_Rect;
};

}}

#endif
