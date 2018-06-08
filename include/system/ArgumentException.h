/******************************************************************************

* Copyright (c) 2017���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-04

* ��Ҫ����:  ������ص��쳣

* �޸ļ�¼:

*****************************************************************************/
#include <string>
#include "core/Exception.h"

namespace nb{ namespace System{

//�����쳣
class NB_EXPORT ArgumentException : public nb::Core::Exception
{
public:
	ArgumentException(const char *paramName);
	ArgumentException(const char *paramName, const char *message);

	const char *GetParamName() const;

private:
	std::string		m_ParamName;
};
typedef nbObjectPtrDerive<ArgumentException, nb::Core::ExceptionPtr>	ArgumentExceptionPtr;

//�մ��ݸ�����������Ϊ��Ч�����ķ���ʱ�������쳣
class NB_EXPORT ArgumentNullException : public ArgumentException
{
public:
	ArgumentNullException(const char *paramName);
	ArgumentNullException(const char *paramName, const char *message);

};
typedef nbObjectPtrDerive<ArgumentNullException, ArgumentExceptionPtr>	ArgumentNullExceptionPtr;

//����ֵ�������õķ��������������ȡֵ��Χʱ�������쳣
class NB_EXPORT ArgumentOutOfRangeException : public ArgumentException
{
public:
	ArgumentOutOfRangeException(const char *paramName, void *v, void *lowBound, void *upBound);
	ArgumentOutOfRangeException(const char *paramName, void *v, void *lowBound, void *upBound, const char *message);

	void *GetLowBound() const;
	void *GetUpBound() const;
	void *GetValue() const;

private:
	void	*m_LowBound;
	void	*m_UpBound;
	void	*m_V;
};
typedef nbObjectPtrDerive<ArgumentOutOfRangeException, ArgumentExceptionPtr>	ArgumentOutOfRangeExceptionPtr;


}}
