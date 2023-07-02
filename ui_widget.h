/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QFrame *line;
    QPushButton *blackfirst;
    QPushButton *whitefirst;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QLabel *blacktime;
    QWidget *widget;
    QPushButton *blackcancel;
    QPushButton *blackok;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_2;
    QLabel *whitetime;
    QPushButton *whiteok;
    QPushButton *whitecancel;
    QPushButton *save;
    QLabel *di;
    QLabel *wo;
    QPushButton *esc;
    QPushButton *backstep;
    QGroupBox *groupBox_3;
    QTextBrowser *textBrowser;
    QWidget *horizontalLayoutWidget;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_7;
    QLabel *label_6;
    QLabel *label_5;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label_3;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(761, 605);
        line = new QFrame(Widget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(290, 10, 91, 301));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        blackfirst = new QPushButton(Widget);
        blackfirst->setObjectName(QStringLiteral("blackfirst"));
        blackfirst->setGeometry(QRect(360, 10, 131, 51));
        whitefirst = new QPushButton(Widget);
        whitefirst->setObjectName(QStringLiteral("whitefirst"));
        whitefirst->setGeometry(QRect(510, 10, 131, 51));
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(360, 80, 361, 191));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        blacktime = new QLabel(groupBox);
        blacktime->setObjectName(QStringLiteral("blacktime"));

        verticalLayout->addWidget(blacktime);

        widget = new QWidget(groupBox);
        widget->setObjectName(QStringLiteral("widget"));
        blackcancel = new QPushButton(widget);
        blackcancel->setObjectName(QStringLiteral("blackcancel"));
        blackcancel->setGeometry(QRect(0, 40, 341, 31));
        blackok = new QPushButton(widget);
        blackok->setObjectName(QStringLiteral("blackok"));
        blackok->setGeometry(QRect(0, 0, 341, 31));

        verticalLayout->addWidget(widget);

        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(360, 280, 361, 221));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widget_2 = new QWidget(groupBox_2);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        whitetime = new QLabel(widget_2);
        whitetime->setObjectName(QStringLiteral("whitetime"));
        whitetime->setGeometry(QRect(10, 10, 321, 81));
        whiteok = new QPushButton(widget_2);
        whiteok->setObjectName(QStringLiteral("whiteok"));
        whiteok->setGeometry(QRect(0, 100, 341, 31));
        whitecancel = new QPushButton(widget_2);
        whitecancel->setObjectName(QStringLiteral("whitecancel"));
        whitecancel->setGeometry(QRect(0, 140, 341, 31));

        verticalLayout_2->addWidget(widget_2);

        save = new QPushButton(Widget);
        save->setObjectName(QStringLiteral("save"));
        save->setGeometry(QRect(420, 530, 111, 31));
        di = new QLabel(Widget);
        di->setObjectName(QStringLiteral("di"));
        di->setGeometry(QRect(30, 10, 131, 21));
        wo = new QLabel(Widget);
        wo->setObjectName(QStringLiteral("wo"));
        wo->setGeometry(QRect(180, 10, 141, 21));
        esc = new QPushButton(Widget);
        esc->setObjectName(QStringLiteral("esc"));
        esc->setGeometry(QRect(560, 530, 111, 31));
        backstep = new QPushButton(Widget);
        backstep->setObjectName(QStringLiteral("backstep"));
        backstep->setGeometry(QRect(660, 10, 81, 51));
        groupBox_3 = new QGroupBox(Widget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 340, 331, 281));
        textBrowser = new QTextBrowser(groupBox_3);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(10, 30, 311, 241));
        horizontalLayoutWidget = new QWidget(Widget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 30, 20, 291));
        verticalLayout_4 = new QVBoxLayout(horizontalLayoutWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(horizontalLayoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_4->addWidget(label_7);

        label_6 = new QLabel(horizontalLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_4->addWidget(label_6);

        label_5 = new QLabel(horizontalLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_4->addWidget(label_5);

        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_4->addWidget(label_4);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_4->addWidget(label_2);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_4->addWidget(label_3);

        horizontalLayoutWidget_2 = new QWidget(Widget);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(40, 310, 301, 20));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        label_8 = new QLabel(horizontalLayoutWidget_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout->addWidget(label_8);

        label_9 = new QLabel(horizontalLayoutWidget_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout->addWidget(label_9);

        label_10 = new QLabel(horizontalLayoutWidget_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout->addWidget(label_10);

        label_11 = new QLabel(horizontalLayoutWidget_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout->addWidget(label_11);

        label_12 = new QLabel(horizontalLayoutWidget_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout->addWidget(label_12);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        blackfirst->setText(QApplication::translate("Widget", "\346\225\214\346\226\271\345\205\210\346\211\213", Q_NULLPTR));
        whitefirst->setText(QApplication::translate("Widget", "\346\210\221\346\226\271\345\205\210\346\211\213 ", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Widget", "\346\225\214\346\226\271", Q_NULLPTR));
        blacktime->setText(QString());
        blackcancel->setText(QApplication::translate("Widget", "CANCEL", Q_NULLPTR));
        blackok->setText(QApplication::translate("Widget", "OK", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("Widget", "\346\210\221\346\226\271", Q_NULLPTR));
        whitetime->setText(QString());
        whiteok->setText(QApplication::translate("Widget", "OK", Q_NULLPTR));
        whitecancel->setText(QApplication::translate("Widget", "CANCEL", Q_NULLPTR));
        save->setText(QApplication::translate("Widget", "\344\277\235\345\255\230", Q_NULLPTR));
        di->setText(QApplication::translate("Widget", "TextLabel", Q_NULLPTR));
        wo->setText(QApplication::translate("Widget", "TextLabel", Q_NULLPTR));
        esc->setText(QApplication::translate("Widget", "\351\200\200\345\207\272", Q_NULLPTR));
        backstep->setText(QApplication::translate("Widget", "\346\202\224\346\243\213", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("Widget", "\346\255\245\351\252\244\346\230\276\347\244\272", Q_NULLPTR));
        textBrowser->setHtml(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun';\"><br /></p></body></html>", Q_NULLPTR));
        label_7->setText(QApplication::translate("Widget", "6", Q_NULLPTR));
        label_6->setText(QApplication::translate("Widget", "5", Q_NULLPTR));
        label_5->setText(QApplication::translate("Widget", "4", Q_NULLPTR));
        label_4->setText(QApplication::translate("Widget", "3", Q_NULLPTR));
        label_2->setText(QApplication::translate("Widget", "2", Q_NULLPTR));
        label_3->setText(QApplication::translate("Widget", "1", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "A", Q_NULLPTR));
        label_8->setText(QApplication::translate("Widget", "B", Q_NULLPTR));
        label_9->setText(QApplication::translate("Widget", "C", Q_NULLPTR));
        label_10->setText(QApplication::translate("Widget", "D", Q_NULLPTR));
        label_11->setText(QApplication::translate("Widget", "E", Q_NULLPTR));
        label_12->setText(QApplication::translate("Widget", "F", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
