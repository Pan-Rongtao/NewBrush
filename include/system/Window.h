#pragma once
#include "core/Object.h"
#include "String.h"
#include "PointI.h"
#include "SizeI.h"
#include "RectI.h"

namespace nb{ namespace System{

class NativeWindow;
class WindowEvent;
class NB_EXPORT Window
{
public:
	//���ô��ڱ���
	void SetCaption(const nb::System::String &caption);

	//��ȡ���ڱ���
	nb::System::String GetCaption() const;

	//���ô���λ��x�������win32�����£�Ϊ�߿����߾ࣩ
	void SetX(int x);

	//��ȡ����x�������win32�����£�Ϊ�߿����߾ࣩ
	int GetX() const;

	//���ô���λ��y�������win32�����£�Ϊ�߿���ϱ߾ࣩ
	void SetY(int y);

	//��ȡ����y�������win32�����£�Ϊ�߿���ϱ߾ࣩ
	int GetY() const;

	//���ô���λ�ã������win32�����£�Ϊ�߿�����ϱ߾ࣩ
	void SetPos(const nb::System::PointI &pos);

	//��ȡ����λ�ã������win32�����£�Ϊ�߿�����ϱ߾ࣩ
	void SetPos(int x, int y);

	//��ȡ����λ�ã������win32�����£�Ϊ�߿�����ϱ߾ࣩ
	nb::System::PointI GetPos() const;

	//���ô��ڿͻ��˿��width
	//�쳣��width < 0
	void SetWidth(int width);

	//��ȡ���ڿͻ��˿��
	int GetWidth() const;

	//���ô��ڿͻ��˸߶�
	//�쳣��height < 0
	void SetHeight(int height);

	//��ȡ���ڿͻ��˸߶�
	int GetHeight() const;		

	//���ô��ڿͻ��˳ߴ�
	//�쳣��sz�еĿ���С��0
	void SetSize(const nb::System::SizeI &size);

	//��ȡ���ڿͻ��˳ߴ�
	nb::System::SizeI GetSize() const;

	//���ô������������win32�����£�λ��Ϊ�ı߿�����ϱ߾࣬�ߴ�Ϊ�ͻ�������
	//�쳣��rect�еĿ�͸�����һ��ֵС��0
	void SetRect(const nb::System::RectI &rect);

	//��ȡ�������������win32�����£�λ��Ϊ�ı߿�����ϱ߾࣬�ߴ�Ϊ�ͻ�������
	nb::System::RectI GetRect() const;

	//��鴰���¼�
	void Pending();

	//���ô����¼�����
	void SetListener(WindowEvent *listener);
	WindowEvent *GetListener() const;

	//��ȡ���ھ��
	long GetWindowHandle() const;

public:
	//����һ��Window�������ı���Ϊ�գ�����ΪRectI(x-middle, y-middle, 800, 480)
	Window();

	//����һ��Window�������ı���Ϊ�գ�����ΪRectI(x-middle, y-middle, width, height)
	Window(int width, int height);

	//����һ��Window�������ı���Ϊ�գ�����ΪRectI(x, y, width, height)
	Window(int x, int y, int width, int height);

	//����һ��Window�������ı���Ϊcaption������ΪRectI(x-middle, y-middle, 800, 480)
	explicit Window(const nb::System::String &caption);

	//����һ��Window�������ı���Ϊcaption������ΪRectI(x-middle, y-middle, width, height)
	Window(const nb::System::String &caption, int width, int height);

	//����һ��Window�������ı���Ϊcaption����������Ϊrect
	Window(const nb::System::String &caption, const nb::System::RectI &rect);

	virtual ~Window();

public:
//	static void Peek();

private:
	void CreateNative();
	void ReleaseNative();

	NativeWindow			*m_pNative;
	WindowEvent				*m_pListener;
};

}}
