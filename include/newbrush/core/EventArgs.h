#pragma once
#include <bitset>
#include "newbrush/core/Point.h"
#include "newbrush/core/Size.h"
#include "newbrush/core/RoutedEvent.h"

namespace nb {

class DependencyProperty;
using DependencyPropertyPtr = std::shared_ptr<DependencyProperty>;

//����ö��
enum class KeyE
{
	None = 0,																				//��
	Cancel,																					//ȡ��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	Back,																					//Backspace�˸��
	Tab,																					//Tab��
	LineFeed,																				//���м�����ʱ�޷��ҵ���Ӧ���̣�TODO��
	Clear,																					//���������ʱ�޷��ҵ���Ӧ���̣�TODO��
	Return = 6,																				//�س���
	Enter = 6,																				//�س���
	Pause,																					//��ͣ��/Break����һ�������Ϸ�
	Capital = 8,																			//��Сд�л���
	CapsLock = 8,																			//��Сд�л���
	KanaMode = 9,																			//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	HangulMode = 9,																			//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	JunjaMode,																				//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	FinalMode,																				//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	HanjaMode = 12,																			//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	KanjiMode = 12,																			//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	Escape,																					//Esc��
	ImeConvert,																				//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	ImeNonConvert,																			//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	ImeAccept,																				//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	ImeModeChange,																			//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	Space,																					//�ո��
	Prior = 19,																				//ǰһ/��һҳ��
	PageUp = 19,																			//ǰһ/��һҳ��
	Next = 20,																				//��һ/��һҳ��
	PageDow = 20,																			//��һ/��һҳ��
	End,																					//������
	Home,																					//Home��
	Left,																					//�������
	Up,																						//���ϼ���
	Right,																					//���Ҽ���
	Down,																					//���¼���
	Select,																					//ѡ�������ʱ�޷��ҵ���Ӧ���̣�TODO��
	Print,																					//��ӡ������ʱ�޷��ҵ���Ӧ���̣�TODO��
	Execute,																				//ִ�м�����ʱ�޷��ҵ���Ӧ���̣�TODO��
	Snapshot = 30,																			//��Ļ���ռ����м�����WPF����Ӧ��TODO��
	PrintScreen = 30,																		//��Ļ���ռ����м�����WPF����Ӧ��TODO��
	Insert,																					//�����
	Delete,																					//ɾ����
	Help,																					//����������ʱ�޷��ҵ���Ӧ���̣�TODO��
	D0 = 34, D1, D2, D3, D4, D5, D6, D7, D8, D9,											//���ּ�0-9
	A = 44, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,		//��ĸ��A-Z
	LWin,																					//��win��
	RWin,																					//��win��
	Apps,																					//�Ҽ���������������win������ctrl��ֱ��
	Sleep,																					//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	NumPad0 = 74, NumPad1, NumPad2, NumPad3, NumPad4, NumPad5,
	NumPad6, NumPad7, NumPad8, NumPad9,														//����������ְ���
	Multiply,																				//��
	Add,																					//��
	Separator,																				//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	Subtract,																				//��
	Decimal,																				//С����
	Divide,																					//��
	F1 = 90, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
	F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,								//F*����F8�����ã�F10����System����
	NumLock,																				//����������ּ���
	Scroll,																					//Scroll Lock��
	LeftShift,																				//��Shift
	RightShift,																				//��Shift
	LeftCtrl,																				//��Ctrl
	RightCtrl,																				//��Ctrl
	LeftAlt,																				//��Alt
	RightAlt,																				//��Alt
	BrowserBack,																			//������˺��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	BrowserForward,																			//�������ǰ�������ʱ�޷��ҵ���Ӧ���̣�TODO��
	BrowserRefresh,																			//�����ˢ��ҳ�棨��ʱ�޷��ҵ���Ӧ���̣�TODO��
	BrowserStop,																			//�����ֹͣˢ�£���ʱ�޷��ҵ���Ӧ���̣�TODO��
	BrowserSearch,																			//�������������ʱ�޷��ҵ���Ӧ���̣�TODO��
	BrowserFavorites,																		//������ղؼУ���ʱ�޷��ҵ���Ӧ���̣�TODO��
	BrowserHome,																			//�������ҳ����ʱ�޷��ҵ���Ӧ���̣�TODO��
	VolumeMute,																				//������������ʱ�޷��ҵ���Ӧ���̣�TODO��
	VolumeDown,																				//������С��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	VolumeUp,																				//�������󰴼�����ʱ�޷��ҵ���Ӧ���̣�TODO��
	MediaNextTrack,																			//ý�岥������һ����������ʱ�޷��ҵ���Ӧ���̣�TODO��
	MediaPreviousTrack,																		//ý�岥������һ����������ʱ�޷��ҵ���Ӧ���̣�TODO��
	MediaStop,																				//ý�岥����ֹͣ��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	MediaPlayPause,																			//ý�岥��������/��ͣ��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	LaunchMail,																				//�����ʼ���������ʱ�޷��ҵ���Ӧ���̣�TODO��
	SelectMedia,																			//ѡ��ý�尴������ʱ�޷��ҵ���Ӧ���̣�TODO��
	LaunchApplication1,																		//����app1����
	LaunchApplication2,																		//����app2����
	Oem1 = 140,																				//�ֺ�ð�ż�
	OemSemicolon = 140,																		//�ֺ�ð�ż�
	OemPlus,																				//�Ӻż�
	OemComma,																				//���ż�
	OemMinus,																				//���ż�
	OemPeriod,																				//���/��ż�
	Oem2 = 145,																				//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	OemQuestion = 145,																		//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	Oem3 = 146,																				//���˺ż�
	OemTilde = 146,																			//���˺ż�
	AbntC1,																					//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	AbntC2,																					//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	Oem4 = 149,																				//�����ż�
	OemOpenBrackets = 149,																	//�����ż�
	Oem5 = 150,																				//б���ߺż�
	OemPipe = 150,																			//б���ߺż�
	Oem6 = 151,																				//�ҷ����ż�
	OemCloseBrackets = 151,																	//�ҷ����ż�
	Oem7 = 152,																				//���ż�
	OemQuotes = 152,																		//���ż�
	Oem8,																					//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	Oem102 = 154,																			//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	OemBackslash = 154,																		//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	ImeProcessed,																			//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	System,																					//��Ctrl����Ctrl��F10 WPF���ᷢ�ü�������ʵ��TODO��
	OemAttn = 157,																			//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	DbeAlphanumeric = 157,																	//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	OemFinish = 158,																		//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	DbeKatakana = 158,																		//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	OemCopy = 159,																			//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	DbeHiragana = 159,																		//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	OemAuto = 160,																			//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	DbeSbcsChar = 160,																		//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	OemEnlw = 160,																			//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	DbeDbcsChar = 161,																		//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	OemBackTab = 162,																		//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	DbeRoman = 162,																			//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	Attn = 163,																				//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	DbeNoRoman = 163,																		//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	CrSel = 164,																			//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	DbeEnterWordRegisterMode = 164,															//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	ExSel = 165,																			//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	DbeEnterImeConfigureMode = 165,															//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	EraseEof = 166,																			//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	DbeFlushString = 166,																	//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	Play = 167,																				//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	DbeCodeInput = 167,																		//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	Zoom = 168,																				//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	DbeNoCodeInput = 168,																	//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	NoName = 169,																			//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	DbeDetermineString = 169,																//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	Pa1 = 170,																				//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	DbeEnterDialogConversionMode = 170,														//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	OemClear,																				//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
	DeadCharProcessed = 172,																//δ֪��������ʱ�޷��ҵ���Ӧ���̣�TODO��
};

//����״̬ö��
enum class KeyStateE : uint8_t
{
	None = 0,	//δѹ��
	Down,		//ѹ��
	Toggled,	//���л�
};

enum class MouseButtonE : uint8_t
{
	Left,		//��ť
	Middle,		//�м䰴ť
	Right,		//�Ұ�ť
};

enum class MouseButtonStateE : uint8_t
{
	Released,	//���ͷ�
	Pressed,	//��ѹ��
};

enum class ReasonSessionEnding
{
	Logoff,					//�����û�ע�������ĻỰ��ֹ
	Shutdown,				//�����û��ػ������ĻỰ��ֹ
};

struct EventArgs { Object *sender; };
struct UnhandledExceptionEventArgs { std::exception e; };
struct ExitEventArgs { int exitCode; };
struct CancelEventArgs : public EventArgs { bool cancel{ false }; };
struct SessionEndingCancelEventArgs : public CancelEventArgs { ReasonSessionEnding reason; };
struct StartupEventArgs { std::vector<std::string> args; };

class NB_API RoutedEventArgs : public EventArgs
{
public:
	RoutedEventArgs();
	RoutedEventArgs(const RoutedEvent &routedEvent);
	RoutedEventArgs(const RoutedEvent &routedEvent, Object *source);
	virtual ~RoutedEventArgs() = default;

