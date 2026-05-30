#ifndef MENU_H
#define MENU_H

#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QFile>

class MenuWidget : public QWidget {
    Q_OBJECT

public:
    explicit MenuWidget(QWidget *parent = nullptr);

    ~MenuWidget() override;

signals:
    void startBtnClicked();

    void settingsBtnClicked();

private:
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QLabel *subTitleLabel;
    QVBoxLayout *buttonLayout;
    QPushButton *startBtn;
    QPushButton *settingsBtn;
    QPushButton *aboutBtn;
    QPushButton *aboutQtBtn;
};

#endif // MENU_H
