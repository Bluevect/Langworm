#include "data.h"

#include <QFile>

// 匿名命名空间，确保 expLevels 仅在 data.cpp 内部使用
namespace {
    // 编译期常数，定义每个等级所需的经验
    constexpr int expLevels[] = {0, 20, 60, 120, 200, 250};
}

const QString Data::dataPath = "./config/data.ini";

Data& Data::getInstance() {
    static Data instance;
    return instance;
}

Data::Data() : level(1), lastLevel(1), score(0), mode(1), difficulty(1), curIndex(-1), curIndexAdvanced(-1) {
    settings = new QSettings(dataPath, QSettings::IniFormat);
    wordsIndexList.clear();
    wordsIndexListAdvanced.clear();
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
    settings->setValue("curIndex", curIndex);
    settings->setValue("curIndexAdvanced", curIndexAdvanced);

    QVariantList varList;
    for (const int wordIndex : wordsIndexList) {
        varList.append(wordIndex);
    }

    settings->setValue("wordsIndexList", varList);

    varList.clear();
    for (const int wordIndex : wordsIndexListAdvanced) {
        varList.append(wordIndex);
    }

    settings->setValue("wordsIndexListAdvanced", varList);
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

    curIndex = settings->value("curIndex", -1).toInt();
    curIndexAdvanced = settings->value("curIndexAdvanced", -1).toInt();

    QVariantList varList = settings->value("wordsIndexList").toList();
    wordsIndexList.clear();
    for (const QVariant &var : varList) {
        wordsIndexList.append(var.toInt());
    }

    varList = settings->value("wordsIndexListAdvanced", varList).toList();
    wordsIndexListAdvanced.clear();
    for (const QVariant &var : varList) {
        wordsIndexListAdvanced.append(var.toInt());
    }

    // 一致性检查
    for (int i = 1; i <= 5; i++) {
        if (level == i && score >= expLevels[i]) level = i + 1;
    }
}

void Data::resetShuffleFlag() {
    curIndex = -1;
    curIndexAdvanced = -1;
    wordsIndexList.clear();
    wordsIndexListAdvanced.clear();

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
