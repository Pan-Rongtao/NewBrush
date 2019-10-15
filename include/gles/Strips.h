#pragma once
#include <vector>
#include "Model.h"

namespace nb{
namespace gl{

class NB_API Strips : public Model
{
public:
	//����һ���յĴ�״
	Strips();

	//����һ����״�������۵�Ϊbreaks
	Strips(const std::vector<glm::vec2> &breaks);

	//����һ����״�������۵�Ϊbreaks
	Strips(const std::vector<glm::vec2> &breaks, float thickness);

	//���
	void setThickness(float thickness);
	const float &thickness() const;

	//�����ʽ
	void setDashArray(const std::vector<float> &array);
	const std::vector<float> &dashArray() const;

	//ƫ����
	void setDashOffset(float offset);
	float dashOffset() const;

	//

private:
	void updateVertexs();
	float nextArrayElementInLoop(uint32_t nCurrentIndex);

	float					m_thickness;
	float					m_dashOffset;
	std::vector<float>		m_dashArray;
	std::vector<glm::vec2>	m_breaks;
};

}}