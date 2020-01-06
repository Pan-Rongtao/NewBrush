#include "gui/Rectangle.h"
#include <math.h>
#include <glm/gtc/matrix_transform.hpp>
#include "gles/Viewport2D.h"
#include "gles/Strips.h"

using namespace nb;
using namespace nb::gui;

Rectangle::Rectangle()
	: RadiusX([&](float v) {set(RadiusXProperty(), v); }, [&]()->float {return get<float>(RadiusXProperty()); })
	, RadiusY([&](float v) {set(RadiusYProperty(), v); }, [&]()->float {return get<float>(RadiusYProperty()); })
{
}

DependencyProperty Rectangle::RadiusXProperty()
{
	static auto dp = DependencyProperty::registerDependency<Rectangle, float>("RadiusX", 0.0);
	return dp;
}

DependencyProperty Rectangle::RadiusYProperty()
{
	static auto dp = DependencyProperty::registerDependency<Rectangle, float>("RadiusY", 0.0);
	return dp;
}

void Rectangle::onRender(Viewport2D & drawContext)
{
	auto offset = worldOffset();
	Rect rc(offset.x(), offset.y(), ActualSize());
	auto c = rc.center();
	if (m_fillObject)
	{
		Rect fillRc{rc};
		if (Stroke())
			fillRc.reset(rc.left() - StrokeThickness() * 0.5f, rc.top() - StrokeThickness() * 0.5f, rc.width() - StrokeThickness(), rc.height() - StrokeThickness());
		updateFillObject(fillRc.width(), fillRc.height(), RadiusX(), RadiusY());
		drawContext.queue(m_fillObject);
		m_fillObject->model()->matrix = glm::translate(glm::mat4(1.0), glm::vec3(c.x(), c.y(), 0.0f));
	}
	if (m_strokeObject)
	{
		updateStrokeObject(rc);
		drawContext.queue(m_strokeObject);
	//	m_strokeObject->model()->matrix = glm::translate(glm::mat4(1.0), glm::vec3(c.x(), c.y(), 0.0f));
	}
}

void Rectangle::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
	if (args.property == FillProperty())
	{
		if (!Fill())				m_fillObject.reset();
		else if (!m_fillObject)		m_fillObject = std::make_shared<RenderObject>(std::make_shared<Model>(std::vector<Mesh>{ Mesh() }));
	}
	else if (args.property == StrokeProperty())
	{
		if (!Stroke())				m_strokeObject.reset();
		else if (!m_strokeObject)	m_strokeObject = std::make_shared<RenderObject>(std::make_shared<Strips>());
	}
}

Size Rectangle::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size Rectangle::arrangeOverride(const Size & finalSize)
{
	return finalSize;
}

