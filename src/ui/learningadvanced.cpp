#include "learningadvanced.h"

#include <QApplication>
#include <QLabel>
#include <QRandomGenerator>
#include <QPushButton>

#include "../core/dictionary.h"

LearningAdvancedWidget::LearningAdvancedWidget(QWidget *parent)
    : QWidget{parent}, data{Data::getInstance()} {
    // 使背景样式生效
    setAttribute(Qt::WA_StyledBackground, true);

    updateWords();

    // 垂直布局
    mainLayout = new QVBoxLayout(this);

    // 得分
    scoreLayout = new QHBoxLayout;

    levelLabel = new QLabel(QString("等级: -1"), this);
    levelLabel->setObjectName("scoreLabel");
    scoreLayout->addWidget(levelLabel);

    scoreLayout->addStretch(1);

    scoreLabel = new QLabel(QString("Exp: -1"), this);
    scoreLabel->setObjectName("scoreLabel");
    scoreLayout->addWidget(scoreLabel);

    mainLayout->addLayout(scoreLayout);

    // 空白
    mainLayout->addStretch(1);

    // 标题部分
    titleLabel = new QLabel(curWord, this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName("titleLabel");
    mainLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);

    // 空白
    mainLayout->addStretch(1);

    // 文本框部分
    inputLayout = new QHBoxLayout;
    inputLayout->addStretch(1);
    inputLayout->setAlignment(Qt::AlignHCenter);

    inputEdit = new QLineEdit(this);
    inputEdit->setPlaceholderText("请输入释义或原单词...");
    inputEdit->setMinimumWidth(250);
    inputEdit->setObjectName("inputEdit");

    submitBtn = new QPushButton("提交", this);
    submitBtn->setObjectName("submitBtn");

    connect(submitBtn, &QPushButton::clicked, this, [=]() {
        // 根据模式使用词典
        const Dictionary &dict = DictionaryManager::getInstance().getDictByDifficulty(data.difficulty);

        if (inputEdit->text() == curMeaning) {
            // 回答正确
            data.addScore(data.difficulty);

            // 更新 curIndex
            const int d = data.difficulty - 1;
            data.curIndex[d]++;

            // 如果单词遍历结束，则下次遍历时重新初始化
            if (data.curIndex[d] >= dict.size()) {
                data.curIndex[d] = -1;
            }

            data.save();

            updateWords();
            updateRendering();

            inputEdit->setText("");
        } else {
            // 回答错误
            QMessageBox::warning(
                this,
                "答案错误",
                QString("答错了！请再试一次。"),
                QMessageBox::Ok
            );
        }

        if (data.level > data.lastLevel) {
            const QString upgradedInfo = data.getUpgradedInfo();

            // 如果升级提示信息为空，直接返回结束该函数
            if (upgradedInfo.isEmpty()) {
                return;
            }

            QMessageBox::information(
                this,
                "解锁新难度",
                QString("你当前等级已达 %1, 解锁了新难度 %2").arg(data.level).arg(upgradedInfo),
                QMessageBox::Ok
            );

            data.lastLevel = data.level;
        }
    });

    // 绑定回车到按钮点击事件上
    connect(inputEdit, &QLineEdit::returnPressed, submitBtn, &QPushButton::click);

    inputLayout->addWidget(inputEdit);
    inputLayout->addWidget(submitBtn);
    inputLayout->addStretch(1);

    mainLayout->addLayout(inputLayout);

    // 空白
    mainLayout->addStretch(1);

    // 返回按钮部分
    returnLayout = new QHBoxLayout;

    progressLabel = new QLabel("进度: -1 / -1", this);
    progressLabel->setObjectName("subTitleLabel");

    returnLayout->addWidget(progressLabel);
    returnLayout->addStretch(1);

    returnBtn = new QPushButton("返回");
    returnLayout->addWidget(returnBtn);

    connect(returnBtn, &QPushButton::clicked, this, &LearningAdvancedWidget::returnBtnClicked);

    mainLayout->addLayout(returnLayout);
}

void LearningAdvancedWidget::updateWords() {
    // 根据模式使用词典
    const Dictionary &dict = DictionaryManager::getInstance().getDictByDifficulty(data.difficulty);

    const int d = data.difficulty - 1;

    // 更新私有变量
    QPair<QList<QString>, QList<QString> > listPair = dict.getListByMode(data.mode);
    wordsList = listPair.first;
    meaningsList = listPair.second;

    if (dict.size() <= 0) {
        qFatal("Dictionary is empty. Aborted.");
    }

    tryShuffle();

    curWord = wordsList[data.wordsIndexList[d][data.curIndex[d]]];
    curMeaning = meaningsList[data.wordsIndexList[d][data.curIndex[d]]];
}

// 重置打乱标志位
void LearningAdvancedWidget::tryShuffle() const {
    // 根据模式使用词典
    const Dictionary &dict = DictionaryManager::getInstance().getDictByDifficulty(data.difficulty);

    const int d = data.difficulty - 1;

    // 将正确单词列表随机打乱，确保每一个单词都有出现的机会
    // curIndex 初始值为 -1，若为 -1 则重新打乱 wordsIndexList
    // 这里不选择直接打乱 wordsList 是因为混合模式下字典是随机的，但两个字典的长度一致
    if (data.curIndex[d] == -1) {
        // 初始化 wordsIndexList
        data.wordsIndexList[d].clear();

        for (int i = 0; i < dict.size(); i++) {
            data.wordsIndexList[d].append(i);
        }

        // 使用标准库的 shuffle 函数进行打乱
        // 使用 Qt 内置的 QRandomGenerator 实现随机数生成
        std::shuffle(data.wordsIndexList[d].begin(), data.wordsIndexList[d].end(), *QRandomGenerator::global());

        // 打乱结束令 curIndex = 0，从第一个单词开始遍历
        data.curIndex[d] = 0;
    }
}

void LearningAdvancedWidget::updateRendering() const {
    const Dictionary &dict = DictionaryManager::getInstance().getDictByDifficulty(data.difficulty);

    const int d = data.difficulty - 1;

    // 更新渲染
    scoreLabel->setText(QString("Exp: %1 / %2").arg(data.score).arg(data.getExpForNextLevel()));
    levelLabel->setText(QString("等级: %1").arg(data.level));
    titleLabel->setText(curWord);
    progressLabel->setText(QString("进度: %1 / %2").arg(data.curIndex[d] + 1).arg(dict.size()));
}

LearningAdvancedWidget::~LearningAdvancedWidget() = default;
