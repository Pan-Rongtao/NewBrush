/*******************************************************
**	RenderObject
**
**	��Ⱦ��
**	
**	��Ⱦ������������Ⱦ��������ݽṹ
**
**	һ����ԣ���Ⱦ�ﶼ���Լ���ģ�ͽṹ�����ʵ�
**		
**		
**		������
**	
********************************************************/
#pragma once
#include <string>
#include "../core/Any.h"
#include "../gles/Model.h"
#include "../gles/Material.h"

struct aiNode;
struct aiMesh;
struct aiScene;
namespace nb{ namespace gl{

class NB_API RenderObject
{
public:
	//����һ���յ�RenderObject�����Ŀ���Ⱦ״̬Ϊtrue
	RenderObject();

	//����һ���յ�RenderObject�����Ŀ���Ⱦ״̬ΪbRenderable
	RenderObject(bool bRenderable);

	//����һ��RenderObject������ģ��Ϊmodel������Ϊmateria������Ⱦ״̬Ϊtrue
	RenderObject(std::shared_ptr<Model> model, std::shared_ptr<Material> material);

	//����һ��RenderObject������ģ��Ϊmodel������Ϊmateria������Ⱦ״̬ΪbRenderable
	RenderObject(std::shared_ptr<Model> model, std::shared_ptr<Material> material, bool bRenderable);

public:	
	//���ļ��м���
	void loadFromFile(const std::string &path);

	//�����Ƿ����Ⱦ���⽫���������Ƿ����
	void setRenderable(bool bRenderable);

	//�Ƿ����Ⱦ
	bool renderable() const;

	//����ģ��
	void setModel(std::shared_ptr<Model> model);

	//��ȡģ��
	std::shared_ptr<Model> model();

	//���ò���
	void setMaterial(std::shared_ptr<Material> material);

	//��ȡ����
	std::shared_ptr<Material> material();

	//�洢����
	void set(const std::string &name, const Any &v);
	
	//���ƣ���д�˷����Թ����Լ�����Ⱦ��ʽ
	virtual void draw() const;

private:
	void loopNode(aiNode * node, const aiScene * scene);
	Mesh processMesh(aiMesh * mesh, const aiScene * scene);

	bool						m_renderable;
	std::shared_ptr<Model>		m_model;
	std::shared_ptr<Material>	m_material;
	std::map<std::string, Any>	m_uniforms;
};

}}
