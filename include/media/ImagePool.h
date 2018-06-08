#pragma once
#include <vector>
#include "system/SizeI.h"
#include "system/String.h"
#include "system/EnumFlags.h"
#include "system/CriticalSection.h"
#include "media/ImageSources.h"

namespace nb{ namespace Media {

class ImagePool_Internal;
class ImagePoolEvent;
class Bitmap;
class NB_EXPORT ImagePool
{
public:

	//�ļ�������
	enum FileType
	{
		FileType_Unknown	= 0x00000001,	//δ֪
		FileType_Jpeg		= 0x00000002,	//JPEG
		FileType_Bmp		= 0x00000004,	//BMP
		FileType_Png		= 0x00000008,	//PNG
		FileType_Reserve	= 0x80000000,	//Ԥ��
	};

	//���ط���
	enum LoadingDirection
	{
		Direction_Forward,					//��ǰ
		Direction_Backward,					//���
		Direction_Radiant,					//����
	};

	struct ImageItemProperty
	{
		nb::System::String	m_SourcePath;	//Դ·��
		bool				m_Loaded;		//�Ƿ��Ѿ�����
		bool				m_Error;		//�Ƿ��Ǵ���ͼƬ
		nb::System::SizeI	m_OriginalSize;	//ͼƬ��ԭ�ߴ�
		Bitmap				*m_Bitmap;		//ʵ��Bitmap
	};

	struct Cache
	{
		//����ģʽ
		enum CacheMode
		{
			CacheMode_Count_Limit,			//��������
			CacheMode_Bytes_Limit,			//�ֽ�����
		};
		Cache(CacheMode mode, int size) : m_Mode(mode), m_Size(size) {}

		CacheMode			m_Mode;
		int					m_Size;
	};

public:
	//���û���
	void SetCache(ImagePool::Cache cache);

	//��ȡ����
	ImagePool::Cache GetCache() const;

	//���ù��������������е��ļ����Ͳű�����
	void SetFilter(const nb::System::EnumFlags<nb::Media::ImagePool::FileType> &flags);

	//��ȡ������
	nb::System::EnumFlags<nb::Media::ImagePool::FileType> GetFilter() const;

	//����ĳ��ͼƬ��ʽ���ļ���СΪbytesLimit���������ж�Ϊ����ͼƬ
	void SetImageMemoryLimit(nb::Media::ImagePool::FileType type, int bytesLimit);
	//��������ͼƬ��ʽ���ļ���СbytesLimit���������ж�Ϊ����ͼƬ
	void SetImageMemoryLimitAllType(int bytesLimit);

	//���ü��ط���
	void SetLoadingDirection(ImagePool::LoadingDirection direction);
	
	//��ȡ���ط���
	ImagePool::LoadingDirection GetLoadingDirection() const;

	//����ͼƬ�ļ��б�Դ��ͼƬ���е�ԭ���ݽ�����գ����赱ǰ�����ڼ���ͼƬ����������ڸڴ�����
	//void SetSourceFiles(const std::vector<nb::System::String> &vtFilePaths);
	void SetSourceFiles(const ImageSources &filePaths);

	//׷��һ��Դ�ļ�
	void AppendSource(const nb::System::String &sSource);

	//����һ��Դ�ļ�
	//�쳣��index���
	void InsertSource(int index, const nb::System::String &sSource);

	//�Ƴ�һ��Դ�ļ�
	void RemoveSource(int index);

	//����һ��Source
	//�쳣��index���
	void UpdateSourceAt(int index, const nb::System::String &sSource);

	//��ȡͼƬ�ļ��б�
	void GetSourceFileList(ImageSources &ret) const;

	//��ȡ�±�Ϊindex��Դ
	//�쳣��index���
	nb::System::String GetSourceAt(int index) const;

	//��ȡԴͼƬ�ļ�����
	int GetSourceFileCount() const;

