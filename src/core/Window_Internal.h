#pragma once
#include <map>
#include "core/Def.h"
#include "core/Window.h"
#ifdef NB_OS_FAMILY_WINDOWS
	#include <Windows.h>
	#include <WindowsX.h>
#elif defined NB_OS_FAMILY_UNIX
	#include <X11/X.h>
	#include <X11/Xlib.h>
#elif NB_OS == NB_OS_LINUX_ARM
	#include <wayland-client.h>
	#include <wayland-egl.h>
#endif

namespace nb{ namespace core{

class Window_Internal
{
public:
	Window_Internal(Window *p);
	~Window_Internal();

	void setTitle(const std::string &title);
	std::string title() const;

	void setX(int x);
	int x() const;

	void setY(int y);
	int y() const;

	void setWidth(int width);
	int width() const;

	void setHeight(int height);
	int height() const;

	int clientWidth() const;
	int clientHeight() const;

	long handle() const;

	void setTopMost(bool topMost);
	bool topMost() const;

	void setWindowState(WindowStateE state);
	WindowStateE getWindowState() const;

	void setWindowStyle(WindowStyleE style);
	WindowStyleE getWindowStyle() const;
	
	void show(bool show);
	bool isShow() const;

	void active();

	void pending();

private:
	Window				*m_pW;

	//���ݲ�ͬƽ̨��˽�б�����˽�к���
#ifdef NB_OS_FAMILY_WINDOWS
	static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	HINSTANCE						m_instance;
	HWND							m_hwnd;
	static std::map<long, Window *>	m_windows;
#elif defined NB_OS_FAMILY_UNIX
	void x11WindowPending();
	WindowEvent::KeyCode nativeKeyToKeycode(int key);
	::Display						*m_X11Display;
	::Window						m_X11WindowID;
	nb::core::RectI					m_rect;
	static wl_fixed_t x_pointer_move = 0;
	static wl_fixed_t y_pointer_move = 0;
#elif NB_OS == NB_OS_LINUX_ARM
	//wl_registry global��Ϣ
	static void onWaylandRegistryGlobal(void *data, struct wl_registry *wl_registry, uint32_t name, const char *interface, uint32_t version);

	//wl_seat capabilities��Ϣ
	static void onWaylandSeatCapabilitties(void *data, struct wl_seat *wl_seat, uint32_t capabilities);

	//wl_pointer enter��leave��motion��button��axis��Ϣ
	static void onWaylandPointerEnter(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface, wl_fixed_t surface_x, wl_fixed_t surface_y);
	static void onWaylandPointerLeave(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface);
	static void onWaylandPointerMotion(void *data, struct wl_pointer *wl_pointer, uint32_t time, wl_fixed_t surface_x, wl_fixed_t surface_y);
	static void onWaylandPointerButton(void *data, struct wl_pointer *wl_pointer, uint32_t serial, uint32_t time, uint32_t button, uint32_t state);
	static void onWaylandPointerAxis(void *data, struct wl_pointer *wl_pointer, uint32_t time, uint32_t axis, wl_fixed_t value);

	//wl_touch down��up��motion��cancel��Ϣ
	static void onWaylandTouchDown(void *data, struct wl_touch *wl_touch, uint32_t serial, uint32_t time, struct wl_surface *surface, int32_t id, wl_fixed_t x, wl_fixed_t y);
	static void onWaylandTouchUp(void *data, struct wl_touch *wl_touch, uint32_t serial, uint32_t time, int32_t id);
	static void onWaylandTouchMotion(void *data, struct wl_touch *wl_touch, uint32_t time, int32_t id, wl_fixed_t x, wl_fixed_t y);
	static void onWaylandTouchFrame(void *data, struct wl_touch *wl_touch);
	static void onWaylandTouchCancel(void *data, struct wl_touch *wl_touch);

	//wl_keyboard ��Ϣ
	static void onWaylandKeyEnter(void *data, struct wl_keyboard *wl_keyboard, uint32_t serial, struct wl_surface *surface, struct wl_array *keys);
	static void onWaylandKeyLeave(void *data, struct wl_keyboard *wl_keyboard, uint32_t serial, struct wl_surface *surface);
	static void onWaylandKey(void *data, struct wl_keyboard *wl_keyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state);


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
		UserData() {}

		Globals						wlGlobals;					//ȫ�ֶ���ṹ����Ϊuserdata����
		SeatGroup					wlSeatGroup;				//�豸��ṹ����Ϊuserdata����
		Listeners					wlListeners;				//�����ṹ
	//	WindowEvent *				windowEvent;
	};

	wl_display						*m_wlDisplay;				//wayland���������
	wl_registry						*m_wlRegistry;				//ȫ�ֶ���ע���
	wl_surface						*m_wlSurface;				//wayland surface
	wl_shell_surface				*m_wlShellSurface;			//wayland shell surface
	wl_egl_window					*m_wlWindow;				//wayland window��egl nativewindow��
	UserData						m_UserData;
#endif
};



}}
