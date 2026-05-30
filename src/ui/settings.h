#ifndef SETTINGS_H
#define SETTINGS_H

#include <QLabel>
#include <QPushButton>
#include <QFile>
#include <QVBoxLayout>

class SettingsWidget : public QWidget {
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent = nullptr);

    ~SettingsWidget() override;

    void updateRendering() const;

signals:
    void returnBtnClicked();

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *topLayout;
    QLabel *titleLabel;
    QLabel *subTitleLabel;
    QLabel *difficultyLabel;
    QLabel *modeLabel;
    QLabel *levelLabel;
    QLabel *scoreLabel;
    QVBoxLayout *buttonLayout;
    QPushButton *exportBtn;
    QPushButton *importBtn;
    QPushButton *resetBtn;
    QHBoxLayout *returnLayout;
    QPushButton *returnBtn;
};

#endif // SETTINGS_H
