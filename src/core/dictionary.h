#ifndef LANGWORM_DICTIONARY_H
#define LANGWORM_DICTIONARY_H

#include <QList>

class Dictionary {
public:
    Dictionary() = default;
    ~Dictionary() = default;

    QList<QString> enList;
    QList<QString> cnList;

    QPair<QList<QString>, QList<QString>> getListByMode(const int &mode) const;
    qsizetype size() const;
    void reset();
};

// 单例模式
class DictionaryManager {
public:
    // 删除拷贝构造和赋值操作
    DictionaryManager(const DictionaryManager&) = delete;
    DictionaryManager& operator=(const DictionaryManager&) = delete;

    // 静态获取实例的接口
    static DictionaryManager& getInstance();

    static const QString dictPath;

    void loadFromJson(const QString &path = dictPath);

    const Dictionary &getDictByMode(const int &difficulty);

    QString getDictName() const;

private:
    // 私有化构造函数
    DictionaryManager() = default;
    ~DictionaryManager() = default;

    Dictionary dictLevel1;
    Dictionary dictLevel2;
    Dictionary dictLevel3;
    QString dictName;
};

#endif //LANGWORM_DICTIONARY_H