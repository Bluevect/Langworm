#include "dictionary.h"

#include <QFile>
#include <QJsonObject>
#include <QRandomGenerator>

QPair<QList<QString>, QList<QString> > Dictionary::getListByMode(const int &mode) const {
    switch (mode) {
        case 1:
            return {enList, cnList};
        case 2:
            return {cnList, enList};
        case 3: {
            const int rand = QRandomGenerator::global()->bounded(2);

            if (rand == 0) {
                return {enList, cnList};
            }

            return {cnList, enList};
        }
        default:
            return {enList, cnList};
    }
}

qsizetype Dictionary::size() const {
    return enList.size();
}

void Dictionary::reset() {
    enList.clear();
    cnList.clear();
}

DictionaryManager &DictionaryManager::getInstance() {
    static DictionaryManager instance;
    return instance;
}

const QString DictionaryManager::dictPath = "./config/dictionary.json";

void DictionaryManager::loadFromJson(const QString &path) {
    // 清除旧数据
    dictLevel1.reset();
    dictLevel2.reset();
    dictLevel3.reset();

    QFile jsonFile(path);

    if (!jsonFile.exists()) {
        qFatal("Failed to load dictionary.json. Does it exist?");
    }

    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qFatal("Failed to load dictionary.json.");
    }

    const QByteArray jsonData = jsonFile.readAll();
    jsonFile.close();

    const QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData));

    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        qWarning() << "Invalid JSON format.";
        return;
    }

    QJsonObject root = jsonDoc.object();

    // 检查 Json 文件是否包含对应字段
    if (!root.contains("level1")) {
        qWarning() << "Invalid JSON format.";
        return;
    }

    if (!root.contains("level2")) {
        qWarning() << "Invalid JSON format.";
        return;
    }

    if (!root.contains("level3")) {
        qWarning() << "Invalid JSON format.";
        return;
    }

    if (!root.contains("name")) {
        qWarning() << "Invalid JSON format.";
        return;
    }

    QJsonObject level1 = root["level1"].toObject();
    QJsonObject level2 = root["level2"].toObject();
    QJsonObject level3 = root["level3"].toObject();

    dictName = root["name"].toString();

    for (auto it = level1.begin(); it != level1.end(); ++it) {
        const QString enWord = it.key();
        const QString cnWord = it.value().toString();

        dictLevel1.enList.append(enWord);
        dictLevel1.cnList.append(cnWord);
    }

    for (auto it = level2.begin(); it != level2.end(); ++it) {
        const QString enWord = it.key();
        const QString cnWord = it.value().toString();

        dictLevel2.enList.append(enWord);
        dictLevel2.cnList.append(cnWord);
    }

    for (auto it = level3.begin(); it != level3.end(); ++it) {
        const QString enWord = it.key();
        const QString cnWord = it.value().toString();

        dictLevel3.enList.append(enWord);
        dictLevel3.cnList.append(cnWord);
    }
}

const Dictionary &DictionaryManager::getDictByDifficulty(const int &difficulty) {
    switch (difficulty) {
        case 1:
        case 4:
            return dictLevel1;
        case 2:
        case 5:
            return dictLevel2;
        case 3:
        case 6:
            return dictLevel3;
        default:
            return dictLevel1;
    }
}

QString DictionaryManager::getDictName() const {
    return dictName;
}
