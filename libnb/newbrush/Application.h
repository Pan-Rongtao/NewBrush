#pragma once
#include <queue>
#include <mutex>
#include "newbrush/Event.h"
#include "newbrush/ResourceDictionary.h"
#include "newbrush/Window.h"

namespace nb{

enum class ReasonSessionEnding
{
	Logoff,					//�����û�ע�������ĻỰ��ֹ
	Shutdown,				//�����û��ػ������ĻỰ��ֹ
};

struct UnhandledExceptionEventArgs	{ std::exception e; };
struct ExitEventArgs				{ int exitCode; };
struct SessionEndingCancelEventArgs { bool cancel{ false }; ReasonSessionEnding reason; };
struct StartupEventArgs				{ std::vector<std::string> args; };

enum class ShutdownModeE : uint8_t
{
	OnExplicitShutdown,		//������shutdownʱ�ر�Ӧ�ó���
	OnLastWindowClose,		//���һ�����ڹرջ����shutdownʱ�ر�Ӧ�ó���
	OnMainWindowClose,		//�����ڹرջ����shutdownʱ�ر�Ӧ�ó���
};

class NB_API Application
{
public:
	//����һ��app�������������һ�Σ��ᷢ���쳣std::logic_error
	Application();
	virtual ~Application() = default;

	//��ȡappʵ�������δ�����������ؿ�
	static Application *get();

	//�ر�ģʽ
	void setShutdownMode(ShutdownModeE mode);
	ShutdownModeE shutdownMode() const;

	//���д���
	const WindowCollection &windows() const;

	//�����ڣ�Ĭ��Ϊ��һ�����ڣ�
	void setMainWindow(Window *w);
	Window *mainWindow();

	//��Դ
	ref<ResourceDictionary> resources();

	//����
	//����ֵ���˳��룬Ĭ�������Ϊ0
	int run(int argc, char *argv[]);

	//�ر�Ӧ�ó���
	//exitCode���ر��루��Ӧ�ó��򷵻�ֵ��
	void shutdown();
	void shutdown(int exitCode);

	//ע����
	template<class PluginT>
	void registerStudioPlugin()
	{
		_registerPlugin(createRef<PluginT>());
	}

	using CallBack = std::function<void(void)>;
	void connect(CallBack callback);

	Event<EventArgs>						Activated;				//��Ӧ�ó����Ϊǰ̨Ӧ�ó��򣬷���
	Event<EventArgs>						Deactivated;			//��Ӧ�ó�������ǰ̨Ӧ�ó��򣬷���
	Event<UnhandledExceptionEventArgs>		UnhandledException;		//����쳣����Ӧ�ó����������Ҽ̳���std::exception���쳣δ����ʱ����
	Event<EventArgs>						UnhandledExtraException;//����쳣����Ӧ�ó������������Զ�����쳣���쳣δ����ʱ����
	Event<ExitEventArgs>					Exit;					//�رչ��̵����֪ͨ
	Event<EventArgs>						LoadCompleted;			//������ɲ�����ʱ����
	Event<SessionEndingCancelEventArgs>		SessionEnding;			//�û���ע����رղ���ϵͳʱ����
	Event<StartupEventArgs>					Startup;				//������ʱ����

protected:
	virtual void onActivated(const EventArgs &args);
	virtual void onDeactivated(EventArgs &args);
	virtual void onExit(const ExitEventArgs &args);
	virtual void onLoadCompleted(const EventArgs &args);
	virtual void onSessionEnding(const SessionEndingCancelEventArgs &args);
	virtual void onStartUp(const StartupEventArgs &args);

private:
	void onWindowClosed(const bool &isMain);
	void onWindowFocused(const bool &focused);

	bool m_exitFlag;
	ShutdownModeE m_shutdownMode;
	ref<ResourceDictionary> m_resources;

	CallBack				pick();
	std::queue<CallBack>	m_msgQueue;
	std::mutex				m_mutex;
};

}
