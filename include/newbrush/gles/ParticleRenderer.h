#pragma once
#include "newbrush/gles/RenderObject.h"

namespace nb {

class NB_API ParticleVertexBuffer : public RenderObject
{
public:
	ParticleVertexBuffer(uint32_t maxParticleCount, uint32_t poolcount);


private:
	std::vector<float>	*m_ver;
	std::vector<uint16_t>	m_indices;
};


}