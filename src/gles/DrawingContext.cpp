#include "newbrush/gles/DrawingContext.h"
#include "newbrush/gles/RenderObject.h"
#include "newbrush/gles/Program.h"
#include "newbrush/gles/Viewport2D.h"
#include "newbrush/gles/Texture2D.h"
#include "newbrush/media/ImageSource.h"
#include "newbrush/media/Pen.h"
#include "newbrush/gles/Strips.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/GradientBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/media/EffectBrush.h"
#include <math.h>

using namespace nb;

void updateBrush(RenderObjectPtr ro, BrushPtr brush)
{
	if (nb::is<SolidColorBrush>(brush))
	{
		ro->setProgram(Programs::primitive());
		auto solidColorBrush = nb::as<SolidColorBrush>(brush);
		auto const &color = solidColorBrush->getValue<Color>(SolidColorBrush::ColorProperty());
		ro->storeUniform("color", glm::vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
	}
	else if (nb::is<LinearGradientBrush>(brush))
	{
		ro->setProgram(Programs::gradientPrimitive());
		auto linearGradientBrush = nb::as<LinearGradientBrush>(brush);
		auto stops = linearGradientBrush->getValue<GradientStopCollectionPtr>(LinearGradientBrush::GradientStopsProperty());
		std::vector<glm::vec4> colors;
		std::vector<float> offsets;
		for (auto i = 0; i != stops->count(); ++i)
		{
			auto stop = (*stops)[i];
			auto color = stop->getValue<Color>(GradientStop::ColorProperty());
			auto offset = stop->getValue<float>(GradientStop::OffsetPropert());
			colors.push_back({ color.redF(), color.greenF(), color.blueF(), color.alphaF() });
			offsets.push_back(offset);
		}
		ro->storeUniform("size", stops->count());
		ro->storeUniform("colors", colors);
		ro->storeUniform("offsets", offsets);
	}
	else if (nb::is<ImageBrush>(brush))
	{
		ro->setProgram(Programs::image());
		auto source = nb::as<ImageBrush>(brush)->getValue<ImageSourcePtr>(ImageBrush::SourceProperty());
		if (source)
		{
			auto const &stream = source->stream();
			auto texture = std::make_shared<Texture2D>();
			auto glFormatAndType = Texture::getGlFormatAndType(source->channels());
			texture->update((const unsigned char *)stream.data(), (int)source->width(), (int)source->height(), glFormatAndType.first, glFormatAndType.second);
			ro->model()->meshes[0].material.textures().push_back(texture);
		}
	}
	else if (std::dynamic_pointer_cast<EffectBrush>(brush))
	{
		bool b = false;
	}
}

DrawingContext::DrawingContext()
	: m_viewport(std::make_shared<Viewport2D>())
{
}

void DrawingContext::drawLine(PenPtr pen, const Point & p0, const Point & p1)
{
	auto model = std::make_shared<Strips>();
	auto const &strokeThickness = pen->getValue<float>(Pen::ThicknessProperty());
	auto const &strokeDashArray = pen->getValue<std::vector<float>>(Pen::DashArrayProperty());
	auto const &strokeDashOffset = pen->getValue<float>(Pen::DashOffsetProperty());
	auto const &strokeLineJoin = pen->getValue<PenLineJoinE>(Pen::LineJoinProperty());
	std::vector<glm::vec2> breaks{ glm::vec2(p0.x(), p0.y()), glm::vec2(p1.x(), p1.y()) };
	model->update(breaks, strokeThickness, strokeDashArray, strokeDashOffset, strokeLineJoin);

	auto renderObj = std::make_shared<RenderObject>(model);
	m_viewport->queue(renderObj);
	auto brush = pen->getValue<BrushPtr>(Pen::BrushProperty());
	updateBrush(renderObj, brush);
}

void DrawingContext::drawRectangle(BrushPtr brush, PenPtr pen, const Rect & rect)
{
	drawRoundedRectangle(brush, pen, rect, 0.0f, 0.0f);
}

void DrawingContext::drawRoundedRectangle(BrushPtr brush, PenPtr pen, const Rect & rect, float radiusX, float radiusY)
{
	auto makeFillRenderObject = [](float width, float height, float radiusX, float radiusY)->RenderObjectPtr
	{
		auto model = std::make_shared<Model>(std::vector<Mesh>{ Mesh() });
		auto &mesh = model->meshes[0];	
		auto &vertexs = mesh.vertexs;
		auto &indices = mesh.indices;
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
		auto renderObj = std::make_shared<RenderObject>(model);
		return renderObj;
	};
	auto makeStrokeRenderObject = [](PenPtr pen, const Rect &rc)->RenderObjectPtr
	{
		auto model = std::make_shared<Strips>();
		auto const &strokeThickness = pen->getValue<float>(Pen::ThicknessProperty());
		auto const &strokeDashArray = pen->getValue<std::vector<float>>(Pen::DashArrayProperty());
		auto const &strokeDashOffset = pen->getValue<float>(Pen::DashOffsetProperty());
		auto const &strokeLineJoin = pen->getValue<PenLineJoinE>(Pen::LineJoinProperty());
		std::vector<glm::vec2> breaks{ glm::vec2(rc.x(), rc.y()), glm::vec2(rc.right(), rc.top()), glm::vec2(rc.right(), rc.bottom()), glm::vec2(rc.x(), rc.bottom()), glm::vec2(rc.x(), rc.y()) };
		model->update(breaks, strokeThickness, strokeDashArray, strokeDashOffset, strokeLineJoin);

		auto renderObj = std::make_shared<RenderObject>(model);
		return renderObj;
	};

	auto const &strokeThickness = pen->getValue<float>(Pen::ThicknessProperty());
	auto fillObj = makeFillRenderObject(rect.width() - strokeThickness, rect.height() - strokeThickness, radiusX, radiusY);
	auto strokeObj = makeStrokeRenderObject(pen, rect);
	updateBrush(fillObj, brush);
	auto penBrush = pen->getValue<BrushPtr>(Pen::BrushProperty());
	updateBrush(strokeObj, penBrush);

	m_viewport->queue(fillObj);
	m_viewport->queue(strokeObj);
}

constexpr auto vertexCount = 200;
void DrawingContext::drawEllipse(BrushPtr brush, PenPtr pen, const Point & center, float radiusX, float radiusY)
{
	auto makeFillRenderObject = [](float a, float b)->RenderObjectPtr
	{
		auto getIndices = []()->std::vector<uint16_t> 
		{
			constexpr auto count = 3 * (vertexCount - 1);
			std::vector<uint16_t> indices(count);
			for (int i = 0; i != vertexCount - 2; ++i)
			{
				int base = 3 * i;
				indices[base] = 0;
				indices[base + 1] = i + 1;
				indices[base + 2] = i + 2;
			}
			indices[count - 3] = 0;
			indices[count - 2] = vertexCount - 1;
			indices[count - 1] = 1;
			return indices;
		};

		auto model = std::make_shared<Model>(std::vector<Mesh>{ Mesh() });
		auto &mesh = model->meshes[0];
		mesh.indices = getIndices();
		auto &vertexs = mesh.vertexs;
		//���ĵ�
		vertexs[0].position = glm::vec3();
		vertexs[0].texCoord = glm::vec2(0.5, 0.5);
		//�Ƿ��ǵѿ�������ϵ��������������꽫��ͬ
		constexpr auto radianStep = 2 * M_PI / (vertexCount - 2);
		for (int i = 1; i != vertexCount; ++i)
		{
			auto radian = radianStep * i;
			vertexs[i].position = glm::vec3(a * cos(radian), b * sin(radian), 0.0);
			vertexs[i].texCoord = glm::vec2(0.5 * cos(radian) + 0.5, 1.0 - (0.5 * sin(radian) + 0.5));
		}
		auto renderObj = std::make_shared<RenderObject>(model);
		return renderObj;
	};

	auto makeStrokeRenderObject = [](PenPtr pen, float a, float b)->RenderObjectPtr
	{
		auto model = std::make_shared<Strips>();
		std::vector<glm::vec2> breaks;
		constexpr auto radianStep = 2 * M_PI / (vertexCount - 2);
		for (int i = 1; i != vertexCount; ++i)
		{
			auto radian = radianStep * i;
			auto p = glm::vec3(a * cos(radian), b * sin(radian), 0.0);
			breaks.push_back(p);
		}
		auto const &strokeThickness = pen->getValue<float>(Pen::ThicknessProperty());
		auto const &strokeDashArray = pen->getValue<std::vector<float>>(Pen::DashArrayProperty());
		auto const &strokeDashOffset = pen->getValue<float>(Pen::DashOffsetProperty());
		auto const &strokeLineJoin = pen->getValue<PenLineJoinE>(Pen::LineJoinProperty());
		model->update(breaks, strokeThickness, strokeDashArray, strokeDashOffset, strokeLineJoin);

		auto renderObj = std::make_shared<RenderObject>(model);
		return renderObj;
	};

	auto const &strokeThickness = pen->getValue<float>(Pen::ThicknessProperty());
	auto fillObj = makeFillRenderObject(radiusX - strokeThickness, radiusX - strokeThickness);
	auto strokeObj = makeStrokeRenderObject(pen, radiusX, radiusY);
	updateBrush(fillObj, brush);
	auto penBrush = pen->getValue<BrushPtr>(Pen::BrushProperty());
	updateBrush(strokeObj, penBrush);

	m_viewport->queue(fillObj);
	m_viewport->queue(strokeObj);
}

void DrawingContext::drawImage(ImageSourcePtr source, const Rect & rect)
{
	auto model = std::make_shared<Model>(std::vector<Mesh>{ Mesh() });
	auto &mesh = model->meshes[0];
	mesh.vertexs.push_back(Vertex(glm::vec3(rect.left(), rect.bottom(), 0.0f), glm::vec2(0.0, 1.0)));
	mesh.vertexs.push_back(Vertex(glm::vec3(rect.right(), rect.bottom(), 0.0f), glm::vec2(1.0, 1.0)));
	mesh.vertexs.push_back(Vertex(glm::vec3(rect.right(), rect.top(), 0.0f), glm::vec2(1.0, 0.0)));
	mesh.vertexs.push_back(Vertex(glm::vec3(rect.left(), rect.top(), 0.0f), glm::vec2(0.0, 0.0)));
	mesh.indices = { 0, 1, 2, 0, 2, 3 };
	auto renderObj = std::make_shared<RenderObject>(model, Programs::image());

	if (source)
	{
		auto texture = std::make_shared<Texture2D>();
		auto &stream = source->stream();
		auto glFormatAndType = Texture::getGlFormatAndType(source->channels());
		texture->update((const unsigned char *)stream.data(), (int)source->width(), (int)source->height(), glFormatAndType.first, glFormatAndType.second);
		renderObj->model()->meshes[0].material.textures().push_back(texture);
	}

	m_viewport->queue(renderObj);
}

void DrawingContext::drawText(const Point & p)
{
}
