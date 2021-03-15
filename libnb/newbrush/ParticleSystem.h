#pragma once
#include <array>
#include <vector>
#include <thread>
#include "glm/glm.hpp"
#include "newbrush/Core.h"

namespace nb
{
	
class Particle;
class ParticleSystem;
class ParticleEmitter;
class ParticleMemoryPool;

//�����ܹ���
//������������ϵͳ�����ӷ����������ӵĳ�ʼ��
//���ӹ�����������ȫ�ַ�Χ�ڴ����������顣 
//����������ϵͳ��������У������Ӷ��㻺��������������Ҫ��Ⱦ�͸���ѭ���� 
class ParticleManager
{
public:
	//��ʼ��
	static void init();

	//��Ⱦ����
	static void update(float deltaTime, const glm::vec3 &cameraDirection);
};

//�����ڴ�ع�����
//�������Ŷ��ParticleMemoryPool
//����Ϊ�µ�����ϵͳѡ����ѵ��ڴ��
class ParticleMemoryPoolManager
{
public:
	static void init(uint32_t particleCount, uint32_t emitterCount, uint32_t particleSystemCount, uint32_t poolCount);
	static ParticleMemoryPool *getMemoryPool(uint32_t index);
	static size_t getBestPoolIdForNewParticles();

private:
	static std::vector<ParticleMemoryPool *>	m_memoryPools;
};

//�����ڴ��
//�����������Ӻ��ͷŵ���
//��ParticleMemoryPoolManager
class ParticleMemoryPool
{
public:
	//����һ�������ڴ�أ�����ӵ������ϵͳparticleSystemCount����������emitterCount����������particleCount
	ParticleMemoryPool(uint32_t particleCount, uint32_t emitterCount, uint32_t particleSystemCount);

	//�����µ�����
	Particle *applyParticle();

	//�ͷ�����
	void freeParticle(Particle *particle);

	//��ȡ���������
	size_t getActiveParticleCount() const;

private:
	Particle		*m_particles;				//����ָ��
	uint32_t 		m_particleCount;			//���Ӹ���
	uint32_t		m_curParticleIndex;			//�����±�
	ParticleEmitter	*m_emitters;				//���ӷ�����ָ��
	uint32_t 		m_emitterCount;				//���ӷ���������
	uint32_t		m_curEmitterIndex;			//���ӷ������±�
	ParticleSystem *m_particleSystems;			//����ϵͳָ��
	uint32_t 		m_particleSystemsCount;		//����ϵͳ����
	uint32_t		m_curParticleSystemIndex;	//����ϵͳ�±�

	std::vector<Particle *>	m_reusableParticles;//���ظ�ʹ����������
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

//////////
class NB_API ParticleVertexBuffer
{
public:
	ParticleVertexBuffer(uint32_t particleCount, uint32_t poolCount);


private:
	std::vector<float>	*m_ver;
	std::vector<int>	m_indices;
};

class ParticleUpdateJob
{
public:

};

}
