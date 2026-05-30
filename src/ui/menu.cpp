#include "menu.h"

#include <QMessageBox>
#include <QWidget>

MenuWidget::MenuWidget(QWidget *parent)
    : QWidget{parent} {
    // 使背景样式生效
    setAttribute(Qt::WA_StyledBackground, true);

    // 垂直布局
    mainLayout = new QVBoxLayout(this);

    // 空白
    mainLayout->addStretch(1);

    // 标题部分
    titleLabel = new QLabel("词虫");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName("titleLabel");
    mainLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);

    // 副标题部分
    subTitleLabel = new QLabel("一个单词记忆辅助软件");
    subTitleLabel->setAlignment(Qt::AlignCenter);
    subTitleLabel->setObjectName("subTitleLabel");
    mainLayout->addWidget(subTitleLabel, 0, Qt::AlignHCenter);

    // 空白
    mainLayout->addStretch(1);

    // 按钮部分
    buttonLayout = new QVBoxLayout;
    buttonLayout->setAlignment(Qt::AlignHCenter);

    startBtn = new QPushButton("开始");
    settingsBtn = new QPushButton("设置");
    aboutBtn = new QPushButton("关于");
    aboutQtBtn = new QPushButton("关于 Qt");

    buttonLayout->addWidget(startBtn);
    buttonLayout->addWidget(settingsBtn);
    buttonLayout->addWidget(aboutBtn);
    buttonLayout->addWidget(aboutQtBtn);

    // 绑定信号
    connect(startBtn, &QPushButton::clicked, this, &MenuWidget::startBtnClicked);
    connect(settingsBtn, &QPushButton::clicked, this, &MenuWidget::settingsBtnClicked);
    connect(aboutBtn, &QPushButton::clicked, this, [=]() {
        QMessageBox::about(
            this,
            "关于 词虫 - Langworm",
            "这是一个简单的单词记忆辅助软件，选出单词的对应的释义可获得经验，"
            "达到一定经验后等级会提升，并解锁新的难度。\n"
            "游戏的难度和模式均可自由调整。\n\n"
            "若玩家想扩充词典，可使用设置中的 导入 / 导出 功能编辑字典文件，"
            "或下载其他玩家制作的词典文件并导入软件内。\n\n"
            "背景图片来自 Unsplash，由 Claudio Schwarz 创作。"
        );
    });
    connect(aboutQtBtn, &QPushButton::clicked, this, [=]() {
        QMessageBox::aboutQt(this, "关于 Qt");
    });

    mainLayout->addLayout(buttonLayout);

    // 空白
    mainLayout->addStretch(1);
}

MenuWidget::~MenuWidget() = default;