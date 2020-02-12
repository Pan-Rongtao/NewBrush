#include "newbrush/media/PropertyAnimationUsingKeyFrames.h"
#include "catch2/catch.hpp"
#include "newbrush/gui/UIElement.h"

using namespace nb;
using namespace nb::gui;

class MyObject : public DependencyObject
{
public:
	static DependencyProperty TextProperty()
	{
		static auto dp = DependencyProperty::registerDependency<MyObject, std::string>("Text", "");
		return dp;
	}
	static DependencyProperty CountProperty()
	{
		static auto dp = DependencyProperty::registerDependency<MyObject, int8_t>("Count", 0);
		return dp;
	}
	static DependencyProperty SizeProperty()
	{
		static auto dp = DependencyProperty::registerDependency<MyObject, int16_t>("Size", 0);
		return dp;
	}
	static DependencyProperty IndexProperty()
	{
		static auto dp = DependencyProperty::registerDependency<MyObject, int32_t>("Index", 0);
		return dp;
	}
	static DependencyProperty TicksProperty()
	{
		static auto dp = DependencyProperty::registerDependency<MyObject, int64_t>("Ticks", 0);
		return dp;
	}
	static DependencyProperty WidthProperty()
	{
		static auto dp = DependencyProperty::registerDependency<MyObject, float>("Width", 0.0f);
		return dp;
	}
	static DependencyProperty HeightProperty()
	{
		static auto dp = DependencyProperty::registerDependency<MyObject, double>("Height", 0.0);
		return dp;
	}
};

