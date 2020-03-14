#include "newbrush/gles/RenderObject.h"
#include <GLES2/gl2.h>
#include "newbrush/core/Log.h"
#ifdef WIN32
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#endif

using namespace nb;

RenderObject::RenderObject()
	: RenderObject(nullptr, nullptr)
{
}

RenderObject::RenderObject(std::shared_ptr<Model> model)
	: RenderObject(model, nullptr)
{
}

RenderObject::RenderObject(std::shared_ptr<Model> model, std::shared_ptr<Program> program)
	: m_model(model)
	, m_program(program)
	, m_renderable(true)
{
}

void RenderObject::loadFromFile(const std::string & path)
{
#ifdef WIN32
	m_model = std::make_shared<Model>();
	Assimp::Importer importer;
	//const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		Log::error("load [%s] fail:%s", path.data(), importer.GetErrorString());
		return;
	}

	loopNode(scene->mRootNode, scene);
#endif
}

void RenderObject::setRenderable(bool bRenderable)
{
	m_renderable = bRenderable;
}

bool RenderObject::renderable() const
{
	return m_renderable;
}

void RenderObject::setModel(std::shared_ptr<Model> model)
{
	m_model = model;
}

std::shared_ptr<Model> RenderObject::model()
{
	return m_model;
}

void RenderObject::setProgram(std::shared_ptr<Program> program)
{
	m_program = program;
}

std::shared_ptr<Program> RenderObject::program()
{
	return m_program;
}

void RenderObject::storeUniform(const std::string & name, const Var & v)
{
	m_uniforms[name] = v;
}

void RenderObject::draw(const Camera &camera, const Projection &projection) const
{
	if (!m_renderable || !m_model || m_model->meshes.empty() || !m_program)
		return;

	auto &program = m_program;
	program->use();
	m_model->preprocess();
	//计算后的mvp，以及分开的m/v/p
	{
		auto const &m = m_model->matrix;
		auto const &v = camera.matrix;
		auto const &p = projection.matrix;
		auto mvp = p * v * m;
		program->uniform(program->getUniformLocation(Program::nbMvpStr), mvp);
		program->uniform(program->getUniformLocation(Program::nbMStr), m);
		program->uniform(program->getUniformLocation(Program::nbVStr), v);
		program->uniform(program->getUniformLocation(Program::nbPStr), p);
	}
	//storage中的uniform
	for (auto const &iter : m_uniforms)
	{
		auto location = program->getUniformLocation(iter.first.data());
		auto const &v = iter.second;
		if (v.type() == typeid(bool))							program->uniform(location, v.extract<bool>());
		else if (v.type() == typeid(int))						program->uniform(location, v.extract<int>());
		else if (v.type() == typeid(float))						program->uniform(location, v.extract<float>());
		else if (v.type() == typeid(double))					program->uniform(location, (float)v.extract<double>());
		else if (v.type() == typeid(glm::vec2))					program->uniform(location, v.extract<glm::vec2>());
		else if (v.type() == typeid(glm::vec3))					program->uniform(location, v.extract<glm::vec3>());
		else if (v.type() == typeid(glm::vec4))					program->uniform(location, v.extract<glm::vec4>());
		else if (v.type() == typeid(glm::mat2x2))				program->uniform(location, v.extract<glm::mat2x2>());
		else if (v.type() == typeid(glm::mat3x3))				program->uniform(location, v.extract<glm::mat3x3>());
		else if (v.type() == typeid(glm::mat4x4))				program->uniform(location, v.extract<glm::mat4x4>());
		else if (v.type() == typeid(glm::ivec2))				program->uniform(location, v.extract<glm::ivec2>());
		else if (v.type() == typeid(glm::ivec3))				program->uniform(location, v.extract<glm::ivec3>());
		else if (v.type() == typeid(glm::ivec4))				program->uniform(location, v.extract<glm::ivec4>());
		else if (v.type() == typeid(std::vector<int>))			program->uniform(location, v.extract<std::vector<int>>());
		else if (v.type() == typeid(std::vector<float>))		program->uniform(location, v.extract<std::vector<float>>());
		else if (v.type() == typeid(std::vector<glm::vec2>))	program->uniform(location, v.extract<std::vector<glm::vec2>>());
		else if (v.type() == typeid(std::vector<glm::vec3>))	program->uniform(location, v.extract<std::vector<glm::vec3>>());
		else if (v.type() == typeid(std::vector<glm::vec4>))	program->uniform(location, v.extract<std::vector<glm::vec4>>());
		else if (v.type() == typeid(std::vector<glm::mat2x2>))	program->uniform(location, v.extract<std::vector<glm::mat2x2>>());
		else if (v.type() == typeid(std::vector<glm::mat3x3>))	program->uniform(location, v.extract<std::vector<glm::mat3x3>>());
		else if (v.type() == typeid(std::vector<glm::mat4x4>))	program->uniform(location, v.extract<std::vector<glm::mat4x4>>());
		else if (v.type() == typeid(std::vector<glm::ivec2>))	program->uniform(location, v.extract<std::vector<glm::ivec2>>());
		else if (v.type() == typeid(std::vector<glm::ivec3>))	program->uniform(location, v.extract<std::vector<glm::ivec3>>());
		else if (v.type() == typeid(std::vector<glm::ivec4>))	program->uniform(location, v.extract<std::vector<glm::ivec4>>());
		else													Log::warn("%s is not a supported type for glsl.", v.type().name());
		
	}

	//依次绘制meshs
	for (auto const &mesh : m_model->meshes)
	{
		program->vertexAttributePointer(Program::nbPositionLocation, Vertex::positionDimension, Vertex::stride, mesh.positionData());
		program->vertexAttributePointer(Program::nbColorLocation, Vertex::colorDimension, Vertex::stride, mesh.colorData());
		program->vertexAttributePointer(Program::nbNormalLocation, Vertex::normalDimension, Vertex::stride, mesh.normalData());
		for (int i = 0; i < mesh.material.textures().size(); i++)
		{
			mesh.material.textures()[i]->bind();
			//texure->bind();
			program->vertexAttributePointer(Program::nbTexCoordLocaltion, Vertex::texCoordDimension, Vertex::stride, mesh.textureCoordinateData());
			glActiveTexture(GL_TEXTURE0 + i);
		}
		glDrawElements(m_model->mode, (int)mesh.indices.size(), GL_UNSIGNED_SHORT, mesh.indices.data());

	}

	program->disuse();
}

