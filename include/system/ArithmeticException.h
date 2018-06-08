/******************************************************************************

* Copyright (c) 2017���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-04

* ��Ҫ����:  ������ص��쳣

* �޸ļ�¼:

*****************************************************************************/
#include "core/Exception.h"

namespace nb{ namespace System{

class NB_EXPORT ArithmeticException : public nb::Core::Exception
{
public:
	ArithmeticException();
	ArithmeticException(const char *message);
};
typedef nbObjectPtrDerive<ArithmeticException, nb::Core::ExceptionPtr>	ArithmeticExceptionPtr;

//ʮ������������ͼ��������������쳣
class NB_EXPORT DivideByZeroException : public ArithmeticException
{
public:
	DivideByZeroException();
	DivideByZeroException(const char *message);

};
typedef nbObjectPtrDerive<DivideByZeroException, ArithmeticExceptionPtr>	DivideByZeroExceptionPtr;

}}
