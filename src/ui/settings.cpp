#include "settings.h"

#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>

#include "../core/dictionary.h"
#include "../core/data.h"

SettingsWidget::SettingsWidget(QWidget *parent)
    : QWidget{parent} {
    // 使背景样式生效
    setAttribute(Qt::WA_StyledBackground, true);

    // 垂直布局
    mainLayout = new QVBoxLayout(this);

    // 空白
    mainLayout->addStretch(1);

    // 标题部分
    titleLabel = new QLabel("设置");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName("titleLabel");
    mainLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);

    // 标题部分
    subTitleLabel = new QLabel(QString("当前词典: %1").arg(DictionaryManager::getInstance().getDictName()));
    subTitleLabel->setAlignment(Qt::AlignCenter);
    subTitleLabel->setObjectName("subTitleLabel");
    mainLayout->addWidget(subTitleLabel, 0, Qt::AlignHCenter);

    // 空白
    mainLayout->addStretch(1);

    // 按钮部分
    buttonLayout = new QVBoxLayout;
    buttonLayout->setAlignment(Qt::AlignHCenter);

    exportBtn = new QPushButton("导出字典");
    importBtn = new QPushButton("导入字典");
    resetBtn = new QPushButton("重置数据");

    buttonLayout->addWidget(exportBtn);
    buttonLayout->addWidget(importBtn);
    buttonLayout->addWidget(resetBtn);

    // 导出字典
    connect(exportBtn, &QPushButton::clicked, this, [=]() {
        QFile jsonFile("./config/dictionary.json");

        if (!jsonFile.exists()) {
            // 文件不存在
            qWarning("Failed to load dictionary.json. Does it exist?");
            return;
        }

        // 让用户选择导出目录
        const QString dictName = DictionaryManager::getInstance().getDictName();

        QString targetPath = QFileDialog::getSaveFileName(
            this,
            "导出字典",
            QString("./%1.json").arg(dictName),
            "Json 文件 (*.json)"
            );

        if (targetPath.isEmpty()) {
            // 用户取消
            return;
        }

        // 确保文件名以 .json 结尾
        if (!targetPath.endsWith(".json", Qt::CaseInsensitive)) {
            targetPath += ".json";
        }

        // 检查是否存在同名文件
        if (QFile::exists(targetPath)) {
            const QMessageBox::StandardButton result = QMessageBox::question(
                this,
                "文件已存在",
                "目标路径下存在同名文件，是否覆盖？",
                QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No)
                );

            // 用户选择否，不覆盖文件
            if (result == QMessageBox::No) {
                return;
            }

            // 尝试删除已有文件
            if (!QFile::remove(targetPath)) {
                QMessageBox::warning(this, "导出失败", "无法覆盖原有文件，请检查权限！");
                return;
            }
        }

        // 复制文件
        if (jsonFile.copy(targetPath)) {
            QMessageBox::information(this, "导出成功", QString("已成功导出到：%1").arg(targetPath));
        } else {
            QMessageBox::warning(this, "导出失败", "复制文件失败，请检查权限或磁盘空间。");
        }
    });

    // 导入字典
    connect(importBtn, &QPushButton::clicked, this, [=]() {
        // 用户选择字典文件
        const QString sourcePath = QFileDialog::getOpenFileName(
            this,
            "选择词典文件",
            QString(),
            "Json 文件 (*.json)"
                );

        if (sourcePath.isEmpty()) {
            // 用户取消
            return;
        }

        const QString targetPath = "./config/dictionary.json";

        // 删除原有字典文件
        if (QFile::exists(targetPath)) {
            if (!QFile::remove(targetPath)) {
                QMessageBox::warning(this, "导入失败", "无法删除原有词典文件，请检查权限！");
                return;
            }
        }

        // 复制文件
        if (QFile::copy(sourcePath, targetPath)) {
            QMessageBox::information(this, "导入成功", "导入成功！");
        } else {
            QMessageBox::warning(this, "导入失败", "复制文件失败，请检查磁盘空间或权限。");
        }

        DictionaryManager::getInstance().loadFromJson(targetPath);
        Data::getInstance().resetShuffleFlag();
        updateRendering();
    });

    // 重置数据
    connect(resetBtn, &QPushButton::clicked, this, [=]() {
        const QMessageBox::StandardButton result = QMessageBox::warning(
            this,
            "重置数据",
            "你确定要重置所有数据吗？",
            QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No)
            );

        if (result == QMessageBox::Yes) {
            // 调用 Data 类中的 reset
            Data::getInstance().reset();

            QMessageBox::information(
            this,
            "重置数据",
            "重置成功！",
            QMessageBox::Ok
            );
        }
    });

    mainLayout->addLayout(buttonLayout);

    // 空白
    mainLayout->addStretch(1);

    // 返回按钮部分
    returnLayout = new QHBoxLayout;
    returnLayout->addStretch(1);

    returnBtn = new QPushButton("返回");
    returnLayout->addWidget(returnBtn);

    connect(returnBtn, &QPushButton::clicked, this, &SettingsWidget::returnBtnClicked);

    mainLayout->addLayout(returnLayout);
}

SettingsWidget::~SettingsWidget() = default;

void SettingsWidget::updateRendering() const {
    subTitleLabel->setText(QString("当前词典: %1").arg(DictionaryManager::getInstance().getDictName()));
}
