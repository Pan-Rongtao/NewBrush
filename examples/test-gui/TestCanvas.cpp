#include "TestCanvas.h"

void TestCanvas::test()
{
	auto cv = std::make_shared<Canvas>();

	auto rc0 = std::make_shared<Rectangle>();
	rc0->Fill = std::make_shared<SolidColorBrush>(Colors::red());
	rc0->Width = 100;
	rc0->Height = 100;

	auto rc1 = std::make_shared<Rectangle>();
	rc1->Fill = std::make_shared<SolidColorBrush>(Colors::green());
	rc1->Width = 100;
	rc1->Height = 100;

	auto rc2 = std::make_shared<Rectangle>();
	rc2->Fill = std::make_shared<SolidColorBrush>(Colors::blue());
	rc2->Width = 100;
	rc2->Height = 100;

	auto rc3 = std::make_shared<Rectangle>();
	rc3->Fill = std::make_shared<SolidColorBrush>(Colors::firebrick());
	rc3->Width = 100;
	rc3->Height = 100;

	auto es0 = std::make_shared<Ellipse>();
	es0->Fill = std::make_shared<SolidColorBrush>(Colors::floralWhite());
	es0->Width = 100;
	es0->Height = 100;

	auto line0 = std::make_shared<Line>();
	line0->Fill = std::make_shared<SolidColorBrush>(Colors::darkBlue());
	line0->X1 = 100;
	line0->Y1 = 100;
	line0->X2 = 200;
	line0->Y2 = 200;

	auto pl0 = std::make_shared<Polyline>();
	pl0->Fill = std::make_shared<SolidColorBrush>(Colors::darkBlue());
	std::vector<Point> points{Point(0, 0), Point(100, 100), Point(150, 50), Point(200, 50), };
	pl0->Points = std::make_shared<std::vector<Point>>(points);

	auto pg0 = std::make_shared<Polygon>();
	pg0->Fill = std::make_shared<SolidColorBrush>(Colors::darkBlue());
	//std::vector<Point> points{ Point(0, 0), Point(100, 100), Point(150, 50), Point(200, 50), };
	pg0->Points = std::make_shared<std::vector<Point>>(points);

	doubleAni.From = 800;
	doubleAni.To = 1000;
	doubleAni.Easing = std::make_shared<SineEase>();
	doubleAni.BeginTime = nb::core::TimeSpan::fromSeconds(1);
	doubleAni.Duration = nb::core::TimeSpan::fromSeconds(1);
	doubleAni.StateChangedEvent += std::bind(&TestCanvas::onStateChanged, this, std::placeholders::_1);
	doubleAni.ProgressEvent += std::bind(&TestCanvas::onProgress, this, std::placeholders::_1);
	doubleAni.CompleteEvent += std::bind(&TestCanvas::onCompleted, this, std::placeholders::_1);
	doubleAni.TargetProperty = &m_window.Width;
//	doubleAni.begin();

	cv->Children().push_back(rc0);
	cv->Children().push_back(rc1);
	cv->Children().push_back(rc2);
	cv->Children().push_back(rc3);
	cv->Children().push_back(es0);
	cv->Children().push_back(line0);
	cv->Children().push_back(pl0);
	cv->Children().push_back(pg0);
	cv->setLeft(rc0, 100);
	cv->setTop(rc0, 100);
	cv->setLeft(rc1, 200);
	cv->setTop(rc1, 200);
	cv->setLeft(rc2, 300);
	cv->setTop(rc2, 300);
	cv->setLeft(rc3, 400);
	cv->setTop(rc3, 400);
	cv->setLeft(es0, 500);
	cv->setTop(es0, 100);
	cv->setLeft(line0, 100);
	cv->setTop(line0, 0);
	cv->setLeft(pl0, 10);
	cv->setTop(pl0, 10);
	cv->setLeft(pg0, 200);
	cv->setTop(pg0, 10);

	m_window.Content = cv;
	
}

void TestCanvas::onStateChanged(const Timeline::StateChangedArgs & args)
{
	printf("onStateChanged:%d\n", args.state);
}

void TestCanvas::onProgress(const Timeline::ProgressArgs & args)
{
	//	printf("onProgress:%f, width=%f\n", args.progress, m_window.Width());
	//printf("onProgress:%f, point=(%f, %f)\n", args.progress, Position().x(), Position().y());
	//	printf("onProgress:%f, color=(%d, %d, %d)\n", args.progress, Background().red(), Background().green(), Background().blue());
}

void TestCanvas::onCompleted(const Timeline::CompleteArgs & args)
{
	printf("onCompleted.\n");
}
