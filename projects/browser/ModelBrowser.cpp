﻿#include "ModelBrowser.h"
#include "ghc/filesystem.hpp"

using namespace nb;
namespace fs = ghc::filesystem;

bool g_useBkg = false;
bool g_rotate360 = false;
extern MessageQueue g_msgQueue;

void ModelBrowser::init()
{
	m_scene = createRef<Scene>();
	m_data = buildData();
	if (m_data)
	{
		m_data->ValueChanged += [&](const DataContext::ValueChangedArgs & args)
		{
			onDataChanged(args.path, args.value);
		};
	}
	load(RES_DIR"/browser/girl/3.fbx");
	m_root = createRef<Node2D>();
	m_root->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_root->setVerticalAlignment(VerticalAlignmentE::Bottom);
	m_root->setBackground(createRef<SolidColorBrush>(Color(100, 100, 100)));
	m_root->setScene(m_scene);
	m_root->Touch += nbBindEventFunction(ModelBrowser::onTouch);
	m_root->Scroll += nbBindEventFunction(ModelBrowser::onScroll);
	m_root->Key += nbBindEventFunction(ModelBrowser::onKey);
#ifdef WIN32
	Application::get()->mainWindow()->Drop += nbBindEventFunction(ModelBrowser::onDrop);
#endif
}

void ModelBrowser::onDataChanged(const std::string &path, const var &value)
{
	if (path == "AllSwitch") //动画总开关数据
	{
		//bool bOn = value.get_value<bool>();
		//for (auto sb : m_scene->animations)
		//{
		//	for (auto tl : sb->children())
		//	{
		//		tl->reverse = !bOn;
		//	}
		//}

		//for (auto ani : m_scene->animations)
		//{
		//	ani->begin();
		//}
	}
	else if (path.size() >= 5 && path.substr(0, 4) == "Door")	//动画开关数据"Door*Switch"
	{
		size_t animationIndex = path[4] - 48 - 1;
		//auto ani = (m_scene->animations.empty() || animationIndex >= m_scene->animations[0]->children().size())
		//	? nullptr : m_scene->animations[0]->children()[animationIndex];
		//if (ani)
		//{
		//	ani->reverse = !value.get_value<bool>();
		//	ani->begin();
		//}
	}
	else if (path == "NewPath") //更换模型数据（由于涉及到OGL的api调用，如果是android端，需要MessageQueue转到SurfaceView渲染线程
	{
		auto newModelPath = value.get_value<std::string>();
		auto task = [this, newModelPath]()
		{
			load(newModelPath);
		};

#ifdef __ANDROID__
		g_msgQueue.post(task);
#else
		task();
#endif

	}
}

void ModelBrowser::load(const std::string & path)
{
	auto model = loadModel(path, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.015f));
	m_scene->clearLights();
	m_scene->clearChildren();
	m_scene->addLight(createRef<PointLight>());
	m_scene->addChild(model);
	binding();
}

void ModelBrowser::onTouch(const TouchEventArgs & e)
{
	Point p = { e.x, e.y };
	if (e.action == TouchActionE::down)
	{
		m_pressed = true;
		m_pressedPoint = p;
	}
	else if (e.action == TouchActionE::move)
	{
		if (!m_pressed) return;

		Point ptOffset = { p.x - m_pressedPoint.x, m_pressedPoint.y - p.y };
		m_pressedPoint = p;

		auto model = as<Model>(m_scene->getChildAt(0));
		if (!model)
			return;

		auto rotate = model->getTransform()->getRotate();
		auto newAngleY = glm::degrees(rotate.y) + ptOffset.x;
		rotate.y = glm::radians(newAngleY);
		if (g_rotate360)
		{
			auto newAngleX = glm::degrees(rotate.x) - ptOffset.y;
			rotate.x = glm::radians(newAngleX);
		}
		model->getTransform()->setRotate(rotate);
	}
	else if (e.action == TouchActionE::up)
	{
		m_pressed = false;
	}
}

void ModelBrowser::onScroll(const ScrollEventArgs & e)
{
	auto scale = m_data->lookup("Scale")->get().get_value<glm::vec3>();
	auto newScale = e.delta > 0 ? scale + glm::vec3(0.001f) : scale - glm::vec3(0.001f);
	setData("Scale", newScale);
}

