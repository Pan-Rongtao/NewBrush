//���ӷ�����
//���ӷ�������������ĸ������ԣ����������Ӹ����Եı仯����
//���ӷ����������м�����
//1������ֵ����ʾ���������ÿ�λؼ������Զ���ֵ�����ǹ̶���ֵ
//2���仯�ȣ���ʾһ���仯���䷶Χ��һ���Ǹ����ͣ��仯��ȡֵΪ[-var, var]
#pragma once
#include <vector>
#include <set>
#include <array>
#include "../core/Def.h"
#include "AnimationValue.h"
#include "glm/glm.hpp"

namespace nb { namespace gl {
	
enum class ParticleFacingTypeE
{
	Billboard2D,
	Billboard3D,
};

enum class ParticleBlendModeE
{
	AlphaBlend,
	Additive,
	Multiplay,
	Mutiplay2x,
	Subtract,
};

struct ParticleEmitterDepthSettings
{
	bool	usesDepthSoftening{ false };
	float	depthFadeDistance{ 0.0f };
	float	depthFadePower{ 0.0f };
};

struct ParticleEmitterTextureAnimation
{
	bool				isAnimated					{ false };
	bool				randomizeInitialFrame		{ false };
	uint32_t			frameCountX					{ 0 };
	uint32_t			frameCountY					{ 0 };
	float				framesPersecond				{ 0.0f };
	float				frameTimeVar				{ 0.0f };
	std::array<bool, 3>	isAnimatedForTextureIndex	{ false };
};

struct ParticleEmitterWideUpdates
{
	float						rotationalVelocity{ 0.0f };
	std::array<glm::vec2, 3>	uvScrollDelta;
	glm::vec3					particleUp;
	glm::vec3					particleRight;
	glm::vec3					particleForward;
};

class Particle;
class ParticleEmitter
{
public:
	//����һ�����ӷ����������������ڴ��poolId��֧�ֵ����������ΪmaxParticleCount
	ParticleEmitter();

	//
	void init(uint32_t poolId, uint32_t maxParticleCount);

	//��ʼ/ֹͣ
	void start();
	void stop();

	//�Ƿ��Ѿ����
	bool isComplete() const;

	//��Ⱦ
	void render();

	//�������ӵĳ�ʼ������
	void update(float deltaTime);

private:

	uint32_t						m_poolId;						//�������ڴ��ID
	bool							m_shouldEmit;					//�Ƿ���Ҫ�����־

	float							m_emitterLifeTime;				//����������
	float							m_emitterCurrentLife;			//����������ʱ��
	uint32_t						m_maxParticleCount;				//���������
	uint32_t						m_minParticleCount;				//��С������
	float							m_floatingParticle;				//��������С���ۻ����֣����ڵ���1.0���Ϊһ�����������ӣ�Ȼ��������Ϊ0.0��������ڷ����������������ӵ�caseЧ����������
	std::vector<Particle *>			m_particles;					//�ѷ��������
	AnimationValue<float>			m_emiteCountPerSecond;			//ÿ�뷢�����Ӹ��������Զ���ֵ����ÿ�η�������������Ǹ�����ֵ

	float							m_particleLifeTime;				//������������
	float							m_particleLifeTimeVar;			//��������������
	glm::vec3						m_spawnArea;					//����λ��
	AnimationValue<glm::vec4>		m_colorMultiplier;				//��ɫ����
	glm::vec4						m_colorVar;						//��ɫ����ֵ
	AnimationValue<float>			m_rotationalVelocity;			//��ת���ʶ���ֵ
	float							m_rotationVar;					//��ת�仯��
	float							m_rotationRateVar;				//��ת�ٶȱ仯��
	AnimationValue<glm::vec3>		m_scale;						//���Ŷ���ֵ
	float							m_scaleVar;						//���ű仯��
	std::array<AnimationValue<glm::vec2>, 3>	m_uvScroll;			//�������궯��ֵ��֧����������
	std::array<glm::vec2, 3> 		m_uvScrollOffsets;				//��������ƫ�ƣ�֧����������
	std::array<glm::vec2, 3>		m_uvScroolVar;					//��������ƫ�ƶ���ֵ��֧����������
	AnimationValue<float>			m_materialIntensity;			//����ǿ�ȶ���ֵ
	float							m_materialIntensityVar;			//����ǿ�ȱ仯��
	ParticleEmitterTextureAnimation	m_texutreAnimation;				//������

	AnimationValue<float>			m_velocity;						//���ʶ���ֵ
	glm::vec3						m_velocityVar;					//���ʱ仯��
	glm::vec3						m_gravity;						//����

	uint32_t						m_startVert;
	uint32_t						m_endVert;
};

}}