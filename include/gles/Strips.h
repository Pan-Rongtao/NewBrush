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

	//����һ����״�������۵�Ϊbreaks�����Ϊthickness
	Strips(const std::vector<glm::vec2> &breaks, float thickness);

	//����һ����״�������۵�Ϊbreaks�����Ϊthickness�������ʽΪdashArray��ƫ����ΪdashOffset
	Strips(const std::vector<glm::vec2> &breaks, float thickness, const std::vector<float> &dashArray, float dashOffset);

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
	//�߶��� y = kx + b
	class LineSegment
	{
	public:
		LineSegment(const glm::vec2 &p0, const glm::vec2 &p1);

		//����p0, p1
		const glm::vec2 &p0() const;
		const glm::vec2 &p1() const;

		//ˮƽ�ʹ�ֱ����ľ���ֵ����Ϊ����
		float xDiff() const;
		float yDiff() const;

		//�߶γ���
		float length() const;

		float evalX(float y) const;

		float evalY(float x) const;
		//ִ�����߼���
		void dashing(float offset, const std::vector<float> &array, float thickness, std::vector<glm::vec2> &points);

	private:
		glm::vec2	m_p0;
		glm::vec2	m_p1;
		float		m_k;
		float		m_b;
	};

	void updateVertexs();
	float nextArrayElementInLoop(uint32_t nCurrentIndex);
	std::vector<uint16_t> getIndices(int vertexCount) const;

	float					m_thickness;
	float					m_dashOffset;
	std::vector<float>		m_dashArray;
	std::vector<glm::vec2>	m_breaks;
};

}}