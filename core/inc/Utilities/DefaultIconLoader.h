#pragma once

#include "RW_base.h"
#include <QString>
#include <QIcon>
#include <unordered_map>

namespace RibbonWidget
{
	class RIBBONWIDGET_EXPORT DefaultIconLoader
	{
	public:
		static DefaultIconLoader& instance();

		static QString getIconPath(const QString& name);
		static const QString& getIconBasePath();
		static const QString& getIconFileExtention();


		static const QIcon &getIcon(const QString& name);
		

		DefaultIconLoader();
		~DefaultIconLoader();
	private:



		QString m_iconBasePath;
		QString m_iconFileExtention;
		std::unordered_map<QString, QIcon*> m_icons;
	};
}





