#pragma once
#include "newbrush/Node2D.h"
#include "newbrush/Texture.h"

namespace nb
{

enum class StretchE
{
	Origion			= 0,	//����ԭ���ݴ�С
	Fill			= 1,	//�����������ݺ�ȣ��������ݴ�С����ȫ�Ҹպ����Ŀ��ߴ�
	Uniform			= 2,	//���������ݺ�ȣ�ͬʱ���ڴ�С����ӦĿ��ߴ�
	UniformToFill	= 3,	//���������ݺ�ȣ�ͬʱ���ڴ�С�����Ŀ��ߴ�
};

class NB_API Polyline : public Node2D
{
public:
	Polyline();
	Polyline(const std::vector<glm::vec2> &points, float size);

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;
	virtual void onRender() override;

private:
	std::vector<glm::vec2> m_points;
	float m_size;
};

class NB_API Polygon : public Node2D
{
public:
	Polygon();
	Polygon(const std::vector<glm::vec2> &points);

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;
	virtual void onRender() override;

private:
	std::vector<glm::vec2> m_points;
};

class NB_API Image : public Node2D
{
public:
	Image();

	void setStretch(const StretchE &stretch);
	const StretchE &stretch() const;

	void setTexture(ref<Texture2D> texture);
	ref<Texture2D> texture() const;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;
	virtual void onRender() override;

private:
	StretchE m_stretch;
	ref<Texture2D> m_texture;
	Size m_availableSize;
};

class TextBlock : public Node2D
{
public:

};

class NB_API ButtonBase : public Node2D
{
public:
	ButtonBase();

	bool isPressed() const;

	Event<EventArgs> Click;

protected:
	virtual void onTouch(const TouchEventArgs &e);
	virtual void onClick();

private:
	bool m_isPressed;
	bool m_leaveWithPressed;
};

}