
#include "Settings.h"
#include <QtCore/QSettings>
#include <QtCore/QStringList>
#include <QtCore/QDir>
#include <stdio.h>

#define VERBOSE 0

ParametersMap Settings::defaultParameters_;
ParametersMap Settings::parameters_;
ParametersType Settings::parametersType_;
Settings Settings::dummyInit_;

QString Settings::workingDirectory()
{
#ifdef WIN32
	return QString("%1/Documents/%2").arg(QDir::homePath()).arg(PROJECT_NAME);
#else
	return QString("%1").arg(QDir::homePath());
#endif
}

QString Settings::iniDefaultPath()
{
    return QString("%1/%2").arg(QDir::currentPath()).arg(Settings::iniDefaultFileName());
}

void Settings::loadSettings(const QString & fileName, QByteArray * windowGeometry, QByteArray * windowState)
{
	QString path = fileName;
	if(fileName.isEmpty())
	{
		path = iniDefaultPath();
	}
	QSettings ini(path, QSettings::IniFormat);
	for(ParametersMap::const_iterator iter = defaultParameters_.begin(); iter!=defaultParameters_.end(); ++iter)
	{
		const QString & key = iter.key();
		QVariant value = ini.value(key, QVariant());
		if(value.isValid())
		{
			QString str = value.toString();
			if(str.contains(";") && str.size() != getParameter(key).toString().size())
			{
				// If a string list is modified, update the value
				// (assuming that index < 10... one character for index)
				QChar index = str.at(0);
				str = getParameter(key).toString();
				str[0] = index.toAscii();
				value = QVariant(str);
				printf("Updated list of parameter \"%s\"\n", key.toStdString().c_str());
			}
			setParameter(key, value);
		}
	}
  
	if(windowGeometry)
	{
		QVariant value = ini.value("windowGeometry", QVariant());
		if(value.isValid())
		{
			*windowGeometry = value.toByteArray();
		}
	}
	if(windowState)
	{
		QVariant value = ini.value("windowState", QVariant());
		if(value.isValid())
		{
			*windowState = value.toByteArray();
		}
	}
  
	printf("Settings loaded from %s\n", path.toStdString().c_str());
}

void Settings::saveSettings(const QString & fileName, const QByteArray & windowGeometry, const QByteArray & windowState)
{
	QString path = fileName;
	if(fileName.isEmpty())
	{
		path = iniDefaultPath();
	}
	QSettings ini(path, QSettings::IniFormat);
	for(ParametersMap::const_iterator iter = parameters_.begin(); iter!=parameters_.end(); ++iter)
	{
		QString type = Settings::getParametersType().value(iter.key());
		if(type.compare("float") == 0)
		{
			ini.setValue(iter.key(), QString::number(iter.value().toFloat(),'g',6));
		}
		else
		{
			ini.setValue(iter.key(), iter.value());
		}
	}
	if(!windowGeometry.isEmpty())
	{
		ini.setValue("windowGeometry", windowGeometry);
	}
	if(!windowState.isEmpty())
	{
		ini.setValue("windowState", windowState);
	}
	printf("Settings saved to %s\n", path.toStdString().c_str());
}

