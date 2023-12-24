#include <QApplication>
#include <iostream>
#include "MainWindow.h"

int main(int argc, char* argv[])
{
	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
	QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);



	QApplication a(argc, argv);
	MainWindow w;
	w.show();


	return a.exec();
}