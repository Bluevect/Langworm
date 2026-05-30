#ifndef LANGWORM_DATA_H
#define LANGWORM_DATA_H

#include <QSettings>

// 单例模式
class Data {
public:
    // 删除拷贝构造和赋值操作
    Data(const Data&) = delete;
    Data& operator=(const Data&) = delete;

    // 静态获取实例的接口
    static Data& getInstance();

    static const QString dataPath;

    int level;
    int lastLevel;
    int score;
    int mode;
    int difficulty;

    void addScore(const int &scoreToAdd = 1);

    QString getExpForNextLevel() const;

    QString getModeStr() const;

    QString getDifficultyStr() const;

    QString getUpgradedInfo() const;

    void save() const;

    void load();

    void reset();

private:
    // 私有化构造函数
    Data();
    ~Data();

    QSettings *settings;
};


#endif //LANGWORM_DATA_H
