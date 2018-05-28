/********************************************************************************
** Form generated from reading UI file 'ChUpdateWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHUPDATEWIDGET_H
#define UI_CHUPDATEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChUpdateWidgetClass
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditFile;
    QPushButton *btnScan;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLabel *lbDevInfo;
    QProgressBar *progressBar;
    QTextBrowser *textBrowMsg;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnUpdate;
    QPushButton *btnConnect;

    void setupUi(QWidget *ChUpdateWidgetClass)
    {
        if (ChUpdateWidgetClass->objectName().isEmpty())
            ChUpdateWidgetClass->setObjectName(QStringLiteral("ChUpdateWidgetClass"));
        ChUpdateWidgetClass->resize(600, 400);
        verticalLayout = new QVBoxLayout(ChUpdateWidgetClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(ChUpdateWidgetClass);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEditFile = new QLineEdit(ChUpdateWidgetClass);
        lineEditFile->setObjectName(QStringLiteral("lineEditFile"));

        horizontalLayout->addWidget(lineEditFile);

        btnScan = new QPushButton(ChUpdateWidgetClass);
        btnScan->setObjectName(QStringLiteral("btnScan"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnScan->sizePolicy().hasHeightForWidth());
        btnScan->setSizePolicy(sizePolicy);
        btnScan->setMinimumSize(QSize(50, 23));
        btnScan->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(btnScan);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(ChUpdateWidgetClass);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_2);

        lbDevInfo = new QLabel(ChUpdateWidgetClass);
        lbDevInfo->setObjectName(QStringLiteral("lbDevInfo"));

        horizontalLayout_3->addWidget(lbDevInfo);


        verticalLayout->addLayout(horizontalLayout_3);

        progressBar = new QProgressBar(ChUpdateWidgetClass);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setStyleSheet(QLatin1String(" QProgressBar {\n"
"	  height: 20px;\n"
"      border: 1px solid grey;\n"
"      border-radius:10px;\n"
"      text-align: center;\n"
"  }"));
        progressBar->setValue(0);
        progressBar->setTextVisible(true);

        verticalLayout->addWidget(progressBar);

        textBrowMsg = new QTextBrowser(ChUpdateWidgetClass);
        textBrowMsg->setObjectName(QStringLiteral("textBrowMsg"));

        verticalLayout->addWidget(textBrowMsg);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btnUpdate = new QPushButton(ChUpdateWidgetClass);
        btnUpdate->setObjectName(QStringLiteral("btnUpdate"));

        horizontalLayout_2->addWidget(btnUpdate);

        btnConnect = new QPushButton(ChUpdateWidgetClass);
        btnConnect->setObjectName(QStringLiteral("btnConnect"));

        horizontalLayout_2->addWidget(btnConnect);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(ChUpdateWidgetClass);

        QMetaObject::connectSlotsByName(ChUpdateWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *ChUpdateWidgetClass)
    {
        ChUpdateWidgetClass->setWindowTitle(QApplication::translate("ChUpdateWidgetClass", "CUpdateWidget", Q_NULLPTR));
        label->setText(QApplication::translate("ChUpdateWidgetClass", "\351\200\211\346\213\251\346\226\207\344\273\266:", Q_NULLPTR));
        btnScan->setText(QApplication::translate("ChUpdateWidgetClass", "\346\265\217\350\247\210...", Q_NULLPTR));
        label_2->setText(QApplication::translate("ChUpdateWidgetClass", "\345\233\272\344\273\266\347\211\210\346\234\254:", Q_NULLPTR));
        lbDevInfo->setText(QString());
        btnUpdate->setText(QApplication::translate("ChUpdateWidgetClass", "\345\215\207\347\272\247", Q_NULLPTR));
        btnConnect->setText(QApplication::translate("ChUpdateWidgetClass", "\350\277\236\346\216\245", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ChUpdateWidgetClass: public Ui_ChUpdateWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHUPDATEWIDGET_H
