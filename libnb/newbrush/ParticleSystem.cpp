#include "newbrush/ParticleSystem.h"
#include "newbrush/ParticleEmitter.h"

using namespace nb;

/****************************************************
*	�������ܹ������������š������ڴ�ع�����'
*	���ĳ�ʼ������ʼ���������ڴ�ع�����'
*	
*****************************************************/
#define MAX_PARTICLES 50000
#define MAX_PARTICLE_EMITTERS 1000
#define MAX_PARTICLE_SYSTEMS 1000
#define NUM_MEMORY_POOLS 8
void ParticleManager::init()
{
	ParticleMemoryPoolManager::init(MAX_PARTICLES, MAX_PARTICLE_EMITTERS, MAX_PARTICLE_SYSTEMS, NUM_MEMORY_POOLS);
}

void ParticleManager::update(float deltaTime, const glm::vec3 & cameraDirection)
{

}

////////////////////////////
std::vector<ParticleMemoryPool *> ParticleMemoryPoolManager::m_memoryPools;
void ParticleMemoryPoolManager::init(uint32_t particleCount, uint32_t emitterCount, uint32_t particleSystemCount, uint32_t poolCount)
{
	m_memoryPools.resize(poolCount);
	for (int i = 0; i != poolCount; ++i)
	{
		m_memoryPools[i] = new ParticleMemoryPool(particleCount / poolCount, emitterCount / poolCount, particleSystemCount / poolCount);
	}
}

ParticleMemoryPool * ParticleMemoryPoolManager::getMemoryPool(uint32_t index)
{
	nbThrowExceptionIf(index >= m_memoryPools.size(), std::out_of_range, "index[%d] is out of range[0, %zu)", index, m_memoryPools.size());

	return m_memoryPools[index];
}

size_t ParticleMemoryPoolManager::getBestPoolIdForNewParticles()
{
	auto iter = std::min_element(m_memoryPools.begin(), m_memoryPools.end(), [](ParticleMemoryPool *a, ParticleMemoryPool *b) 
	{
		return a->getActiveParticleCount() < b->getActiveParticleCount();
	});
	return iter - m_memoryPools.begin();
}

ParticleMemoryPool::ParticleMemoryPool(uint32_t particleCount, uint32_t emitterCount, uint32_t particleSystemCount)
	: m_particleCount(particleCount)
	, m_emitterCount(emitterCount)
	, m_particleSystemsCount(particleSystemCount)
	, m_curParticleIndex(0)
	, m_curEmitterIndex(0)
	, m_curParticleSystemIndex(0)
{
	m_emitters = new ParticleEmitter[emitterCount];
	for (int i = 0; i != emitterCount; ++i)
		m_emitters[i].init(0, particleCount);
	m_particles = new Particle[particleCount];
	m_particleSystems = new ParticleSystem[particleSystemCount];
}

/****************************************************
*	�����ǰ�����±�С����������Ĵ�С����ֱ�ӷ��ظ��±������
*	����������ظ�ʹ���������鲻Ϊ�գ�ȡ���������һ������
*	���򣬷��ؿ�
*****************************************************/
Particle * ParticleMemoryPool::applyParticle()
{
	Particle *p = nullptr;
	if (m_curParticleIndex < m_particleCount)
	{
		p = &m_particles[m_curParticleIndex];
		m_curParticleIndex++;
	}
	else if (!m_reusableParticles.empty())
	{
		p = m_reusableParticles[m_reusableParticles.size() - 1];
		m_reusableParticles.pop_back();
	}
	return p;
}

/****************************************************
*	�ͷ�����
*	�ͷź󣬸�����������������
*	�ͷź󣬸����Ӵ��롮���ظ�ʹ���������顯�й��ظ�ʹ��
*****************************************************/
void ParticleMemoryPool::freeParticle(Particle * particle)
{
	//partial->reset();
	m_reusableParticles.push_back(particle);
}

/****************************************************
*	��ȡ�Ѽ������������
*	�����ظ�ʹ���������顯Ҳ��ʾ�ͷ��˵����ӣ�
*	ʹ�õ�ǰ�����±�-�����ظ�ʹ���������顯�ĸ�����Ϊ��ǰ���ڻ������
*****************************************************/
size_t ParticleMemoryPool::getActiveParticleCount() const
{
	return m_curParticleIndex - m_reusableParticles.size();
}

ParticleVertexBuffer::ParticleVertexBuffer(uint32_t maxParticleCount, uint32_t poolcount)
{
}
