#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("2023软工小组的备份软件");
    ui->backUpWidget->setTabText(0, "备份");
    ui->backUpWidget->setTabText(1, "恢复");
    ui->backUpWidget->setTabText(2, "配置");
    ui->backUpWidget->setTabToolTip(0,"备份重要的文件");
    ui->backUpWidget->setTabToolTip(1,"恢复已备份的文件");
    ui->backUpWidget->setTabToolTip(2,"修改备份目标路径");
    ui->backUpWidget->setMovable(true);

    ui->keyWordRestoreLineEdit->setEnabled(false);
    ui->keyWordLineEdit->setEnabled(false);
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

// 备份功能
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

// 更新需恢复文件显示列表
void Widget::on_updateRestoreFileButton_clicked()
{
    QString filePath = ConfigManager::getDesPath();
    QDirIterator iter(filePath, QDirIterator::Subdirectories);
    // 迭代遍历备份路径下所有文件，将其去重后加入列表
    while (iter.hasNext()) {
        iter.next();
        QFileInfo info = iter.fileInfo();

        if (info.fileName() == ".." || info.fileName() == ".") continue;

        // 去重
        bool duplication = false;
        for (int i = 0; i < ui->restoreFileList->topLevelItemCount(); ++i) {
            if (ui->restoreFileList->topLevelItem(i)->text(0) == QFileInfo(info).fileName()) {
                duplication = true;
                break;
            }
        }
        if (duplication) continue;

        QTreeWidgetItem* fileItem = new QTreeWidgetItem;
        fileItem->setText(0, QFileInfo(info).fileName());
        fileItem->setText(1, QString::number(QFileInfo(info).size()));
        fileItem->setText(2, QFileInfo(info).fileTime(QFileDevice::FileModificationTime).toString("yyyy-MM-dd ddd hh:mm:ss"));
        ui->restoreFileList->addTopLevelItem(fileItem);
    }
    if (!ui->restoreFileList->currentItem() && ui->restoreFileList->topLevelItemCount()) {
        ui->restoreFileList->setCurrentItem(ui->restoreFileList->topLevelItem(0));
    }
}

// 删除某个已备份的文件
void Widget::on_deleteStoredFileButton_clicked()
{
    if (ui->restoreFileList->currentItem()) {
        // 删除该文件
        QString filePath = ConfigManager::getDesPath() + "\\" + ui->restoreFileList->currentItem()->text(0);
        QFile currentFile(filePath);
        currentFile.remove();

        // 删去显示列表中该项
        delete ui->restoreFileList->currentItem();
    }
}

// 选择恢复路径
void Widget::on_viewRestoreFilePathButton_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("恢复到"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (directory != "") {
        ui->restorePathLineEdit->setText(directory);
    }
}

// 恢复功能
void Widget::on_restoreFileButton_clicked()
{
    if (!ui->restoreFileList->currentItem()) {
        QMessageBox::information(this, "提示", "请选择要恢复的备份文件。", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    if (ui->restorePathLineEdit->text().trimmed() == "") {
        QMessageBox::information(this, "提示", "请选择要恢复到的目录。", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    if (ui->keyWordRestoreCheckBox->isChecked() && ui->keyWordRestoreLineEdit->text().trimmed() == "") {
        QMessageBox::information(this, "提示", "请输入密码。", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    QString srcFilePath = ConfigManager::getDesPath() + "\\" + ui->restoreFileList->currentItem()->text(0);
    int errorCode = Restore::restore(srcFilePath, ui->restorePathLineEdit->text(), ui->keyWordRestoreCheckBox->isChecked(), ui->keyWordRestoreLineEdit->text());
    QStringList message = {"正常执行",  "源文件扩展名不是bak", "打开.bak源文件失败",
                           "打开目标路径失败", ".bak文件过短，频率表不完整，解压失败", ".bak文件结尾不完整，解压失败",
                           "密码错误", "解码错误", ".tar文件打开失败", "打开目标路径失败", "创建目录失败"};
    QMessageBox::information(this, "提示", message[errorCode], QMessageBox::Yes, QMessageBox::Yes);
}

// 只有在restore区密码复选框勾选后才能编辑密码框
void Widget::on_keyWordRestoreCheckBox_stateChanged(int arg1)
{
    ui->keyWordRestoreLineEdit->setEnabled(ui->keyWordRestoreCheckBox->checkState());
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