void Rectangle::updateFillObject(float width, float height, float radiusX, float radiusY)
{
	if (!Fill())
		return;

	//����model����
	//�ĸ��ǵ�λ��
	auto &vertexs = m_fillObject->model()->meshes[0].vertexs;
	auto &indices = m_fillObject->model()->meshes[0].indices;
	bool radius = (width != 0.0f && height != 0.0f) && (radiusX != 0.0f && radiusY != 0.0f);			//�Ƿ���Ҫ����
	constexpr auto connerVertexSize = 20u;							//ÿ�����εĶ�����
	constexpr auto connerIndicesSize = 3 * (connerVertexSize - 2);	//ÿ�����εĶ������д�С
	constexpr auto radianStep = M_PI_2 / (connerVertexSize - 2);	//���ε�λ����
	vertexs.resize(radius ? connerVertexSize * 4 : 4);				//���ж�����
	indices.resize(radius ? connerIndicesSize * 4 + 12 : 6);		//���ж������д�С=�ĸ����ȶ������� + ʮ���������ζ�������
	if (radius)
	{
		//�޶�Բ���ھ��ΰ볤/����
		auto _radiusX = std::fabs(radiusX) <= width * 0.5f ? std::fabs(radiusX) : width * 0.5f;
		auto _radiusY = std::fabs(radiusY) <= height * 0.5f ? std::fabs(radiusY) : height * 0.5f;

		auto fillConner = [&vertexs, &indices, &connerVertexSize, &connerIndicesSize, _radiusX, _radiusY, &radianStep, width, height](const glm::vec3 &center, float radianSpan, int cornnerIndex) 
		{
			auto beg = cornnerIndex * connerVertexSize;
			auto centerTexCoord = glm::vec2();
			switch (cornnerIndex)
			{
			case 0:	centerTexCoord = glm::vec2(_radiusX / width, 1 - _radiusY / height);		break;
			case 1:	centerTexCoord = glm::vec2(1 - _radiusX / width, 1 - (_radiusY / height));	break;
			case 2:	centerTexCoord = glm::vec2(1 - _radiusX / width, _radiusY / height);		break;
			case 3:	centerTexCoord = glm::vec2(_radiusX / width, _radiusY / height);			break;
			default:																			break;
			}
			for (auto i = 0u; i < connerVertexSize; ++i)
			{
				//��䶥������
				if (i == 0)
				{
					vertexs[beg].position = center;
					vertexs[beg].texCoord = centerTexCoord;
				}
				else
				{
					auto radian = radianStep * (i - 1) + radianSpan;
					vertexs[beg + i].position = glm::vec3(_radiusX * cos(radian), _radiusY * sin(radian), 0.0) + center;
					vertexs[beg + i].texCoord = glm::vec2(centerTexCoord.x + _radiusX / width * cos(radian), centerTexCoord.y - _radiusY / height * sin(radian));
				}
				//��䶥������
				if (i >= 0 && i < connerVertexSize - 2)
				{
					int base = connerIndicesSize * cornnerIndex + (3 * i);
					indices[base] = beg;
					indices[base + 1] = beg + i + 1;
					indices[base + 2] = beg + i + 2;
				}
			}
		};
		//���Ͻǻ��Ρ����Ͻǻ��Ρ����½ǻ��Ρ����½ǻ���
		auto connerIndex = 0u;
		fillConner(glm::vec3{ _radiusX - width * 0.5, _radiusY - height * 0.5, 0.0f }, (float)M_PI, connerIndex++);
		fillConner(glm::vec3{ width * 0.5 - _radiusX, _radiusY - height * 0.5, 0.0f }, (float)M_PI * 1.5f, connerIndex++);
		fillConner(glm::vec3{ width * 0.5 - _radiusX, height * 0.5 - _radiusY, 0.0f }, M_PI * 0.0, connerIndex++);
		fillConner(glm::vec3{ _radiusX - width * 0.5, height * 0.5 - _radiusY, 0.0f }, (float)M_PI * 0.5, connerIndex++);
		//�м�ʮ���������εĶ�������
		auto beg = indices.size() - 12;
		indices[beg++] = 1;						indices[beg++] = connerVertexSize * 2 - 1;	indices[beg++] = connerVertexSize * 2 + 1;
		indices[beg++] = 1;						indices[beg++] = connerVertexSize * 2 + 1;	indices[beg++] = connerVertexSize * 4 - 1;
		indices[beg++] = connerVertexSize - 1;	indices[beg++] = connerVertexSize + 1;		indices[beg++] = connerVertexSize * 3 - 1;
		indices[beg++] = connerVertexSize - 1;	indices[beg++] = connerVertexSize * 3 - 1;	indices[beg++] = connerVertexSize * 3 + 1;

	}
	else
	{
		vertexs[0].position = glm::vec3{ -width * 0.5, height * 0.5, 0.0f };	vertexs[0].texCoord = glm::vec2(0.0, 0.0);
		vertexs[1].position = glm::vec3{ width * 0.5, height * 0.5, 0.0f };		vertexs[1].texCoord = glm::vec2(1.0, 0.0);
		vertexs[2].position = glm::vec3{ width * 0.5, -height * 0.5, 0.0f };	vertexs[2].texCoord = glm::vec2(1.0, 1.0);
		vertexs[3].position = glm::vec3{ -width * 0.5, -height * 0.5, 0.0f };	vertexs[3].texCoord = glm::vec2(0.0, 1.0);
		indices = { 0, 1, 2, 0, 2, 3 };
	}

	//���²���
	updateMeterial(m_fillObject, Fill());
}

void Rectangle::updateStrokeObject(const Rect &rc)
{
	if (!m_strokeObject)
		return;

	std::vector<glm::vec2> breaks{ glm::vec2(rc.x(), rc.y()), glm::vec2(rc.right(), rc.top()), glm::vec2(rc.right(), rc.bottom()), glm::vec2(rc.x(), rc.bottom()), glm::vec2(rc.x(), rc.y()) };
	std::dynamic_pointer_cast<Strips>(m_strokeObject->model())->update(breaks, StrokeThickness(), StrokeDashArray(), StrokeDashOffset(), StrokeLineJoin());

	updateMeterial(m_strokeObject, Stroke());
}
