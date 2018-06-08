/******************************************************************************

* Copyright (c) 2017���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-04

* ��Ҫ����:  ��������ص��쳣

* �޸ļ�¼:

*****************************************************************************/
#include "core/Exception.h"

namespace nb{ namespace System{

class NB_EXPORT ArrayException : public nb::Core::Exception
{
public:
	ArrayException();
	ArrayException(const char *message);
	
};
typedef nbObjectPtrDerive<ArrayException, nb::Core::ExceptionPtr>	ArrayExceptionPtr;

//��������������޵�����Ԫ��ʱ�������쳣
class NB_EXPORT ArrayIndexOutOfRangeException : public ArrayException
{
public:
	ArrayIndexOutOfRangeException(int arraySize, int index);
	ArrayIndexOutOfRangeException(int arraySize, int index, const char *message);

private:
	int	m_ArraySize;
	int m_Index;
};
typedef nbObjectPtrDerive<ArrayIndexOutOfRangeException, ArrayExceptionPtr>	ArrayIndexOutOfRangeExceptionPtr;

//ά����������鴫�ݸ�����ʱ�������쳣
class NB_EXPORT ArrayRankException : public ArrayException
{
public:
	ArrayRankException();
	ArrayRankException(const char *message);
};
typedef nbObjectPtrDerive<ArrayRankException, ArrayExceptionPtr>	ArrayRankExceptionPtr;

}}
