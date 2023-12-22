#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <configManager.h>
#include <backUp.h>
#include <restore.h>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <regex>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_addFileButton_clicked();

    void on_addDirButton_clicked();

    void on_deleteFileButton_clicked();

    void on_clearFileButton_clicked();

    void on_backUpButton_clicked();

    void on_deleteStoredFileButton_clicked();

    void on_viewRestoreFilePathButton_clicked();

    void on_restoreFileButton_clicked();

    void on_keyWordRestoreCheckBox_stateChanged(int arg1);

    void on_encodeCheckBox_stateChanged(int arg1);

    void on_changeDesPath_clicked();

    void on_updateRestoreFileButton_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
