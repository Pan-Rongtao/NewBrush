/******************************************************************************

* Copyright (c) 2017���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-04

* ��Ҫ����:  ��IO��ص��쳣

* �޸ļ�¼:

*****************************************************************************/
#include <string>
#include "core/Exception.h"

namespace nb{ namespace System{

class NB_EXPORT IOException : public nb::Core::Exception
{
public:
	IOException();
	IOException(const char *ioName);
	IOException(const char *ioName, const char *message);

	const char *GetName();

private:
	std::string		m_Name;
};
typedef nbObjectPtrDerive<IOException, nb::Core::ExceptionPtr>	IOExceptionPtr;

//δ�ҵ�Ŀ¼�쳣
class NB_EXPORT FileNotFoundException : public IOException
{
public:
	FileNotFoundException();
	FileNotFoundException(const char *ioName);
	FileNotFoundException(const char *ioName, const char *message);
};
typedef nbObjectPtrDerive<FileNotFoundException, IOExceptionPtr>	FileNotFoundExceptionPtr;

//δ�ҵ��ļ��쳣
class NB_EXPORT DirectoryNotFoundException : public IOException
{
public:
	DirectoryNotFoundException();
	DirectoryNotFoundException(const char *ioName);
	DirectoryNotFoundException(const char *ioName, const char *message);
};
typedef nbObjectPtrDerive<DirectoryNotFoundException, IOExceptionPtr>	DirectoryNotFoundExceptionPtr;

//�ļ����ѵ���ĩβ�쳣
class NB_EXPORT EndOfStreamException : public IOException
{
public:
	EndOfStreamException();
	EndOfStreamException(const char *ioName);
	EndOfStreamException(const char *ioName, const char *message);
};
typedef nbObjectPtrDerive<EndOfStreamException, IOExceptionPtr>	EndOfStreamExceptionPtr;

//�ļ�����ʧ���쳣
class NB_EXPORT FileLoadFailedException : public IOException
{
public:
	FileLoadFailedException();
	FileLoadFailedException(const char *ioName);
	FileLoadFailedException(const char *ioName, const char *message);
};
typedef nbObjectPtrDerive<FileLoadFailedException, IOExceptionPtr>	FileLoadFailedExceptionPtr;

//�ļ���̫���쳣
class NB_EXPORT PathTooLongException : public IOException
{
public:
	PathTooLongException();
	PathTooLongException(const char *ioName);
	PathTooLongException(const char *ioName, const char *message);

};
typedef nbObjectPtrDerive<PathTooLongException, IOExceptionPtr>	PathTooLongExceptionPtr;


}}
