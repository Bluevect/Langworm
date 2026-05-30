#ifndef LEARNINGADVANCED_H
#define LEARNINGADVANCED_H

#include "../core/data.h"

#include <QMessageBox>
#include <QWidget>
#include <QLayout>
#include <QLineEdit>

class LearningAdvancedWidget : public QWidget {
    Q_OBJECT

public:
    explicit LearningAdvancedWidget(QWidget *parent = nullptr);

    ~LearningAdvancedWidget() override;

    void updateWords();

    void updateRendering() const;

    void tryShuffle() const;

    signals:
        void returnBtnClicked();

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *scoreLayout;
    QLabel *scoreLabel;
    QLabel *levelLabel;
    QLabel *titleLabel;
    QHBoxLayout *inputLayout;
    QLineEdit *inputEdit;
    QPushButton *submitBtn;
    QHBoxLayout *returnLayout;
    QLabel *progressLabel;
    QPushButton *returnBtn;

    QString curWord;
    QString curMeaning;
    QList<QString> wordsList;
    QList<QString> meaningsList;

    Data& data;
};

#endif // LEARNINGADVANCED_H