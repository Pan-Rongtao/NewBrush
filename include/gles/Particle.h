#pragma once

namespace nb{ namespace gl{

//����ϵͳ
class ParticleSystem
{
public:
};

//����
class Particle
{

};

//���ӷ�����
class ParticleEmitter
{
public:
	int particleCount;		//���������
	int emiteRate;			//ÿ�η������Ӹ���
	int life;				//������������
	float emiteSpeed;		//�����ʼ�ٶ�
};

//�����˶�Ч��
class ParticleAffector
{

};

}}