#include "learningmenu.h"

#include <QPushButton>

LearningMenuWidget::LearningMenuWidget(QWidget *parent)
    : QWidget{parent}, data{Data::getInstance()} {
    // 使背景样式生效
    setAttribute(Qt::WA_StyledBackground, true);

    // 垂直布局
    mainLayout = new QVBoxLayout(this);

    // 顶部布局
    topLayout = new QHBoxLayout;

    levelLabel = new QLabel(QString("等级: -1"), this);
    levelLabel->setObjectName("scoreLabel");
    topLayout->addWidget(levelLabel);

    topLayout->addStretch(1);

    scoreLabel = new QLabel(QString("Exp: -1 / -1"), this);
    scoreLabel->setObjectName("scoreLabel");
    topLayout->addWidget(scoreLabel);

    mainLayout->addLayout(topLayout);

    // 空白
    mainLayout->addStretch(1);

    // 标题部分
    titleLabel = new QLabel("学习");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName("titleLabel");
    mainLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);

    // 难度与模式部分
    difficultyLabel = new QLabel(QString("难度: -1"));
    difficultyLabel->setAlignment(Qt::AlignCenter);
    difficultyLabel->setObjectName("subTitleLabel");
    mainLayout->addWidget(difficultyLabel, 0, Qt::AlignHCenter);

    modeLabel = new QLabel(QString("模式: -1"));
    modeLabel->setAlignment(Qt::AlignCenter);
    modeLabel->setObjectName("subTitleLabel");
    mainLayout->addWidget(modeLabel, 0, Qt::AlignHCenter);

    // 空白
    mainLayout->addStretch(1);

    // 按钮部分
    buttonLayout = new QVBoxLayout;
    buttonLayout->setAlignment(Qt::AlignHCenter);

    learnBtn = new QPushButton("开始");
    difficultyBtn = new QPushButton("调整难度");
    modeBtn = new QPushButton("切换模式");
    returnBtn = new QPushButton("返回");

    buttonLayout->addWidget(learnBtn);
    buttonLayout->addWidget(difficultyBtn);
    buttonLayout->addWidget(modeBtn);
    buttonLayout->addWidget(returnBtn);

    // 绑定信号
    connect(learnBtn, &QPushButton::clicked, this, &LearningMenuWidget::learnBtnClicked);
    connect(difficultyBtn, &QPushButton::clicked, this, &LearningMenuWidget::adjustDifficulty);
    connect(modeBtn, &QPushButton::clicked, this, &LearningMenuWidget::adjustMode);
    connect(returnBtn, &QPushButton::clicked, this, &LearningMenuWidget::returnBtnClicked);

    mainLayout->addLayout(buttonLayout);

    // 空白
    mainLayout->addStretch(1);
}

LearningMenuWidget::~LearningMenuWidget() = default;

void LearningMenuWidget::adjustDifficulty() {
    data.difficulty++;

    if (data.difficulty > data.level || data.difficulty > 6)
        data.difficulty = 1;

    if (data.level == 1) {
        QMessageBox::warning(
            this,
            "等级过低",
            QString("你当前的等级过低，无法调整难度！"),
            QMessageBox::Ok
        );
    }

    difficultyLabel->setText(QString("难度: %1").arg(data.getDifficultyStr()));
}

void LearningMenuWidget::adjustMode() const {
    data.mode++;

    if (data.mode > 3)
        data.mode = 1;

    modeLabel->setText(QString("模式: %1").arg(data.getModeStr()));
}

void LearningMenuWidget::updateRendering() const {
    levelLabel->setText(QString("等级: %1").arg(data.level));
    scoreLabel->setText(QString("Exp: %1 / %2").arg(data.score).arg(data.getExpForNextLevel()));
    difficultyLabel->setText(QString("难度: %1").arg(data.getDifficultyStr()));
    modeLabel->setText(QString("模式: %1").arg(data.getModeStr()));
}
