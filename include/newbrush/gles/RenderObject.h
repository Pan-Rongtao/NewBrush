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
#include "newbrush/gles/Model.h"
#include "newbrush/gles/Material.h"
#include "newbrush/gles/Camera.h"
#include "newbrush/gles/Projection.h"
#include "Poco/Dynamic/Var.h"

struct aiNode;
struct aiMesh;
struct aiScene;
namespace nb{
	
using Poco::Dynamic::Var;
class NB_API RenderObject
{
public:
	//����һ���յ�RenderObject�����Ŀ���Ⱦ״̬Ϊtrue
	RenderObject();

	//����һ���յ�RenderObject�����Ŀ���Ⱦ״̬ΪbRenderable
	RenderObject(std::shared_ptr<Model> model);

	//����һ��RenderObject������ģ��Ϊmodel������Ϊprogram������Ⱦ״̬Ϊtrue
	RenderObject(std::shared_ptr<Model> model, std::shared_ptr<Program> program);

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

	//����program
	void setProgram(std::shared_ptr<Program> program);

	//��ȡprogram
	std::shared_ptr<Program> program();

	//�洢uniform�������Ա��´�ˢ��ʹ��
	void storeUniform(const std::string &name, const Var &v);
	
	//���ƣ���д�˷����Թ����Լ�����Ⱦ��ʽ
	virtual void draw(const Camera &camera, const Projection &projection) const;

private:
	void loopNode(aiNode * node, const aiScene * scene);
	Mesh processMesh(aiMesh * mesh, const aiScene * scene);

	std::shared_ptr<Model>		m_model;
	std::shared_ptr<Program>	m_program;
	std::map<std::string, Var>	m_uniforms;
	bool						m_renderable;
};

}
