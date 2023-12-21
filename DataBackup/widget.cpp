#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

// 添加待备份文件（一份或多份）
void Widget::on_addFileButton_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "选择一个或多个文件", "/home", "所有文件 (*.*)");
    for (const auto& file : files) {
        // 去重
        bool duplication = false;
        for (int i = 0; i < ui->backUpFileList->topLevelItemCount(); ++i) {
            if (ui->backUpFileList->topLevelItem(i)->text(1) == file) {
                duplication = true;
                break;
            }
        }
        if (duplication) continue;

        // 将文件名以及其路径显示在BackUpFileList中
        QTreeWidgetItem* fileItem = new QTreeWidgetItem;
        fileItem->setText(0, QFileInfo(file).fileName());
        fileItem->setText(1, file);
        ui->backUpFileList->addTopLevelItem(fileItem);
    }
    if (!ui->backUpFileList->currentItem() && ui->backUpFileList->topLevelItemCount()) {
        ui->backUpFileList->setCurrentItem(ui->backUpFileList->topLevelItem(0));
    }
}

// 添加待备份的目录
void Widget::on_addDirButton_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("选择一个需要备份的文件夹"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (directory != "") {
        // 去重
        for (int i = 0; i < ui->backUpFileList->topLevelItemCount(); ++i) {
            if (ui->backUpFileList->topLevelItem(i)->text(1) == directory) return;
        }

        // 将目录名和具体路径显示出来
        QTreeWidgetItem* fileItem = new QTreeWidgetItem;
        fileItem->setText(0, QFileInfo(directory).fileName());
        fileItem->setText(1, directory);
        ui->backUpFileList->addTopLevelItem(fileItem);
    }
    if (!ui->backUpFileList->currentItem() && ui->backUpFileList->topLevelItemCount()) {
        ui->backUpFileList->setCurrentItem(ui->backUpFileList->topLevelItem(0));
    }
}

// 删除某份待备份的文件
void Widget::on_deleteFileButton_clicked()
{
    if (ui->backUpFileList->currentItem()) {
        delete ui->backUpFileList->currentItem();
    }
}

// 清空待备份文件列表
void Widget::on_clearFileButton_clicked()
{
    while (ui->backUpFileList->currentItem()) {
        delete ui->backUpFileList->currentItem();
    }
}

void Widget::on_backUpButton_clicked()
{
    // 没有需要备份的文件
    if (!ui->backUpFileList->topLevelItemCount()) {
        QMessageBox::information(this, "提示", "请添加需要备份的文件。", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    // 没有定义备份文件名
    if (ui->fileNameLineEdit->text().trimmed() == "") {
        QMessageBox::information(this, "提示", "请输入备份后的文件名。", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    // 文件名不合法
    std::regex filenameExpress("[\\/:*?\"<>|]");
    if (std::regex_search(ui->fileNameLineEdit->text().toStdString(), filenameExpress)) {
        QMessageBox::information(this, "提示", "请输入合法的备份文件名。", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    // 勾选加密复选框但未输入密码
    if (ui->encodeCheckBox->isChecked() && ui->keyWordLineEdit->text().trimmed() == "") {
        QMessageBox::information(this, "提示", "请输入密码。", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    QStringList files;
    for (int i = 0; i < ui->backUpFileList->topLevelItemCount(); ++i) {
        files.append(ui->backUpFileList->topLevelItem(i)->text(1));
    }
    QString desTar = ui->fileNameLineEdit->text()+".tar";
    int errorCode = BackUp::backup(files, desTar, ui->encodeCheckBox->isChecked(), ui->keyWordLineEdit->text().toStdString());
    QStringList message = {"备份成功", "tar文件的目标文件打开失败", "打开源文件失败", "源文件扩展名不是bak", "打开tar源文件失败", "打开目标文件失败"};
    QMessageBox::information(this, "提示", message[errorCode], QMessageBox::Yes, QMessageBox::Yes);
}

void Widget::on_deleteStoredFileButton_clicked()
{

}

void Widget::on_viewRestoreFilePathButton_clicked()
{

}

void Widget::on_restoreFileButton_clicked()
{

}

void Widget::on_keyWordRestoreCheckBox_stateChanged(int arg1)
{

}

// 使加密复选框和密码编辑框互斥
void Widget::on_encodeCheckBox_stateChanged(int arg1)
{
    ui->keyWordLineEdit->setEnabled(ui->encodeCheckBox->checkState());
}

// 修改文件备份目标路径
void Widget::on_changeDesPath_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("备份目的路径"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (directory != "") {
        ui->restorePathLineEdit->setText(directory);
        ConfigManager::updateDesPath(directory);
    }
}
