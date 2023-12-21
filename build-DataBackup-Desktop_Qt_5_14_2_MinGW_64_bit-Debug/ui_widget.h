/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTabWidget *backUpWidget;
    QWidget *backUp;
    QLabel *label;
    QTreeWidget *backUpFileList;
    QPushButton *backUpButton;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *addFileButton;
    QPushButton *addDirButton;
    QPushButton *deleteFileButton;
    QPushButton *clearFileButton;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *encodeCheckBox;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    QLineEdit *keyWordLineEdit;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *fileNameLineEdit;
    QWidget *restore;
    QTreeWidget *restoreFileList;
    QLabel *label_4;
    QPushButton *deleteStoredFileButton;
    QWidget *widget3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QLineEdit *restorePathLineEdit;
    QPushButton *viewRestoreFilePathButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *restoreFileButton;
    QWidget *widget4;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *keyWordRestoreCheckBox;
    QLineEdit *keyWordRestoreLineEdit;
    QWidget *config;
    QWidget *widget5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QLineEdit *desPathLineEdit;
    QPushButton *changeDesPath;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        backUpWidget = new QTabWidget(Widget);
        backUpWidget->setObjectName(QString::fromUtf8("backUpWidget"));
        backUpWidget->setGeometry(QRect(10, 0, 794, 591));
        backUp = new QWidget();
        backUp->setObjectName(QString::fromUtf8("backUp"));
        label = new QLabel(backUp);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 161, 31));
        backUpFileList = new QTreeWidget(backUp);
        backUpFileList->setObjectName(QString::fromUtf8("backUpFileList"));
        backUpFileList->setGeometry(QRect(20, 40, 741, 321));
        backUpButton = new QPushButton(backUp);
        backUpButton->setObjectName(QString::fromUtf8("backUpButton"));
        backUpButton->setGeometry(QRect(650, 540, 80, 20));
        widget = new QWidget(backUp);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(15, 371, 741, 41));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        addFileButton = new QPushButton(widget);
        addFileButton->setObjectName(QString::fromUtf8("addFileButton"));

        horizontalLayout->addWidget(addFileButton);

        addDirButton = new QPushButton(widget);
        addDirButton->setObjectName(QString::fromUtf8("addDirButton"));

        horizontalLayout->addWidget(addDirButton);

        deleteFileButton = new QPushButton(widget);
        deleteFileButton->setObjectName(QString::fromUtf8("deleteFileButton"));

        horizontalLayout->addWidget(deleteFileButton);

        clearFileButton = new QPushButton(widget);
        clearFileButton->setObjectName(QString::fromUtf8("clearFileButton"));

        horizontalLayout->addWidget(clearFileButton);

        widget1 = new QWidget(backUp);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(20, 480, 741, 51));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        encodeCheckBox = new QCheckBox(widget1);
        encodeCheckBox->setObjectName(QString::fromUtf8("encodeCheckBox"));

        horizontalLayout_2->addWidget(encodeCheckBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label_3 = new QLabel(widget1);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        keyWordLineEdit = new QLineEdit(widget1);
        keyWordLineEdit->setObjectName(QString::fromUtf8("keyWordLineEdit"));

        horizontalLayout_2->addWidget(keyWordLineEdit);

        widget2 = new QWidget(backUp);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(20, 430, 581, 41));
        horizontalLayout_3 = new QHBoxLayout(widget2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        fileNameLineEdit = new QLineEdit(widget2);
        fileNameLineEdit->setObjectName(QString::fromUtf8("fileNameLineEdit"));

        horizontalLayout_3->addWidget(fileNameLineEdit);

        backUpWidget->addTab(backUp, QString());
        restore = new QWidget();
        restore->setObjectName(QString::fromUtf8("restore"));
        restoreFileList = new QTreeWidget(restore);
        restoreFileList->setObjectName(QString::fromUtf8("restoreFileList"));
        restoreFileList->setGeometry(QRect(20, 41, 741, 291));
        label_4 = new QLabel(restore);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 10, 171, 31));
        deleteStoredFileButton = new QPushButton(restore);
        deleteStoredFileButton->setObjectName(QString::fromUtf8("deleteStoredFileButton"));
        deleteStoredFileButton->setGeometry(QRect(670, 350, 91, 21));
        widget3 = new QWidget(restore);
        widget3->setObjectName(QString::fromUtf8("widget3"));
        widget3->setGeometry(QRect(20, 390, 741, 71));
        horizontalLayout_4 = new QHBoxLayout(widget3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(widget3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_4->addWidget(label_5);

        restorePathLineEdit = new QLineEdit(widget3);
        restorePathLineEdit->setObjectName(QString::fromUtf8("restorePathLineEdit"));

        horizontalLayout_4->addWidget(restorePathLineEdit);

        viewRestoreFilePathButton = new QPushButton(widget3);
        viewRestoreFilePathButton->setObjectName(QString::fromUtf8("viewRestoreFilePathButton"));

        horizontalLayout_4->addWidget(viewRestoreFilePathButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        restoreFileButton = new QPushButton(widget3);
        restoreFileButton->setObjectName(QString::fromUtf8("restoreFileButton"));

        horizontalLayout_4->addWidget(restoreFileButton);

        widget4 = new QWidget(restore);
        widget4->setObjectName(QString::fromUtf8("widget4"));
        widget4->setGeometry(QRect(20, 480, 561, 61));
        horizontalLayout_5 = new QHBoxLayout(widget4);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        keyWordRestoreCheckBox = new QCheckBox(widget4);
        keyWordRestoreCheckBox->setObjectName(QString::fromUtf8("keyWordRestoreCheckBox"));

        horizontalLayout_5->addWidget(keyWordRestoreCheckBox);

        keyWordRestoreLineEdit = new QLineEdit(widget4);
        keyWordRestoreLineEdit->setObjectName(QString::fromUtf8("keyWordRestoreLineEdit"));

        horizontalLayout_5->addWidget(keyWordRestoreLineEdit);

        backUpWidget->addTab(restore, QString());
        config = new QWidget();
        config->setObjectName(QString::fromUtf8("config"));
        widget5 = new QWidget(config);
        widget5->setObjectName(QString::fromUtf8("widget5"));
        widget5->setGeometry(QRect(30, 50, 711, 24));
        horizontalLayout_6 = new QHBoxLayout(widget5);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(widget5);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_6->addWidget(label_6);

        desPathLineEdit = new QLineEdit(widget5);
        desPathLineEdit->setObjectName(QString::fromUtf8("desPathLineEdit"));

        horizontalLayout_6->addWidget(desPathLineEdit);

        changeDesPath = new QPushButton(widget5);
        changeDesPath->setObjectName(QString::fromUtf8("changeDesPath"));

        horizontalLayout_6->addWidget(changeDesPath);

        backUpWidget->addTab(config, QString());

        retranslateUi(Widget);

        backUpWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
#if QT_CONFIG(tooltip)
        backUpWidget->setToolTip(QCoreApplication::translate("Widget", "<html><head/><body><p>\345\244\207\344\273\275</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        backUpWidget->setWhatsThis(QCoreApplication::translate("Widget", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        label->setText(QCoreApplication::translate("Widget", " \345\276\205\345\244\207\344\273\275\346\226\207\344\273\266\345\210\227\350\241\250:", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = backUpFileList->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("Widget", "\346\226\207\344\273\266\350\267\257\345\276\204", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("Widget", "\346\226\207\344\273\266\345\220\215", nullptr));
        backUpButton->setText(QCoreApplication::translate("Widget", " \345\244\207\344\273\275", nullptr));
        addFileButton->setText(QCoreApplication::translate("Widget", "\346\267\273\345\212\240\346\226\207\344\273\266", nullptr));
        addDirButton->setText(QCoreApplication::translate("Widget", "\346\267\273\345\212\240\347\233\256\345\275\225", nullptr));
        deleteFileButton->setText(QCoreApplication::translate("Widget", "\345\210\240\351\231\244", nullptr));
        clearFileButton->setText(QCoreApplication::translate("Widget", "  \346\270\205\347\251\272", nullptr));
        encodeCheckBox->setText(QCoreApplication::translate("Widget", " \345\212\240\345\257\206", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"center\">\345\257\206\347\240\201\357\274\232</p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"center\">\345\244\207\344\273\275\346\226\207\344\273\266\345\220\215\357\274\232</p></body></html>", nullptr));
        backUpWidget->setTabText(backUpWidget->indexOf(backUp), QCoreApplication::translate("Widget", "Tab 1", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = restoreFileList->headerItem();
        ___qtreewidgetitem1->setText(3, QCoreApplication::translate("Widget", "\346\230\257\345\220\246\345\212\240\345\257\206", nullptr));
        ___qtreewidgetitem1->setText(2, QCoreApplication::translate("Widget", "\345\244\207\344\273\275\346\227\266\351\227\264", nullptr));
        ___qtreewidgetitem1->setText(1, QCoreApplication::translate("Widget", "\346\226\207\344\273\266\345\244\247\345\260\217", nullptr));
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("Widget", "\346\226\207\344\273\266\345\220\215", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "\345\276\205\346\201\242\345\244\215\346\226\207\344\273\266\345\210\227\350\241\250", nullptr));
        deleteStoredFileButton->setText(QCoreApplication::translate("Widget", " \345\210\240\351\231\244", nullptr));
        label_5->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"center\">\350\277\230\345\216\237\345\210\260\357\274\232</p></body></html>", nullptr));
        viewRestoreFilePathButton->setText(QCoreApplication::translate("Widget", "...", nullptr));
        restoreFileButton->setText(QCoreApplication::translate("Widget", "\346\201\242\345\244\215", nullptr));
        keyWordRestoreCheckBox->setText(QCoreApplication::translate("Widget", "\345\257\206\347\240\201", nullptr));
        backUpWidget->setTabText(backUpWidget->indexOf(restore), QCoreApplication::translate("Widget", "Tab 2", nullptr));
        label_6->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"center\">\346\225\260\346\215\256\345\244\207\344\273\275\350\267\257\345\276\204\357\274\232</p></body></html>", nullptr));
        changeDesPath->setText(QCoreApplication::translate("Widget", "\344\277\256\346\224\271", nullptr));
        backUpWidget->setTabText(backUpWidget->indexOf(config), QCoreApplication::translate("Widget", "\351\241\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
