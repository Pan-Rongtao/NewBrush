#pragma once
#include <vector>
#include <set>
#include <array>
#include "newbrush/core/Def.h"
#include "newbrush/gles/AnimationValue.h"
#include "glm/glm.hpp"

namespace nb{

class Particle;
class ParticleSystem;
class ParticleEmitter;
class ParticleMemoryPool;

//�����ܹ���
class ParticleManager
{
public:
	static void init(uint32_t particleSystemCount, uint32_t emitterCount, uint32_t particleCount, uint32_t poolCount);

	static void update();
};

//�����ڴ�ع���
class ParticleMemoryPoolManager
{
public:
	static void init(uint32_t particleSystemCount, uint32_t emitterCount, uint32_t particleCount, uint32_t poolCount);
	static ParticleMemoryPool *getMemoryPool(uint32_t index);
	static size_t getBestPoolIdForNewParticles();

private:
	static std::vector<ParticleMemoryPool *>	m_memoryPools;
};

//�����ڴ��
class ParticleMemoryPool
{
public:
	ParticleMemoryPool(uint32_t particleSystemCount, uint32_t emitterCount, uint32_t particleCount);
	
	Particle *applyParticle();
	void freeParticle(Particle *particle);
	size_t getActiveParticleCount() const;

private:
	ParticleSystem	*m_particleSystems;
	ParticleEmitter	*m_emitters;
	Particle		*m_particles;
	uint32_t 		m_particleSystemsCount;
	uint32_t 		m_emitterCount;
	uint32_t 		m_particleCount;
	uint32_t		m_curParticleSystemIndex;
	uint32_t		m_curEmitterIndex;
	uint32_t		m_curParticleIndex;
	std::vector<Particle *>	m_reusableParticles;
};

//����ϵͳ��������Ч���Ķ��������
class ParticleSystem
{
public:

};

//����
class Particle
{
public:
	glm::vec3					position;			//λ��
	glm::vec4					colorMul;			//?����color����
	glm::vec4					colorVar;			//����
	std::array<glm::vec2, 3>	texOffsets;			//�������֧꣬����������
	float						rotation;			//��ת��Ϊɶ��float����vec3����
	float						ratationRate;		//��ת�ٶ�
	glm::vec3					initialScale;		//��ʼ����
	glm::vec3					scale;				//����
	glm::vec3					velocity;			//�ٶȣ�x,y,z����ά�ȣ�
	glm::vec3					acceleration;		//���ٶ�
	float						lifeTime;			//��������
	float						currentLife;		//��ǰ����
	float						intensity;			//ǿ��
	glm::vec2					textureFrame;		//??
	float						textureFrameTime;	//??
	float						textureFrameTimeVar;//??
};

}