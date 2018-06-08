/******************************************************************************

* Copyright (c) 2017���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-04

* ��Ҫ����:  ϵͳ��ص��쳣

* �޸ļ�¼:

*****************************************************************************/
#include "core/Exception.h"

namespace nb{ namespace System{

//ϵͳ�쳣����
class NB_EXPORT SystemException : public nb::Core::Exception
{
public:
	SystemException();
	SystemException(const char *message);
};
typedef nbObjectPtrDerive<SystemException, nb::Core::ExceptionPtr>	SystemExceptionPtr;

//�߼�����
class NB_EXPORT LogicException : public SystemException
{
public:
	LogicException();
	LogicException(const char *message);

};
typedef nbObjectPtrDerive<LogicException, SystemExceptionPtr>	LogicExceptionPtr;

//����ĵ���ʱ��
class NB_EXPORT BadTimingOperationException : public LogicException
{
public:
	BadTimingOperationException();
	BadTimingOperationException(const char *message);

};
typedef nbObjectPtrDerive<BadTimingOperationException, LogicExceptionPtr>	BadTimingOperationExceptionPtr;

}}