#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "menu.h"
#include "learningmenu.h"
#include "learning.h"
#include "learningadvanced.h"
#include "settings.h"

#include <QMainWindow>
#include <QStackedWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

public
slots:
    void onStartBtnClicked() const;

    void onSettingsBtnClicked() const;

    void onLearnBtnClicked() const;

    void onReturn() const;

private:
    MenuWidget *menu;
    SettingsWidget *settings;
    LearningMenuWidget *learningMenu;
    LearningWidget *learning;
    LearningAdvancedWidget *learningAdvanced;
    QStackedWidget *stack;
};
#endif // MAINWINDOW_H
