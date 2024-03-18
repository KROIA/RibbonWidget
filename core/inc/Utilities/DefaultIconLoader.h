#pragma once

#include "RibbonWidget_base.h"
#include <QString>
#include <QIcon>
#include <unordered_map>

namespace RibbonWidget
{
	class RIBBON_WIDGET_EXPORT DefaultIconLoader
	{
	public:
		static DefaultIconLoader& instance();

		//static QString getIconPath(const QString& name);
		//static const QString& getIconBasePath();
		//static const QString& getIconFileExtention();


		static const QIcon &getIcon(const QString& path);
		

		DefaultIconLoader();
		~DefaultIconLoader();
	private:



		//QString m_iconBasePath;
		//QString m_iconFileExtention;
		std::unordered_map<QString, QIcon*> m_icons;
	};
}





