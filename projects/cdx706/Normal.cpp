#include "Normal.h"
#include "MainView.h"

constexpr char clockNormal_vs[] = R"(
attribute vec3 position;
attribute vec2 uv;
uniform mat4 u_modelMatrix;
uniform mat4 u_viewProjectionMatrix;
varying vec2 v_uv;
void main()
{
	v_uv = uv;
	gl_Position = u_viewProjectionMatrix * u_modelMatrix * vec4(position, 1.0);
}
)";

constexpr char clockNormal_fs[] = R"(
precision mediump float;
uniform sampler2D texture1;
uniform sampler2D texture2;
varying vec2 v_uv;
uniform float u_radius;

void main( void )
{
	vec2 _npos = gl_FragCoord.xy / vec2(756.0, 756.0);   // 0.0 .. 1.0
	vec2 _uv = (1.0 - _npos);

	_uv -= vec2(0.5, 0.5);
	_uv = vec2(_uv.x * cos(u_radius) - _uv.y * sin(u_radius), _uv.x * sin(u_radius) + _uv.y * cos(u_radius));
	_uv += vec2(0.5, 0.5);
					
	vec4 _color0 = texture2D(u_sampler0, _uv);
	vec4 _color1 = texture2D(u_sampler1, v_uv);
	vec4 color;
	if(_color1.r >= 0.9)
		color = mix(_color0, _color1, 0.2);
	gl_FragColor = color;
}
)";

constexpr float R = 278.0f;
constexpr int DotsCount = 36 * 4;
const float RadiusStep = glm::two_pi<float>() / DotsCount;
constexpr float DotsAngleRange = 360.0f;
class NumberMaterial : public Material
{
public:
	NumberMaterial(ref<Texture2D> tex1, ref<Texture2D> tex2)
		: Material(ShaderLibrary::get("shader_clockNormal", clockNormal_vs, clockNormal_fs))
		, texture1(tex1)
		, texture2(tex2)
		, angle(0.0f)
	{
	}

	virtual void uploadUniform(ref<Camera> camera) override
	{
		shader->setFloat("u_radius", glm::radians(angle));
		shader->setInt("u_sampler0", 0);
		shader->setInt("u_sampler1", 1);
		if (texture1) texture1->activeAndBind();
		if (texture2) texture2->activeAndBind();
	}

	ref<Texture2D> texture1;
	ref<Texture2D> texture2;
	float angle;
};

NormalNode::NormalNode()
{
	setWidth(756.0f);
	setHeight(756.0f);
	setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"cxd706/normal/background.png")));

	TextureLibrary::addTexture2D("dot5x5", RES_DIR"cxd706/normal/spot2.png");
	TextureLibrary::addTexture2D("dot4x4", RES_DIR"cxd706/normal/spot4x4.png");
	TextureLibrary::addTexture2D("dot2x2", RES_DIR"cxd706/normal/spot2x2.png");

	m_secondPointer = createRef<Node2D>(0.0f, 0.0f, 8.0f, 8.0f);
	m_secondPointer->setBackground(createRef<ImageBrush>(createRef<Texture2D>(RES_DIR"cxd706/normal/b_008x8.png")));

	m_hourShadowParent = createRef<Node2D>(0.0f, -80.0f, 180.0f, 151.0f);
	m_hourShadowParent->setAlignmentCenter();
	m_hourShadowParent->setTransform(createRef<TranslateTransform2D>(0.0f, 0.0f));
	m_minuteShadowParent = createRef<Node2D>(0.0f, 80.0f, 180.0f, 151.0f);
	m_minuteShadowParent->setAlignmentCenter();
	m_minuteShadowParent->setTransform(createRef<TranslateTransform2D>(0.0f, 0.0f));

	m_hourParent = createRef<Node2D>(0.0f, -80.0f, 150.0f, 120.0f);
	m_hourParent->setAlignmentCenter();
	m_minuteParent = createRef<Node2D>(0.0f, 80.0f, 150.0f, 120.0f);
	m_minuteParent->setAlignmentCenter();

	m_dotPanel = createRef<Node2D>();

	glm::vec2 center(size().width / 2.0f, size().height / 2.0f);
	updateDots(center, R, 270.0f, DotsAngleRange);

	addChild(m_dotPanel);
	addChild(m_secondPointer);
	addChild(m_hourShadowParent);
	addChild(m_minuteShadowParent);
	addChild(m_hourParent);
	addChild(m_minuteParent);

	m_timer.start(10);
	m_timer.Tick += nbBindEventFunction(NormalNode::onTick);

	m_secondPointerAnimation.setTarget(m_secondPointer);
	m_secondPointerAnimation.setTargetPropertyName("Opacity");
	m_secondPointerAnimation.setFrom(0.0f);
	m_secondPointerAnimation.setTo(1.0f);
	m_secondPointerAnimation.duration = TimeSpan::fromMilliseconds(200);
	m_secondPointerAnimation.autoReverse = true;
	auto easing = createRef<CubicEase>();

	setSecondPointerForTime(R - 3*8, -90);

}