	//���ø��ڣ����ڵ�����������һ�μ��ص�ͼƬλ�ã������յ�ǰ�Ļ����С����Ϣ�����ͷ�ĳЩ�Ѽ���ͼƬ����
	//sentry����þͽ�����ԭ�򣬱��統sentry���ڿ��Ʒ�Χ�ڣ�ѡȡ����Ŀ����±���Ϊ����
	void SetSentry(int sentry);

	//��ȡ����λ��
	int GetSentry() const;

	//��ʼ����
	void StartLoading();

	//ֹͣ���أ�ֹͣ���ؽ�ɾ��ͼƬ���е�����ͼƬ
	//bClear���Ƿ��������
	void StopLoading(bool bClear);

	//�Ƿ��ڹ���
	bool IsWorking() const;

	//��ȡ�Ѽ���ͼƬ��������������ͼƬ��
	//int GetLoadedCount() const;

	//��ȡ�±�Ϊindex��ͼƬ���Բ��������˺���������GetImageItemPropertyUnlock����ʹ�ã�������ܲ�������
	//�쳣��index���
	bool GetImageItemPropertyAndLock(int index, ImageItemProperty &itemProperty);
	//��ȡͼƬ���Խ���������ע�⣡�������GetImageItemPropertyAndLock����false����Ӧ�õ���
	void GetImageItemPropertyUnlock(int index);

	//��ȡscale�ߴ�
	nb::System::SizeI GetScaleSize() const;

	//������Ϣ����
	void SetListener(ImagePoolEvent *p);
	ImagePoolEvent *GetListener() const;

public:
	//����һ��ͼƬ��
	//scale�ߴ�Ϊ	160x160
	//����CacheMode_Count_Limit�Ļ���ģʽ�������СΪ������
	//�ļ�������Ϊ	JPG|BMP|PNG
	//���ط���Ϊ	Direction_Radiant
	//����Դ�ǿյ�
	ImagePool();

	//����һ��ͼƬ��
	//scale�ߴ�Ϊ	scaleSize
	//����CacheMode_Count_Limit�Ļ���ģʽ�������СΪ������
	//�ļ�������Ϊ	JPG|BMP|PNG
	//���ط���Ϊ	Direction_Radiant
	//����Դ�ǿյ�
	ImagePool(const nb::System::SizeI &scaleSize);


	//����һ��ͼƬ��
	//scale�ߴ�Ϊ	160x160
	//����CacheMode_Count_Limit�Ļ���ģʽ�������СΪcacheSize
	//�ļ�������Ϊ	JPG|BMP|PNG
	//���ط���Ϊ	Direction_Radiant
	//����Դ�ǿյ�
	ImagePool(const nb::System::SizeI &scaleSize, ImagePool::Cache cache);

	//����һ��ͼƬ��
	//scale�ߴ�Ϊ	scaleSize
	//����mode����ģʽ�������СΪcacheSize
	//�ļ�������Ϊ	flags
	//���ط���Ϊ	direction
	//����Դ�ǿյ�
	ImagePool(const nb::System::SizeI &scaleSize, ImagePool::Cache cache, const nb::System::EnumFlags<nb::Media::ImagePool::FileType> &flags, ImagePool::LoadingDirection direction);

	~ImagePool();

private:
	ImagePool(const ImagePool &other);
	void operator = (const ImagePool &other);

	ImagePool_Internal		*m_pInternal;
};

//��Ϣ���̷߳�������ע�⣡��������
class NB_EXPORT ImagePoolEvent
{
public:
	//��ʼ����
	virtual void ImagePool_OnLoading_Start(nb::Media::ImagePool *sender)											{}

	//���У���ͼƬ�ؼ���������еĻ����ͻᴦ�ڿ���״̬
	virtual void ImagePool_OnLoading_Idled(nb::Media::ImagePool *sender)											{}

	//һ��ͼƬ������ɣ�millisecond������ʱ����bSccess���Ƿ���سɹ�
	virtual void ImagePool_OnImage_Loaded(nb::Media::ImagePool *sender, int index, int millisecond)	{}

	//һ��ͼƬ��������
	virtual void ImagePool_OnImage_Released(nb::Media::ImagePool *sender, int index)								{}

};

}}
