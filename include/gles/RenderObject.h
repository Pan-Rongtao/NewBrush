/*******************************************************
**	RenderObject
**
**	��Ⱦ��
**	
**	��Ⱦ������������Ⱦ��������ݽṹ
**
**	һ����ԣ���Ⱦ�ﶼ���Լ���ģ�ͽṹ�����ʺ�program��
**		
**		
**		������
**	
********************************************************/
#pragma once
#include "system/Global.h"
#include "gles/Model.h"
#include "gles/Material.h"

namespace nb{ namespace gl{ namespace Gles{

class Model;
class Material;
class Program;
class NB_EXPORT RenderObject : public ModelEventListener, public MaterialEventListener
{
public:
	//��Ⱦģʽ
	enum RenderMode
	{
		RenderMode_Mapping	= 0,		//��ͼ
		RenderMode_Color	= 1,		//��ɫ
	};

public:	
	//�����Ƿ����Ⱦ���⽫���������Ƿ����
	void SetRenderable(bool bRenderable);

	//�Ƿ����Ⱦ
	bool IsRenderable() const;

	//����ģ��
	void SetModel(Model *model);

	//��ȡģ��
	Model *GetModel() const;

	//���ò���
	void SetMaterial(Material *material);

	//��ȡ����
	Material *GetMaterial() const;

	//������Ⱦģʽ
	void SetRenderMode(RenderMode mode);

	//��ȡ��Ⱦģʽ
	RenderMode GetRenderMode() const;

	//�Ƿ���Խ���batching
	bool CanBatchWith(const RenderObject *renderObject) const;

public:
	//����һ���յ�RenderObject�����Ŀ���Ⱦ״̬Ϊtrue
	RenderObject();

	//����һ���յ�RenderObject�����Ŀ���Ⱦ״̬ΪbRenderable
	RenderObject(bool bRenderable);

	//����һ��RenderObject������ģ��Ϊmodel������Ϊmateria������Ⱦ״̬Ϊtrue
	RenderObject(Model *model, Material *material);

	//����һ��RenderObject������ģ��Ϊmodel������Ϊmateria������Ⱦ״̬ΪbRenderable
	RenderObject(Model *model, Material *material, bool bRenderable);

private:
	virtual void On_ModelData_Changed(Model::VertexAttributesType type);
	virtual void On_Texture_Changed();

	bool					m_bRenderable;
	Model					*m_Model;
	Material				*m_Material;
	RenderMode				m_RenderMode;
};

}}}
