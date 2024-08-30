#include "setting.h"
#include <QIODevice>
#include <QFile>
#include <QTextStream>
#include <QDebug>

Setting::Setting()
{
    QFile file(SETTING_FILE_NAME);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream in(&file);
    QString line = nullptr;
    while ((line = in.readLine()) != nullptr)
    {
        QString key = line;
        if ((line = in.readLine()) == nullptr) break;
        QString value = line.replace("\\n", "\n");
        keyValues[key.toStdString()] = value.toStdString();
        qDebug() << key << value;
    }
    file.close();

}

const std::string Setting::get(const std::string& key)
{
    return keyValues.count(key) ? keyValues[key] : "";
}

void Setting::put(const std::string& key, const std::string& value)
{
    keyValues[std::move(key)] = std::move(value);
}

void Setting::store()
{
    QFile file(SETTING_FILE_NAME);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
    {
        return;
    }

    for (auto begin = keyValues.cbegin(),
                end = keyValues.cend(); begin != end; ++begin)
    {
        file.write(QByteArray::fromStdString(begin->first));
        file.write(QByteArray::fromStdString("\n"));
        file.write(QByteArray::fromStdString(begin->second).replace("\n", "\\n"));
        file.write(QByteArray::fromStdString("\n"));
    }

    file.flush();
    file.close();
}

bool Setting::isEmpty() const
{
    return keyValues.empty();
}