void ModelBrowser::onKey(const KeyEventArgs &e)
{
	auto keyDown = e.action == KeyAction::down;
	auto model = as<Model>( m_scene->getChildAt(0) );
	auto light = m_scene->hasLight() ? nb::as<PointLight>(m_scene->getLightAt(0)) : nullptr;
	auto camera = m_scene->getCamera();
	Log::info("key[{}] press", (int)e.key);
	auto modelTranslate = model->getTransform()->getTranslate();
	auto modelRotate = model->getTransform()->getRotate();
	auto cameraRotate = camera->getRotate();
	switch (e.key)
	{
	case KeyCode::W:	modelTranslate.y += 0.1f; model->getTransform()->setTranslate(modelTranslate);	break;
	case KeyCode::S:	modelTranslate.y -= 0.1f; model->getTransform()->setTranslate(modelTranslate);	break;
	case KeyCode::A:	modelTranslate.x -= 0.1f; model->getTransform()->setTranslate(modelTranslate);	break;
	case KeyCode::D:	modelTranslate.x += 0.1f; model->getTransform()->setTranslate(modelTranslate);	break;
	case KeyCode::Z:	modelTranslate.z += 0.1f; model->getTransform()->setTranslate(modelTranslate);	break;
	case KeyCode::X:	modelTranslate.z -= 0.1f; model->getTransform()->setTranslate(modelTranslate);	break;
	case KeyCode::R:	modelRotate.y -= 0.1f; model->getTransform()->setRotate(modelRotate);	break;
	case KeyCode::T:	modelRotate.y += 0.1f; model->getTransform()->setRotate(modelRotate);	break;
	case KeyCode::F:	modelRotate.x += 0.1f; model->getTransform()->setRotate(modelRotate);	break;
	case KeyCode::G:	modelRotate.x -= 0.1f; model->getTransform()->setRotate(modelRotate);	break;

	case KeyCode::_1:	if (keyDown) setData("NewPath", RES_DIR"/browser/a08/fbx.fbx");		break;
	case KeyCode::_2:	if (keyDown) setData("NewPath", RES_DIR"/browser/am8/fbx.fbx");		break;
	case KeyCode::_3:	if (keyDown) setData("NewPath", RES_DIR"/browser/assassin/fbx.fbx");break;
	case KeyCode::_4:	if (keyDown) setData("NewPath", RES_DIR"/browser/bmw/fbx.fbx");		break;
	case KeyCode::_5:	if (keyDown) setData("NewPath", RES_DIR"/browser/bugatti/fbx.fbx");	break;
	case KeyCode::_6:	if (keyDown) setData("NewPath", RES_DIR"/browser/nanosuit/obj.obj");break;
	case KeyCode::_7:	if (keyDown) setData("NewPath", RES_DIR"/browser/siqi/fbx.fbx");	break;
	case KeyCode::_8:	if (keyDown) setData("NewPath", RES_DIR"/browser/dancer/fbx.fbx");	break;
	case KeyCode::_9:	if (keyDown) setData("NewPath", RES_DIR"/browser/girl/3.fbx");		break;
	case KeyCode::_0:	if (keyDown) setData("NewPath", RES_DIR"/browser/robert0/fbx.fbx");	break;

	case KeyCode::J:	cameraRotate.y += 0.1f; camera->setRotate(cameraRotate);break;
	case KeyCode::L:	cameraRotate.y -= 0.1f; camera->setRotate(cameraRotate);break;
	case KeyCode::K:	cameraRotate.x += 0.1f; camera->setRotate(cameraRotate);break;
	case KeyCode::I:	cameraRotate.x -= 0.1f; camera->setRotate(cameraRotate);break;

	case KeyCode::right:if (light) light->position.x += 1;						break;
	case KeyCode::left:	if (light) light->position.x -= 1;						break;
	case KeyCode::down:	if (light) light->position.y -= 1;						break;
	case KeyCode::up:	if (light) light->position.y += 1;						break;

	case KeyCode::kp_0:
	{
		auto bOn = m_data->lookup("AllSwitch")->get().get_value<bool>();
		//setData("AllSwitch", !bOn);
		setData("AllSwitch", true);
	}
	break;
	case KeyCode::kp_1: case KeyCode::kp_2: case KeyCode::kp_3: case KeyCode::kp_4: case KeyCode::kp_5: case KeyCode::kp_6: //小键盘1~6设置动画开关数据
	{
		std::string doorDataPath = "Door" + std::to_string((int)e.key - (int)KeyCode::kp_0) + "Switch";
		auto bOn = m_data->get(doorDataPath)->get().get_value<bool>();
		setData(doorDataPath, !bOn);
	}
	break;
	case KeyCode::kp_decimal:
	{
	}
	break;
	case KeyCode::minus: case KeyCode::equal:
	{
		auto scale = m_data->lookup("Scale")->get().get_value<glm::vec3>();
		auto newScale = e.key == KeyCode::minus ? scale - glm::vec3(0.002f) : scale + glm::vec3(0.002f);
		setData("Scale", newScale);
	}
	break;
	case KeyCode::kp_enter:
	{
		if (!m_scene->hasLight())
			return;

		auto target = m_scene->getLightAt(0);
		auto targetProperty = type::get<Light>().get_property("Ambient");
		m_lightAnimation.beginTime = TimeSpan::fromSeconds(1);
		m_lightAnimation.duration = TimeSpan::fromSeconds(10);
		m_lightAnimation.setTarget(target);
		m_lightAnimation.setTargetProperty(targetProperty);
		m_lightAnimation.keyFrames().insert(ColorKeyFrame(TimeSpan::fromSeconds(0), Colors::red));
		m_lightAnimation.keyFrames().insert(ColorKeyFrame(TimeSpan::fromSeconds(1), Colors::green));
		m_lightAnimation.keyFrames().insert(ColorKeyFrame(TimeSpan::fromSeconds(3), Colors::blue));
		m_lightAnimation.begin();
	}
	case KeyCode::kp_divide:
	{
		//m_scene->camera->projectionType = ProjectionType::Orthographic;
		//auto scale = m_scene->children[0]->transform->getScale() * 20.0f;
		//m_scene->children[0]->transform->setScale(scale);
	}
	break;
	case KeyCode::space:
	{
		if (keyDown)
		{
			auto isPlaying = model->isPlaying();
			!isPlaying ? model->play() : model->pause();
		}
	}
	break;
	case KeyCode::F1:
	{
		if (keyDown) g_rotate360 = !g_rotate360;
	}
	break;
	case KeyCode::F2:
	{
		if (keyDown)
		{
			auto material = createRef<Material>();
			auto *vs =
#include "../../libnb/newbrush/shader/Normal.vs"
				;
			auto *fs =
#include "../../libnb/newbrush/shader/Normal.fs"
				;
			material->shader = ShaderLibrary::get("shader_normal", vs, fs);
			model->setMaterial(material);
		}
	}
	break;
	case KeyCode::F3:
	{
		if (keyDown)
		{
			auto material = createRef<Material>();
			auto *vs =
#include "../../libnb/newbrush/shader/Fresnel.vs"
				;
			auto *fs =
#include "../../libnb/newbrush/shader/Fresnel.fs"
				;
			material->shader = ShaderLibrary::get("shader_fresnel", vs, fs);
			model->setMaterial(material);
		}
	}
	break;
	default: break;
	}
}

