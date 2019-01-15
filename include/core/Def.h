#pragma once
#include <typeinfo>
#include <string>
#include <stdint.h>
#include <memory>
#include <algorithm>

//Ҫ��c++11
//#if __cplusplus < 201103L
//	#error "c++11 supported requested."
//#endif

//ƽ̨ʶ��,���ʶ����ƽ̨����������������������ֹ����
#define PLATFORM_UNKNOWN					0x00000001
#define PLATFORM_WINDOWS					0x00000002
#define PLATFORM_WINCE						0x00000004
#define PLATFORM_LINUX_X11					0x00000008
#define PLATFORM_LINUX_ARM					0x00000010
#define PLATFORM_MAC						0x00000020
#define PLATFORM_IOS						0x00000040
#define PLATFORM_ANDROID					0x00000080
#define NB_SDK_TARGET_PLATFORM				PLATFORM_UNKNOWN

//��UNIX�¿�ʹ��g++ -dM -E - </dev/null����鿴������Ĭ�Ϻ�
#if defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)	//windows
	#undef	NB_SDK_TARGET_PLATFORM
	#define NB_SDK_TARGET_PLATFORM		PLATFORM_WINDOWS
	#pragma warning(disable: 4251)
#elif defined(WINCE)															//wince
	#undef	NB_SDK_TARGET_PLATFORM
	#define NB_SDK_TARGET_PLATFORM		PLATFORM_WINCE
#elif defined(__ARMEL__) || defined(LINUX_ARM) || defined(__aarch64__)			//linux-arm
	#undef	NB_SDK_TARGET_PLATFORM
	#define NB_SDK_TARGET_PLATFORM		PLATFORM_LINUX_ARM
#elif defined(linux) || defined(__linux__) || defined(__LINUX__)				//linux-x11
	#undef	NB_SDK_TARGET_PLATFORM
	#define NB_SDK_TARGET_PLATFORM		PLATFORM_LINUX_X11
#elif defined(__ANDROID__) || (__Android__)										//android
	#undef	NB_SDK_TARGET_PLATFORM
	#define NB_SDK_TARGET_PLATFORM		PLATFORM_ANDROID
#elif defined(__IOS__) || defined(__Ios__) || defined(ios)						//ios��iosֻ���������ã���
	#undef	NB_SDK_TARGET_PLATFORM
	#define NB_SDK_TARGET_PLATFORM		PLATFORM_IOS
#elif defined(__APPLE__) || defined(Mac) || defined(Apple)						//mac
	#undef	NB_SDK_TARGET_PLATFORM
	#define NB_SDK_TARGET_PLATFORM		PLATFORM_MAC
#else
	#error "!!!!!!!!!!Can not recognize the target platform type: have you configured an sopported platform ? check file 'core/Def.h' to confirm the Macro 'NB_SDK_TARGET_PLATFORM'.!!!!!!!!!!"
#endif

#define NB_NAMESPACE_CORE_BEGIN		namespace nb{ namespace core{
#define NB_NAMESPACE_MEDIA_BEGIN	namespace nb{ namespace media{
#define NB_NAMESPACE_GLES_BEGIN		namespace nb{ namespace gl{
#define NB_NAMESPACE_GUI_BEGIN		namespace nb{ namespace gui{
#define NB_NAMESPACE_END			}}
#define NB_USING_NAMESPACE_CORE		using namespace nb::core;
#define NB_USING_NAMESPACE_MEDIA	using namespace nb::media;
#define NB_USING_NAMESPACE_GLES		using namespace nb::gl;
#define NB_USING_NAMESPACE_GUI		using namespace nb::gui;

//����API������
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS
	#define NB_API					__declspec(dllexport)
	#define NB_SPRINTF				_snprintf_s
#else
	#define NB_API
	#define NB_SPRINTF				snprintf
#endif

#define NB_TYPE_NAME(type)			typeid(type).name()
#define NB_THROW_EXCEPTION(content) throw nb::core::Exception(content, __FILE__, __LINE__); 

namespace nb {

	//��Ա������vc���޷�������Linux���޴����⡣Ŀǰû�кð취�����ֻ�����ɺ����ķ�ʽ
	//��ʾPI=3.1415926
	NB_API double pi();

	//��ʾe=2.7182818
	NB_API double e();

	//�Ƕ�ת����
	NB_API double angleToRadian(double angle);

	//����ת�Ƕ�
	NB_API double radioToAngle(double radian);

	//Լ���ڣ���ֵ��0.00001�ڱ�ʾfloat���
	NB_API bool approximatelyEqual(float f1, float f2);

	//Լ���ڣ���ֵ��0.000000000001�ڱ�ʾdouble���
	NB_API bool approximatelyEqual(double d1, double d2);

	//����Լ���ڣ���ʾ��ֵ��f1��f2����������ֵ�������Ժ��Բ��ơ�����f1��f2��Ϊ�ڼ����������ǵĲ�ֵΪ10��������Ϊ�����ϵ�Լ����
	NB_API bool magnitudeEqual(float f1, float f2);

	//����Լ����
	NB_API bool magnitudeEqual(double d1, double d2);

	//ȡ�߽��ڵĺϷ�ֵ�������min��max�ᱻ������������ֵ������min, max��Ҳ������value����Bound(1, 5, 10) = 5; Bound(1, 5, 0) = 1; Bound(1, 5, 3) = 3;
	//min��max������Ϊ�꣬��Ҫ��()
	template<class T>
	NB_API const T &bound(const T &lower, const T &upper, const T &value)
	{
		return (std::max)((std::min)(lower, upper), (std::min)((std::max)(lower, upper), value));
	}

	//ȡ��ֵ����ʾvalue��v1��v2�������ֵ������ֵһ����v1����v2��
	template<class T>
	NB_API const T &nearBy(const T &v1, const T &v2, const T &value)
	{
		return std::abs(v1 - value) > std::abs(v2 - value) ? v2 : v1;
	}

	//��һ������ķ�Χ������ DistanceFromArea(1, 5, -1)����2��DistanceFromArea(1, 5, 3)����0��DistanceFromArea(1, 5, 9)����4
	template<class T>
	NB_API const T distanceFromArea(const T &xBound, const T &yBound, const T &val)
	{
		return (val < xBound) ? xBound - val : (val > yBound ? val - yBound : int(0));
	}

	//��ȡĿ��ƽ̨����
	NB_API int getTargetPlatformType();
	NB_API std::string getTargetPlatformName();

	//��ȡ����������ʱ�ӵδ�������������
	NB_API uint64_t getTickCount();

	//��ȡ��ǰ����id
	NB_API int getCurrentProcessId();

	//��ȡ��ǰ�߳�id
	NB_API int getCurrentThreadId();

	//����pid��ȡ������
	NB_API std::string getProcessName(int pid);

	//������/����/΢��
	NB_API void sleep(int seconds);
	NB_API void msleep(int milliseconds);
	NB_API void usleep(int useconds);
}