void NormalNode::onTick(const EventArgs & e)
{
	if (e.sender == &m_timer)
	{
		auto timeAngle = MainView::getAngleForTime();
		auto timeRadius = glm::radians(timeAngle);

		//setSecondPointerForTime(R, timeAngle - 90);

		glm::vec2 center(size().width / 2.0f, size().height / 2.0f);
		//updateDots(center, R, timeAngle - 90, DotsAngleRange);

		return;
		static constexpr float circleR = 40.0f;
		moveShadowNumberCircle(m_hourShadowParent, 0.0f, -80.0f, circleR, timeAngle + 90);
		moveShadowNumberCircle(m_minuteShadowParent, 0.0f, 80.0f, circleR, timeAngle + 90);

		//static auto lastMinute = now.minute();
		//if (lastMinute != now.minute())
		{
			setTime(m_hourShadowParent, 10, "_shadow", 50.0f, false, timeAngle);
			setTime(m_minuteShadowParent, 33, "_shadow", 75.0f, false, timeAngle);
			setTime(m_hourParent, 10, "", 50.0f, true, timeAngle);
			setTime(m_minuteParent, 33, "", 75.0f, true, timeAngle);
		}
	}

}

void NormalNode::moveShadowNumberCircle(ref<Node2D> node, float x, float y, float r, float angle)
{
	Point pt;
	pt.x = x + r * cos(glm::radians(angle));
	pt.y = y + r * sin(glm::radians(angle));
	node->setPosition(pt);
}

void NormalNode::moveEffectNumberCircle(ref<Node2D> node, float angle)
{
	auto brush = nb::as<EffectBrush>(node->background());
	if (!brush)
		return;

	auto material = nb::as<NumberMaterial>(brush->material);
	if (!material)
		return;

	material->angle = angle;
}

void NormalNode::setTime(ref<Node2D> parent, int value, const std::string &imagePrefix, float space, bool useEffect, float angle)
{
	parent->clearChildren();
	std::vector<ref<Node2D>> nodes;
	auto temp = value;
	while (temp)
	{
		auto n = temp % 10;
		auto nodeImagePath = std::to_string(n) + imagePrefix + ".png";
		auto tex = createRef<Texture2D>(RES_DIR"cxd706/" + nodeImagePath);
		auto brush = createRef<ImageBrush>(tex);

		static auto tex1 = createRef<Texture2D>(RES_DIR"cxd706/img_text_colour.png");
		auto tex2 = tex;
		tex2->setSamplerUnit(1);
		auto numberMaterial = createRef<NumberMaterial>(tex1, tex2);
		numberMaterial->angle = angle;
		auto numberBrush = createRef<EffectBrush>(numberMaterial, nullptr);

		auto node = createRef<Node2D>(0.0f, 0.0f, tex->width(), tex->height());
		node->setVerticalAlignment(VerticalAlignmentE::Center);
		if (useEffect)
			node->setBackground(numberBrush);
		else
			node->setBackground(brush);
		nodes.push_back(node);
		temp /= 10;
	}
	auto k = 0;
	for (int i = nodes.size() - 1; i >= 0; --i)
	{
		auto node = nodes[i];
		node->setX(space * k);
		parent->addChild(nodes[i]);
		++k;
	}
}

void NormalNode::updateDots(const glm::vec2 &center, float r, float centerAngle, float angleRange)
{
	auto angleEnd = int(centerAngle + angleRange / 2 + 360) % 360;
	auto angleMin = angleEnd - angleRange;
	auto angleMax = angleEnd;

	auto tex = TextureLibrary::getTexture2D("dot4x4");
	float w = tex->width();
	float h = tex->height();

	m_dotPanel->clearChildren();
	for (int k = 0; k <= 20; ++k)
	{
		for (int i = 0; i != DotsCount; ++i)
		{
			auto radiuses = RadiusStep * i;
			auto angle = glm::degrees(radiuses);
			if ((angleMin < 0.0f && ((angle >= angleMin + 360 && angle <= 360) || (angle >= 0 && angle <= angleMax)))
				|| (angleMin >= 0.0f && angle >= angleMin && angle <= angleMax))
			{
				glm::vec2 pt = glm::vec2(r * cos(radiuses), r * sin(radiuses)) + center - glm::vec2(w / 2, h / 2);

				auto node = createRef<Node2D>(pt.x, pt.y, w, h);
				node->setBackground(createRef<ImageBrush>(tex));
				//node->setTransform(createRef<ScaleTransform2D>(scale, scale, w / 2, h / 2));
				m_dotPanel->addChild(node);
			}
		}
		r -= 8.0f;
	}
}

float lastRadius = 0.0f;
void NormalNode::setSecondPointerForTime(float r, float angle)
{
	angle = (float)(int(angle + 360) % 360);
	float radius = glm::radians(angle);
	glm::vec2 center(size().width / 2.0f, size().height / 2.0f);
	for (int i = DotsCount; i >= 0; --i)
	{
		auto radiuses = RadiusStep * i;
		if (radius >= radiuses)
		{
			glm::vec2 pt = glm::vec2(r * cos(radiuses), r * sin(radiuses)) + center - glm::vec2(m_secondPointer->size().width / 2.0f, m_secondPointer->size().height / 2.0f);
			m_secondPointer->setPosition({ pt.x, pt.y });
			if (lastRadius != radiuses)
			{
				lastRadius = radiuses;
			//	m_secondPointerAnimation.begin();
			}
			return;
		}
	}
}