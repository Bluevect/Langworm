#ifndef LEARNING_MENU_H
#define LEARNING_MENU_H

#include "../core/data.h"

#include <QMessageBox>
#include <QLayout>
#include <QLabel>
#include <QFile>

class LearningMenuWidget : public QWidget {
    Q_OBJECT

public:
    explicit LearningMenuWidget(QWidget *parent = nullptr);

    ~LearningMenuWidget() override;

    void updateRendering() const;

    signals:
    void returnBtnClicked();

    void learnBtnClicked();

public
    slots:
    void adjustDifficulty();

    void adjustMode() const;

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *topLayout;
    QLabel *titleLabel;
    QLabel *difficultyLabel;
    QLabel *modeLabel;
    QLabel *levelLabel;
    QLabel *scoreLabel;
    QVBoxLayout *buttonLayout;
    QPushButton *learnBtn;
    QPushButton *difficultyBtn;
    QPushButton *modeBtn;
    QPushButton *returnBtn;

    Data &data;
};

#endif // LEARNING_MENU_H