void ModelBrowser::onDrop(const DropEventArgs & e)
{
	auto paths = e.paths;

	if (paths.size() == 1)
	{
		load(paths[0]);
	}
	else if (paths.size() == 2)
	{
		auto const &vs = paths[0];
		auto const &fs = paths[1];

	}
}

ref<DataObject> ModelBrowser::buildData()
{
	auto data = nb::makeDataObject("m_root");
	data->add(makeDataColor("Ambient", Color(127, 127, 127)));
	data->add(makeDataColor("Diffuse", Color(127, 127, 127)));
	data->add(makeDataColor("Specular", Color(127, 127, 127)));
	data->add(makeDataVec3("LightPosition", glm::vec3(0.0f, 0.0f, 5.0f)));
	data->add(makeDataVec3("Translate", glm::vec3(0.0f, -1.0f, 0.0f)));
	data->add(makeDataVec3("Rotate", glm::vec3(0.0f, 0.0f, 0.0f)));
	data->add(makeDataVec3("Scale", glm::vec3(0.020f)));
	data->add(makeDataBool("AllSwitch", false));
	data->add(makeDataBool("Door1Switch", false));
	data->add(makeDataBool("Door2Switch", false));
	data->add(makeDataBool("Door3Switch", false));
	data->add(makeDataBool("Door4Switch", false));
	data->add(makeDataBool("Door5Switch", false));
	data->add(makeDataBool("Door6Switch", false));
	data->add(makeDataString("NewPath", ""));
	return data;
}

void ModelBrowser::binding()
{
	if (!m_scene || !m_data)	return;

	auto light = m_scene->hasLight() ? nb::as<PointLight>(m_scene->getLightAt(0)) : nullptr;
	if (light)
	{
		BindingMaster::clear();
		BindingMaster::addBinding(light, type::get<PointLight>().get_property("Ambient"), createRef<Binding>(m_data, "Ambient"));
		BindingMaster::addBinding(light, type::get<PointLight>().get_property("Diffuse"), createRef<Binding>(m_data, "Diffuse"));
		BindingMaster::addBinding(light, type::get<PointLight>().get_property("Specular"), createRef<Binding>(m_data, "Specular"));
		BindingMaster::addBinding(light, type::get<PointLight>().get_property("Position"), createRef<Binding>(m_data, "LightPosition"));
	}

	auto target1 = m_scene->getChildAt(0)->getTransform();
	BindingMaster::addBinding(target1, type::get<Transform>().get_property("Translate"), createRef<Binding>(m_data, "Translate"));
	BindingMaster::addBinding(target1, type::get<Transform>().get_property("Rotate"), createRef<Binding>(m_data, "Rotate"));
	BindingMaster::addBinding(target1, type::get<Transform>().get_property("Scale"), createRef<Binding>(m_data, "Scale"));

}

//一定不要少了这句
ref<ViewBase> g_view = createRef<ModelBrowser>();