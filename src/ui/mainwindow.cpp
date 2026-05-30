#include "mainwindow.h"

#include "settings.h"
#include "../core/dictionary.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    // 加载数据与字典
    Data::getInstance().load();
    DictionaryManager::getInstance().loadFromJson();

    // 窗口属性设置
    resize(800, 600);
    setMinimumWidth(600);
    setMinimumHeight(400);
    setWindowTitle("词虫 - Langworm");
    setWindowIcon(QIcon(":/Langworm.ico"));

    // 菜单部件
    menu = new MenuWidget(this);
    menu->setObjectName("menu");

    // 设置部件
    settings = new SettingsWidget(this);
    settings->setObjectName("settings");

    // 学习菜单部件
    learningMenu = new LearningMenuWidget(this);
    learningMenu->updateRendering();
    learningMenu->setObjectName("learningMenu");

    // 学习部件
    learning = new LearningWidget(this);
    learning->updateRendering();
    learning->setObjectName("learning");

    // 高级学习部件 (要求用户输入释义)
    learningAdvanced = new LearningAdvancedWidget(this);
    learningAdvanced->updateRendering();
    learningAdvanced->setObjectName("learningAdvanced");

    // 绑定
    connect(menu, &MenuWidget::startBtnClicked, this, &MainWindow::onStartBtnClicked);
    connect(menu, &MenuWidget::settingsBtnClicked, this, &MainWindow::onSettingsBtnClicked);
    connect(settings, &SettingsWidget::returnBtnClicked, this, &MainWindow::onReturn);
    connect(learningMenu, &LearningMenuWidget::learnBtnClicked, this, &MainWindow::onLearnBtnClicked);
    connect(learningMenu, &LearningMenuWidget::returnBtnClicked, this, &MainWindow::onReturn);
    connect(learning, &LearningWidget::returnBtnClicked, this, &MainWindow::onStartBtnClicked);
    connect(learningAdvanced, &LearningAdvancedWidget::returnBtnClicked, this, &MainWindow::onStartBtnClicked);

    // 中心部件
    stack = new QStackedWidget(this);
    stack->addWidget(menu);
    stack->addWidget(settings);
    stack->addWidget(learningMenu);
    stack->addWidget(learning);
    stack->addWidget(learningAdvanced);
    setCentralWidget(stack);

    // 软件启动时进入菜单部件
    stack->setCurrentWidget(menu);
}

MainWindow::~MainWindow() = default;

void MainWindow::onStartBtnClicked() const {
    stack->setCurrentWidget(learningMenu);
    learningMenu->updateRendering();
}

void MainWindow::onSettingsBtnClicked() const {
    stack->setCurrentWidget(settings);
}

void MainWindow::onLearnBtnClicked() const {
    const Data &data = Data::getInstance();

    if (data.difficulty >= 4 && data.difficulty <= 6) {
        stack->setCurrentWidget(learningAdvanced);
        learningAdvanced->updateWords();
        learningAdvanced->updateRendering();
    } else {
        stack->setCurrentWidget(learning);
        learning->updateWords();
        learning->updateRendering();
    }
}

void MainWindow::onReturn() const {
    stack->setCurrentWidget(menu);
}
