#include "Utilities/DefaultIconLoader.h"
#include <QDebug>
#include <QPixmap>

namespace RibbonWidget
{
	DefaultIconLoader& DefaultIconLoader::instance()
	{
		static DefaultIconLoader instance;
		return instance;
	}


	QString DefaultIconLoader::getIconPath(const QString& name)
	{
		const DefaultIconLoader &instance = DefaultIconLoader::instance();
		return instance.m_iconBasePath + "/" + name + instance.m_iconFileExtention;
	}

	const QString& DefaultIconLoader::getIconBasePath()
	{
		return instance().m_iconBasePath;
	}
	const QString& DefaultIconLoader::getIconFileExtention()
	{
		return instance().m_iconFileExtention;
	}



	const QIcon& DefaultIconLoader::getIcon(const QString& name)
	{
		DefaultIconLoader& instance = DefaultIconLoader::instance();
		auto it = instance.m_icons.find(name);
		if (it != instance.m_icons.end())
		{
			return *it->second;
		}

		QString path = instance.getIconPath(name);

		QIcon* icon = new QIcon(path);
		instance.m_icons[name] = icon;
		return *icon;
	}

	DefaultIconLoader::DefaultIconLoader()
		: m_iconBasePath(":/icons")
		, m_iconFileExtention(".png")
	{
		Q_INIT_RESOURCE(RibbonIcons);
	}
	DefaultIconLoader::~DefaultIconLoader()
	{

	}
}