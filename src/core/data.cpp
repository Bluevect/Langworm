#include "data.h"

#include <QFile>

// 匿名命名空间，确保 expLevels 仅在 data.cpp 内部使用
namespace {
    // 编译期常数，定义每个等级所需的经验
    constexpr int expLevels[] = {0, 20, 60, 120, 200, 250};
}

const QString Data::dataPath = "./config/data.ini";

Data &Data::getInstance() {
    static Data instance;
    return instance;
}

Data::Data() : level(1), lastLevel(1), score(0), mode(1), difficulty(1), curIndex{-1} {
    settings = new QSettings(dataPath, QSettings::IniFormat);

    for (int i = 0; i < 6; i++) {
        wordsIndexList[i].clear();
    }
}

Data::~Data() {
    delete settings;
}

void Data::addScore(const int &scoreToAdd) {
    score += scoreToAdd;

    // 判断是否可以升级
    // expLevels[i - 1] 表示升到 i 级所需的经验
    for (int i = 2; i <= 6; i++) {
        if (score >= expLevels[i - 1] && level < i) {
            level = i;
        }
    }

    save();
}

QString Data::getExpForNextLevel() const {
    switch (level) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            return QString::number(expLevels[level]);
        case 6:
            // 显示满级
            return "MAX";
        default:
            return QString::number(expLevels[1]);
    }
}

QString Data::getModeStr() const {
    switch (mode) {
        case 1:
            return "英译中";
        case 2:
            return "中译英";
        case 3:
            return "混合模式";
        default:
            return "英译中";
    }
}

QString Data::getDifficultyStr() const {
    switch (difficulty) {
        case 1:
            return "单词";
        case 2:
            return "词组";
        case 3:
            return "短句";
        case 4:
            return "单词拼写";
        case 5:
            return "词组拼写";
        case 6:
            return "短句拼写";
        default:
            return "单词";
    }
}

QString Data::getUpgradedInfo() const {
    switch (level) {
        case 2:
            return "词组";
        case 3:
            return "短句";
        case 4:
            return "单词拼写";
        case 5:
            return "词组拼写";
        case 6:
            return "短句拼写";
        default:
            return "";
    }
}

// 保存数据至 data.ini
void Data::save() const {
    settings->setValue("level", level);
    settings->setValue("lastLevel", lastLevel);
    settings->setValue("score", score);
    settings->setValue("mode", mode);
    settings->setValue("difficulty", difficulty);

    for (int i = 0; i < 6; i++) {
        settings->setValue(QString("curIndex%1").arg(i), curIndex[i]);

        QVariantList varList;
        for (const int wordIndex: wordsIndexList[i]) {
            varList.append(wordIndex);
        }

        settings->setValue(QString("wordsIndexList%1").arg(i), varList);
    }
}

// 加载数据
void Data::load() {
    if (const QFile dataFile(dataPath); !dataFile.exists()) {
        return;
    }

    level = settings->value("level", 1).toInt();
    lastLevel = settings->value("lastLevel", 1).toInt();
    score = settings->value("score", 0).toInt();
    mode = settings->value("mode", 1).toInt();
    difficulty = settings->value("difficulty", 1).toInt();

    for (int i = 0; i < 6; i++) {
        curIndex[i] = settings->value(QString("curIndex%1").arg(i), -1).toInt();

        QVariantList varList = settings->value(QString("wordsIndexList%1").arg(i)).toList();
        wordsIndexList[i].clear();
        for (const QVariant &var: varList) {
            wordsIndexList[i].append(var.toInt());
        }
    }

    // 一致性检查
    for (int i = 1; i <= 5; i++) {
        if (level == i && score >= expLevels[i]) level = i + 1;
    }
}

void Data::resetShuffleFlag() {
    for (int i = 0; i < 6; i++) {
        curIndex[i] = -1;
        wordsIndexList[i].clear();
    }

    save();
}

// 重置所有数据
void Data::reset() {
    level = 1;
    lastLevel = 1;
    score = 0;
    mode = 1;
    difficulty = 1;

    resetShuffleFlag();
}