	bool		Handled;
	RoutedEvent	Event;
	Object		*OriginalSource;
	Object		*Source;
};

struct NB_API InputEventArgs : public RoutedEventArgs
{
public:
	InputEventArgs(int timestamp);
	int		Timestamp;		//�¼�������ʱ��
};


class InputElement;
class NB_API MouseEventArgs : public InputEventArgs
{
public:
	MouseEventArgs(int timestamp);

	Point getPosition(std::shared_ptr<InputElement> relativeTo) const;			//��ȡ��������ָ��Ԫ�ص�λ��

	MouseButtonStateE	LeftButton;		//��ť״̬
	MouseButtonStateE	MiddleButton;	//�м䰴ť״̬
	MouseButtonStateE	RightButton;	//�Ұ�ť״̬
};

class NB_API MouseButtonEventArgs : public MouseEventArgs
{
public:
	MouseButtonEventArgs(int timestamp, MouseButtonE button);

	MouseButtonE		ChangedButton;	//�����İ�ť
	MouseButtonStateE	ButtonState;	//��ť״̬
	int					ClickCount;		//����������ɴ�������˫�����������ж�
};

class NB_API MouseWheelEventArgs : public MouseEventArgs
{
public:
	MouseWheelEventArgs(int timestamp, int delta);

