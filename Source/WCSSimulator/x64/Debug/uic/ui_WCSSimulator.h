/********************************************************************************
** Form generated from reading UI file 'WCSSimulator.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WCSSIMULATOR_H
#define UI_WCSSIMULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WCSSimulatorClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditAddress;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *tableWidget_4;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *tableWidget_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableWidget_2;

    void setupUi(QMainWindow *WCSSimulatorClass)
    {
        if (WCSSimulatorClass->objectName().isEmpty())
            WCSSimulatorClass->setObjectName(QString::fromUtf8("WCSSimulatorClass"));
        WCSSimulatorClass->resize(1024, 720);
        WCSSimulatorClass->setMinimumSize(QSize(1024, 720));
        centralWidget = new QWidget(WCSSimulatorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEditAddress = new QLineEdit(centralWidget);
        lineEditAddress->setObjectName(QString::fromUtf8("lineEditAddress"));

        horizontalLayout->addWidget(lineEditAddress);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setAlignment(Qt::AlignCenter);
        verticalLayout_4 = new QVBoxLayout(groupBox_4);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        tableWidget_4 = new QTableWidget(groupBox_4);
        if (tableWidget_4->columnCount() < 9)
            tableWidget_4->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        tableWidget_4->setObjectName(QString::fromUtf8("tableWidget_4"));

        verticalLayout_4->addWidget(tableWidget_4);


        gridLayout_2->addWidget(groupBox_4, 2, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setAlignment(Qt::AlignCenter);
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        tableWidget_3 = new QTableWidget(groupBox_3);
        if (tableWidget_3->columnCount() < 3)
            tableWidget_3->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(2, __qtablewidgetitem11);
        tableWidget_3->setObjectName(QString::fromUtf8("tableWidget_3"));

        verticalLayout_3->addWidget(tableWidget_3);


        gridLayout->addWidget(groupBox_3, 0, 3, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setAlignment(Qt::AlignCenter);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableWidget = new QTableWidget(groupBox);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem15);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setAlignment(Qt::AlignCenter);
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tableWidget_2 = new QTableWidget(groupBox_2);
        if (tableWidget_2->columnCount() < 2)
            tableWidget_2->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem17);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));

        verticalLayout_2->addWidget(tableWidget_2);


        gridLayout->addWidget(groupBox_2, 0, 1, 1, 1);

        gridLayout->setColumnStretch(0, 2);

        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);

        WCSSimulatorClass->setCentralWidget(centralWidget);

        retranslateUi(WCSSimulatorClass);

        QMetaObject::connectSlotsByName(WCSSimulatorClass);
    } // setupUi

    void retranslateUi(QMainWindow *WCSSimulatorClass)
    {
        WCSSimulatorClass->setWindowTitle(QCoreApplication::translate("WCSSimulatorClass", "WCSSimulator", nullptr));
        label->setText(QCoreApplication::translate("WCSSimulatorClass", "\345\234\260\345\235\200\357\274\232", nullptr));
        pushButton->setText(QCoreApplication::translate("WCSSimulatorClass", "\347\233\221\345\220\254", nullptr));
        pushButton_2->setText(QCoreApplication::translate("WCSSimulatorClass", "\350\257\246\346\203\205", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("WCSSimulatorClass", "\350\256\242\345\215\225\344\277\241\346\201\257", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_4->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("WCSSimulatorClass", "\350\256\242\345\215\225\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_4->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("WCSSimulatorClass", "\346\211\230\347\233\230\347\240\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_4->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("WCSSimulatorClass", "\345\210\206\347\233\230\346\234\272", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_4->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("WCSSimulatorClass", "\345\210\206\346\213\243\345\217\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_4->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("WCSSimulatorClass", "\345\207\272\350\264\247\345\217\243", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_4->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("WCSSimulatorClass", "\346\211\247\350\241\214\350\200\205", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_4->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("WCSSimulatorClass", "\347\212\266\346\200\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_4->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("WCSSimulatorClass", "\344\270\213\345\215\225\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_4->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("WCSSimulatorClass", "\345\256\214\346\210\220\346\227\266\351\227\264", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("WCSSimulatorClass", "\345\207\272\350\264\247\345\217\243", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_3->horizontalHeaderItem(0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("WCSSimulatorClass", "\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_3->horizontalHeaderItem(1);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("WCSSimulatorClass", "\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_3->horizontalHeaderItem(2);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("WCSSimulatorClass", "\347\212\266\346\200\201", nullptr));
        groupBox->setTitle(QCoreApplication::translate("WCSSimulatorClass", "\345\210\206\347\233\230\346\234\272", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("WCSSimulatorClass", "\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("WCSSimulatorClass", "\345\234\260\345\235\200", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("WCSSimulatorClass", "\350\277\236\346\216\245", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("WCSSimulatorClass", "\347\212\266\346\200\201", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("WCSSimulatorClass", "\345\210\206\346\213\243\345\217\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("WCSSimulatorClass", "\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("WCSSimulatorClass", "\345\220\215\347\247\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WCSSimulatorClass: public Ui_WCSSimulatorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WCSSIMULATOR_H