TEST_CASE("test BoolAnimationUsingKeyFrames", "[BoolAnimationUsingKeyFrames]")
{
	auto ui = std::make_shared<UIElement>();
	BoolAnimationUsingKeyFrames animation;
	animation.setDuration(TimeSpan::fromSeconds(5));
	animation.setTarget(ui);
	animation.setTargetProperty(UIElement::IsFocusedProperty());
	animation.keyFrames().insert(BoolKeyFrame(TimeSpan::fromSeconds(1), true));
	animation.keyFrames().insert(BoolKeyFrame(TimeSpan::fromSeconds(2), false));
	animation.keyFrames().insert(BoolKeyFrame(TimeSpan::fromSeconds(3), true));

	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto focus = ui ? ui->get<bool>(UIElement::IsFocusedProperty()) : false;
		printf("animation procesing: time[%s], progress[%.5f], focus[%d]\n", time.toString().data(), progress, focus);
	};
	animation.Completed += [](const EventArgs &args) {
		printf("animation complete\n");
	};
	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test StringAnimationUsingKeyFrames", "[StringAnimationUsingKeyFrames]")
{
	auto ui = std::make_shared<MyObject>();
	StringAnimationUsingKeyFrames animation;
	animation.setDuration(TimeSpan::fromSeconds(5));
	animation.setTarget(ui);
	animation.setTargetProperty(MyObject::TextProperty());
	animation.keyFrames().insert(StringKeyFrame(TimeSpan::fromSeconds(0), "init"));
	animation.keyFrames().insert(StringKeyFrame(TimeSpan::fromSeconds(1), "abc"));
	animation.keyFrames().insert(StringKeyFrame(TimeSpan::fromSeconds(2), "def"));
	animation.keyFrames().insert(StringKeyFrame(TimeSpan::fromSeconds(3), "sv"));

	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto txt = ui ? ui->get<std::string>(MyObject::TextProperty()) : "";
		printf("animation procesing: time[%s], progress[%.5f], txt[%s]\n", time.toString().data(), progress, txt.data());
	};
	animation.Completed += [](const EventArgs &args) {
		printf("animation complete\n");
	};
	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test Int8AnimationUsingKeyFrames", "[Int8AnimationUsingKeyFrames]")
{
	auto ui = std::make_shared<MyObject>();
	Int8AnimationUsingKeyFrames animation;
	animation.setDuration(TimeSpan::fromSeconds(3));
	animation.setTarget(ui);
	animation.setTargetProperty(MyObject::CountProperty());
	animation.keyFrames().insert(Int8KeyFrame(TimeSpan::fromSeconds(0), 10));
	animation.keyFrames().insert(Int8KeyFrame(TimeSpan::fromSeconds(1), 20));
	animation.keyFrames().insert(Int8KeyFrame(TimeSpan::fromSeconds(2), 100));

	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto count = ui ? ui->get<int8_t>(MyObject::CountProperty()) : -1;
		printf("animation procesing: time[%s], progress[%.5f], count[%d]\n", time.toString().data(), progress, count);
	};
	animation.Completed += [](const EventArgs &args) {
		printf("animation complete\n");
	};
	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test Int16AnimationUsingKeyFrames", "[Int16AnimationUsingKeyFrames]")
{
	auto ui = std::make_shared<MyObject>();
	Int16AnimationUsingKeyFrames animation;
	animation.setDuration(TimeSpan::fromSeconds(3));
	animation.setTarget(ui);
	animation.setTargetProperty(MyObject::SizeProperty());
	animation.keyFrames().insert(Int16KeyFrame(TimeSpan::fromSeconds(0), 10));
	animation.keyFrames().insert(Int16KeyFrame(TimeSpan::fromSeconds(1), 20));
	animation.keyFrames().insert(Int16KeyFrame(TimeSpan::fromSeconds(2), 100));

	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto size = ui ? ui->get<int16_t>(MyObject::SizeProperty()) : -1;
		printf("animation procesing: time[%s], progress[%.5f], count[%d]\n", time.toString().data(), progress, size);
	};
	animation.Completed += [](const EventArgs &args) {
		printf("animation complete\n");
	};
	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test Int32AnimationUsingKeyFrames", "[Int32AnimationUsingKeyFrames]")
{
	auto ui = std::make_shared<MyObject>();
	Int32AnimationUsingKeyFrames animation;
	animation.setDuration(TimeSpan::fromSeconds(3));
	animation.setTarget(ui);
	animation.setTargetProperty(MyObject::IndexProperty());
	animation.keyFrames().insert(Int32KeyFrame(TimeSpan::fromSeconds(0), -10));
	animation.keyFrames().insert(Int32KeyFrame(TimeSpan::fromSeconds(1), 0));
	animation.keyFrames().insert(Int32KeyFrame(TimeSpan::fromSeconds(2), 999));

	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto index = ui ? ui->get<int32_t>(MyObject::IndexProperty()) : -1;
		printf("animation procesing: time[%s], progress[%.5f], count[%d]\n", time.toString().data(), progress, index);
	};
	animation.Completed += [](const EventArgs &args) {
		printf("animation complete\n");
	};
	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test Int64AnimationUsingKeyFrames", "[Int64AnimationUsingKeyFrames]")
{
	auto ui = std::make_shared<MyObject>();
	Int64AnimationUsingKeyFrames animation;
	animation.setDuration(TimeSpan::fromSeconds(3));
	animation.setTarget(ui);
	animation.setTargetProperty(MyObject::TicksProperty());
	animation.keyFrames().insert(Int64KeyFrame(TimeSpan::fromSeconds(0), -10));
	animation.keyFrames().insert(Int64KeyFrame(TimeSpan::fromSeconds(1), 0));
	animation.keyFrames().insert(Int64KeyFrame(TimeSpan::fromSeconds(2), 999));
	
	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto ttt = ui ? ui->get<int64_t>(MyObject::TicksProperty()) : -1;
		printf("animation procesing: time[%s], progress[%.5f], count[%lld]\n", time.toString().data(), progress, ttt);
	};
	animation.Completed += [](const EventArgs &args) {
		printf("animation complete\n");
	};
	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test FloatAnimationUsingKeyFrames", "[FloatAnimationUsingKeyFrames]")
{
	auto ui = std::make_shared<MyObject>();
	FloatAnimationUsingKeyFrames animation;
	animation.setDuration(TimeSpan::fromSeconds(3));
	animation.setTarget(ui);
	animation.setTargetProperty(MyObject::WidthProperty());
	animation.keyFrames().insert(FloatKeyFrame(TimeSpan::fromSeconds(0), 0.1f));
	animation.keyFrames().insert(FloatKeyFrame(TimeSpan::fromSeconds(1), 0.9f));
	animation.keyFrames().insert(FloatKeyFrame(TimeSpan::fromSeconds(2), 1.0f));

	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto width = ui ? ui->get<float>(MyObject::WidthProperty()) : NAN;
		printf("animation procesing: time[%s], progress[%.5f], count[%.5f]\n", time.toString().data(), progress, width);
	};
	animation.Completed += [](const EventArgs &args) {
		printf("animation complete\n");
	};
	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}

TEST_CASE("test DoubleAnimationUsingKeyFrames", "[DoubleAnimationUsingKeyFrames]")
{
	auto ui = std::make_shared<MyObject>();
	DoubleAnimationUsingKeyFrames animation;
	animation.setDuration(TimeSpan::fromSeconds(3));
	animation.setTarget(ui);
	animation.setTargetProperty(MyObject::HeightProperty());
	animation.keyFrames().insert(DoubleKeyFrame(TimeSpan::fromSeconds(0), 0.1));
	animation.keyFrames().insert(DoubleKeyFrame(TimeSpan::fromSeconds(1), 0.9));
	animation.keyFrames().insert(DoubleKeyFrame(TimeSpan::fromSeconds(2), 1.0));

	animation.StateChanged += [](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto state = tl->currentState();
		printf("animation state chaged = %d\n", state);
	};
	animation.Process += [&ui](const EventArgs &args) {
		auto tl = static_cast<Timeline *>(args.sender);
		auto time = tl->getCurrentTime();
		auto progress = tl->getCurrentProgress();
		auto height = ui ? ui->get<double>(MyObject::HeightProperty()) : NAN;
		printf("animation procesing: time[%s], progress[%.5f], count[%.5f]\n", time.toString().data(), progress, height);
	};
	animation.Completed += [](const EventArgs &args) {
		printf("animation complete\n");
	};
	animation.begin();

	while (true)
	{
		Timer::driveInLoop();
	}
}