	int	Delta;							//����ֵ
};

class InputElement;
class NB_API Keyboard
{
public:
	static KeyStateE getKeyState(KeyE key);
	static bool isKeyDown(KeyE key);
	static bool isKeyUp(KeyE key);
	static bool isKeyToggled(KeyE key);
	std::shared_ptr<InputElement> focus(std::shared_ptr<InputElement> element);
};

class NB_API KeyboardEventArgs : public InputEventArgs
{
public:
	KeyboardEventArgs(int timestamp);
};

//���̽���仯�¼�
class NB_API KeyboardFocusChangedEventArgs : public KeyboardEventArgs
{
public:
	KeyboardFocusChangedEventArgs(int timestamp, std::shared_ptr<InputElement> oldFocus, std::shared_ptr<InputElement> newFocus);

	std::shared_ptr<InputElement>	OldFocus;	//��ǰ���н����Ԫ��
	std::shared_ptr<InputElement>	NewFocus;	//���ƶ�����Ԫ��
};

//�����¼����������WPF�в�࣬��Ҫ�ص�ע�⣩
class NB_API KeyEventArgs : public KeyboardEventArgs
{
public:
	KeyEventArgs(int timestamp, KeyE key);

	KeyE			SystemKey;	//��ϵͳ��������ļ���ϵͳ����F10����Alt����Alt�������������Alt��[systemKey, key]=[Alt, System]���������Alt+A=[A, System]
	KeyE			Key;		//����
	std::bitset<3>	WKeyState;	//����״̬
};

struct NB_API TouchEventArgs : public InputEventArgs
{
	TouchEventArgs(int timestamp);

	Point getTouchPoint() const;
};

struct NB_API DragEventArgs : public RoutedEventArgs
{

};

struct SizeChangedEventArgs : public RoutedEventArgs
{
	Size previousSize;
	Size newSize;
	bool widthChanged;
	bool HeightChanged;
};

struct DependencyPropertyChangedEventArgs
{
	DependencyPropertyPtr	property;
	var						oldValue;
	var						newValue;
};

class RoutedProperyChangedEventArgs : public RoutedEventArgs
{
public:
	var		oldValue;
	var		newValue;
};

class ExceptonRoutedEventArgs
{
public:
	std::exception	errorException;
};

}