void RenderObject::loopNode(aiNode * node, const aiScene * scene)
{
#ifdef WIN32
	for (int i = 0; i != node->mNumMeshes; ++i)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		m_model->meshes.push_back(processMesh(mesh, scene));
	}
	for (int i = 0; i != node->mNumChildren; ++i)
		loopNode(node->mChildren[i], scene);
#endif
}

Mesh RenderObject::processMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<Vertex> vertexs;
	std::vector<uint16_t> indices;
	Material ma;
#ifdef WIN32
	for (int i = 0; i != mesh->mNumVertices; ++i)
	{
		Vertex ver;
		if (mesh->HasPositions())		ver.position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
		if (mesh->mColors[0])			ver.color = { mesh->mColors[0][i].r, mesh->mColors[0][i].g, mesh->mColors[0][i].b, mesh->mColors[0][i].a };
		if (mesh->mTextureCoords[0])	ver.texCoord = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
		if (mesh->HasNormals())			ver.normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
		vertexs.push_back(ver);
	}

	for (int i = 0; i != mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j != face.mNumIndices; ++j)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	auto loadMaterialTextures = [](aiMaterial *mat, aiTextureType type, uint8_t samplerUnit)->std::vector<std::shared_ptr<Texture2D>> {
		std::vector<std::shared_ptr<Texture2D>> textures;
		int ii = mat->GetTextureCount(type);
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
			aiString str;
			mat->GetTexture(type, i, &str);

			std::string filename = std::string(str.C_Str());
			filename = "D:/share/myProject/modelLoading/resources/objects/models/car_texture/" + filename.substr(filename.find_last_of('\\') + 1);

			auto texture2DPtr = std::make_shared<Texture2D>(Bitmap(filename));
			texture2DPtr->setWrapping(TextureWrapping{ TextureWrapping::WrappingModeE::Repeat });
			texture2DPtr->setFilter(TextureFilter{ TextureFilter::FilterE::Bilinear , TextureFilter::FilterE::Trilinear });
			texture2DPtr->setSamplerUnit(samplerUnit);

			textures.push_back(texture2DPtr);
		}
		return textures;
	};

	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		// 1. diffuse maps
		std::vector<std::shared_ptr<Texture2D>> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, 0);
		ma.textures().insert(ma.textures().end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. specular maps
		std::vector<std::shared_ptr<Texture2D>> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, 1);
		ma.textures().insert(ma.textures().end(), specularMaps.begin(), specularMaps.end());
		// 3. normal maps
		std::vector<std::shared_ptr<Texture2D>> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, 2);
		ma.textures().insert(ma.textures().end(), normalMaps.begin(), normalMaps.end());
		// 4. height maps
		std::vector<std::shared_ptr<Texture2D>> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, 3);
		ma.textures().insert(ma.textures().end(), heightMaps.begin(), heightMaps.end());
	}
	
#endif
	return Mesh(vertexs, indices, ma);
}
