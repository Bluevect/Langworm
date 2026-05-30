#ifndef LEARNING_H
#define LEARNING_H

#include "../core/data.h"

#include <QMessageBox>
#include <QWidget>
#include <QLayout>
#include <QLabel>

class LearningWidget : public QWidget {
    Q_OBJECT

public:
    explicit LearningWidget(QWidget *parent = nullptr);

    ~LearningWidget() override;

    void updateWords();

    void updateRendering() const;

    void tryShuffle() const;

    signals:
        void returnBtnClicked();

public slots:
    void onOptionClicked();

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *scoreLayout;
    QLabel *scoreLabel;
    QLabel *levelLabel;
    QLabel *titleLabel;
    QGridLayout *optionsLayout;
    QPushButton *optBtn1;
    QPushButton *optBtn2;
    QPushButton *optBtn3;
    QPushButton *optBtn4;
    QHBoxLayout *returnLayout;
    QLabel *progressLabel;
    QPushButton *returnBtn;

    QString curWord;
    QString curMeaning;
    QList<QString> wordsList;
    QList<QString> meaningsList;
    QList<QString> optsList;

    Data& data;
};

#endif // LEARNING_H
