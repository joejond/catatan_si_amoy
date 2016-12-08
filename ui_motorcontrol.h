/********************************************************************************
** Form generated from reading UI file 'motorcontrol.ui'
**
** Created: Thu Aug 29 12:14:04 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOTORCONTROL_H
#define UI_MOTORCONTROL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MotorControl
{
public:
    QGridLayout *gridLayout;
    QCheckBox *chk_motor_enable;
    QLabel *label;
    QComboBox *cb_port;
    QLabel *label_2;
    QVBoxLayout *verticalLayout;
    QRadioButton *rb_motor_fw;
    QRadioButton *rb_motor_rev;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pb_motor_start;
    QPushButton *pb_motor_stop;
    QFrame *line;
    QFrame *line_2;

    void setupUi(QWidget *MotorControl)
    {
        if (MotorControl->objectName().isEmpty())
            MotorControl->setObjectName(QString::fromUtf8("MotorControl"));
        MotorControl->resize(196, 207);
        gridLayout = new QGridLayout(MotorControl);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        chk_motor_enable = new QCheckBox(MotorControl);
        chk_motor_enable->setObjectName(QString::fromUtf8("chk_motor_enable"));

        gridLayout->addWidget(chk_motor_enable, 0, 0, 1, 2);

        label = new QLabel(MotorControl);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        cb_port = new QComboBox(MotorControl);
        cb_port->setObjectName(QString::fromUtf8("cb_port"));

        gridLayout->addWidget(cb_port, 2, 1, 1, 1);

        label_2 = new QLabel(MotorControl);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        rb_motor_fw = new QRadioButton(MotorControl);
        rb_motor_fw->setObjectName(QString::fromUtf8("rb_motor_fw"));

        verticalLayout->addWidget(rb_motor_fw);

        rb_motor_rev = new QRadioButton(MotorControl);
        rb_motor_rev->setObjectName(QString::fromUtf8("rb_motor_rev"));

        verticalLayout->addWidget(rb_motor_rev);


        gridLayout->addLayout(verticalLayout, 3, 1, 1, 1);

        label_3 = new QLabel(MotorControl);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        comboBox = new QComboBox(MotorControl);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        label_4 = new QLabel(MotorControl);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);


        gridLayout->addLayout(horizontalLayout, 4, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pb_motor_start = new QPushButton(MotorControl);
        pb_motor_start->setObjectName(QString::fromUtf8("pb_motor_start"));

        horizontalLayout_2->addWidget(pb_motor_start);

        pb_motor_stop = new QPushButton(MotorControl);
        pb_motor_stop->setObjectName(QString::fromUtf8("pb_motor_stop"));

        horizontalLayout_2->addWidget(pb_motor_stop);


        gridLayout->addLayout(horizontalLayout_2, 6, 0, 1, 2);

        line = new QFrame(MotorControl);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 5, 0, 1, 2);

        line_2 = new QFrame(MotorControl);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 1, 0, 1, 2);


        retranslateUi(MotorControl);

        QMetaObject::connectSlotsByName(MotorControl);
    } // setupUi

    void retranslateUi(QWidget *MotorControl)
    {
        MotorControl->setWindowTitle(QApplication::translate("MotorControl", "Form", 0, QApplication::UnicodeUTF8));
        chk_motor_enable->setText(QApplication::translate("MotorControl", "Enable motor control", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MotorControl", "Port :", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MotorControl", "Direction :", 0, QApplication::UnicodeUTF8));
        rb_motor_fw->setText(QApplication::translate("MotorControl", "Foreward", 0, QApplication::UnicodeUTF8));
        rb_motor_rev->setText(QApplication::translate("MotorControl", "Reverse", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MotorControl", "Speed", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MotorControl", "0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MotorControl", "300", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MotorControl", "600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MotorControl", "900", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MotorControl", "1200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MotorControl", "1500", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MotorControl", "1800", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MotorControl", "2100", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MotorControl", "2400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MotorControl", "2700", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MotorControl", "3000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MotorControl", "3300", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MotorControl", "3600", 0, QApplication::UnicodeUTF8)
        );
        label_4->setText(QApplication::translate("MotorControl", "rpm", 0, QApplication::UnicodeUTF8));
        pb_motor_start->setText(QApplication::translate("MotorControl", "START", 0, QApplication::UnicodeUTF8));
        pb_motor_stop->setText(QApplication::translate("MotorControl", "STOP", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MotorControl: public Ui_MotorControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOTORCONTROL_H
