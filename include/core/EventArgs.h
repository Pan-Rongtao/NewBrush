#pragma once
#include "../core/Def.h"

namespace nb {
	
enum class ReasonSessionEnding
{
	Logoff,					//�����û�ע�������ĻỰ��ֹ
	Shutdown,				//�����û��ػ������ĻỰ��ֹ
};

struct EventArgs{};
struct UnhandledExceptionEventArgs { std::exception e; };
struct ExitEventArgs { int exitCode; };
struct CancelEventArgs : public EventArgs { bool cancel{false}; };
struct SessionEndingCancelEventArgs : public CancelEventArgs { ReasonSessionEnding reason; };
struct StartupEventArgs { std::vector<std::string> args; };


}