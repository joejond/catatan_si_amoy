/********************************************************************************
** Form generated from reading UI file 'modulsetting.ui'
**
** Created: Thu Aug 29 15:00:02 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODULSETTING_H
#define UI_MODULSETTING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModulSetting
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *le_ip_modul;
    QFrame *line;
    QLabel *label_2;
    QCheckBox *chk_kanal1;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QCheckBox *chk_kanal2;
    QCheckBox *chk_kanal3;
    QCheckBox *chk_kanal4;
    QFrame *line_2;
    QCheckBox *chk_fasa_aktif;
    QLabel *label_6;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_7;
    QLineEdit *le_acc1;
    QLineEdit *le_acc2;
    QLineEdit *le_acc3;
    QLineEdit *le_acc4;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_8;
    QLabel *label_9;
    QComboBox *cb_lines;
    QComboBox *cb_fstop;
    QLabel *label_13;
    QLabel *label_15;
    QLabel *label_14;
    QLabel *labelSamplingRate;
    QLabel *labelDataCount;
    QLabel *labelETA;
    QLabel *label_10;
    QComboBox *cb_fstart;
    QHBoxLayout *horizontalLayout;
    QPushButton *pb_update_set_modul;

    void setupUi(QWidget *ModulSetting)
    {
        if (ModulSetting->objectName().isEmpty())
            ModulSetting->setObjectName(QString::fromUtf8("ModulSetting"));
        ModulSetting->resize(316, 501);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ModulSetting->sizePolicy().hasHeightForWidth());
        ModulSetting->setSizePolicy(sizePolicy);
        ModulSetting->setMinimumSize(QSize(0, 0));
        verticalLayout = new QVBoxLayout(ModulSetting);
        verticalLayout->setSpacing(3);
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        frame = new QFrame(ModulSetting);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 1, 1, 1);

        le_ip_modul = new QLineEdit(groupBox);
        le_ip_modul->setObjectName(QString::fromUtf8("le_ip_modul"));
        sizePolicy.setHeightForWidth(le_ip_modul->sizePolicy().hasHeightForWidth());
        le_ip_modul->setSizePolicy(sizePolicy);

        gridLayout->addWidget(le_ip_modul, 0, 2, 1, 1);

        line = new QFrame(groupBox);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 1, 1, 4);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 3, 1, 1, 1);

        chk_kanal1 = new QCheckBox(groupBox);
        chk_kanal1->setObjectName(QString::fromUtf8("chk_kanal1"));

        gridLayout->addWidget(chk_kanal1, 3, 2, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 5, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 6, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 7, 1, 1, 1);

        chk_kanal2 = new QCheckBox(groupBox);
        chk_kanal2->setObjectName(QString::fromUtf8("chk_kanal2"));

        gridLayout->addWidget(chk_kanal2, 5, 2, 1, 1);

        chk_kanal3 = new QCheckBox(groupBox);
        chk_kanal3->setObjectName(QString::fromUtf8("chk_kanal3"));

        gridLayout->addWidget(chk_kanal3, 6, 2, 1, 1);

        chk_kanal4 = new QCheckBox(groupBox);
        chk_kanal4->setObjectName(QString::fromUtf8("chk_kanal4"));

        gridLayout->addWidget(chk_kanal4, 7, 2, 1, 1);

        line_2 = new QFrame(groupBox);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 8, 1, 1, 4);

        chk_fasa_aktif = new QCheckBox(groupBox);
        chk_fasa_aktif->setObjectName(QString::fromUtf8("chk_fasa_aktif"));

        gridLayout->addWidget(chk_fasa_aktif, 11, 2, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 11, 1, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_11->setFont(font);

        gridLayout->addWidget(label_11, 2, 1, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font);

        gridLayout->addWidget(label_12, 2, 2, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);

        gridLayout->addWidget(label_7, 2, 3, 1, 1);

        le_acc1 = new QLineEdit(groupBox);
        le_acc1->setObjectName(QString::fromUtf8("le_acc1"));

        gridLayout->addWidget(le_acc1, 3, 3, 1, 1);

        le_acc2 = new QLineEdit(groupBox);
        le_acc2->setObjectName(QString::fromUtf8("le_acc2"));

        gridLayout->addWidget(le_acc2, 5, 3, 1, 1);

        le_acc3 = new QLineEdit(groupBox);
        le_acc3->setObjectName(QString::fromUtf8("le_acc3"));

        gridLayout->addWidget(le_acc3, 6, 3, 1, 1);

        le_acc4 = new QLineEdit(groupBox);
        le_acc4->setObjectName(QString::fromUtf8("le_acc4"));

        gridLayout->addWidget(le_acc4, 7, 3, 1, 1);


        verticalLayout_2->addWidget(groupBox);


        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(ModulSetting);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        frame_2->setFont(font1);
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox_2 = new QGroupBox(frame_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 1, 0, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 3, 0, 1, 1);

        cb_lines = new QComboBox(groupBox_2);
        cb_lines->setObjectName(QString::fromUtf8("cb_lines"));

        gridLayout_2->addWidget(cb_lines, 3, 1, 1, 1);

        cb_fstop = new QComboBox(groupBox_2);
        cb_fstop->setObjectName(QString::fromUtf8("cb_fstop"));

        gridLayout_2->addWidget(cb_fstop, 1, 1, 1, 1);

        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_2->addWidget(label_13, 4, 0, 1, 1);

        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_2->addWidget(label_15, 6, 0, 1, 1);

        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_2->addWidget(label_14, 5, 0, 1, 1);

        labelSamplingRate = new QLabel(groupBox_2);
        labelSamplingRate->setObjectName(QString::fromUtf8("labelSamplingRate"));

        gridLayout_2->addWidget(labelSamplingRate, 4, 1, 1, 1);

        labelDataCount = new QLabel(groupBox_2);
        labelDataCount->setObjectName(QString::fromUtf8("labelDataCount"));

        gridLayout_2->addWidget(labelDataCount, 5, 1, 1, 1);

        labelETA = new QLabel(groupBox_2);
        labelETA->setObjectName(QString::fromUtf8("labelETA"));

        gridLayout_2->addWidget(labelETA, 6, 1, 1, 1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 0, 0, 1, 1);

        cb_fstart = new QComboBox(groupBox_2);
        cb_fstart->setObjectName(QString::fromUtf8("cb_fstart"));

        gridLayout_2->addWidget(cb_fstart, 0, 1, 1, 1);

        gridLayout_2->setColumnStretch(0, 1);

        verticalLayout_3->addWidget(groupBox_2);


        verticalLayout->addWidget(frame_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(50, -1, 50, -1);
        pb_update_set_modul = new QPushButton(ModulSetting);
        pb_update_set_modul->setObjectName(QString::fromUtf8("pb_update_set_modul"));
        pb_update_set_modul->setMaximumSize(QSize(16777215, 16777215));
        pb_update_set_modul->setFont(font);

        horizontalLayout->addWidget(pb_update_set_modul);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(ModulSetting);

        QMetaObject::connectSlotsByName(ModulSetting);
    } // setupUi

    void retranslateUi(QWidget *ModulSetting)
    {
        ModulSetting->setWindowTitle(QApplication::translate("ModulSetting", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ModulSetting", "Setting modul :", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ModulSetting", "IP modul", 0, QApplication::UnicodeUTF8));
        le_ip_modul->setText(QApplication::translate("ModulSetting", "192.168.1.123", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ModulSetting", "kanal-1", 0, QApplication::UnicodeUTF8));
        chk_kanal1->setText(QApplication::translate("ModulSetting", "aktif", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ModulSetting", "kanal-2", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ModulSetting", "kanal-3", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ModulSetting", "kanal-4", 0, QApplication::UnicodeUTF8));
        chk_kanal2->setText(QApplication::translate("ModulSetting", "aktif", 0, QApplication::UnicodeUTF8));
        chk_kanal3->setText(QApplication::translate("ModulSetting", "aktif", 0, QApplication::UnicodeUTF8));
        chk_kanal4->setText(QApplication::translate("ModulSetting", "aktif", 0, QApplication::UnicodeUTF8));
        chk_fasa_aktif->setText(QApplication::translate("ModulSetting", "aktif", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("ModulSetting", "trigger fasa", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("ModulSetting", "[kanal]", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("ModulSetting", "[set aktif]", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("ModulSetting", "[Acc - mV/G]", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("ModulSetting", "Parameter Vibrasi (modul) :", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("ModulSetting", "F-max (Hz)", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("ModulSetting", "request lines", 0, QApplication::UnicodeUTF8));
        cb_lines->clear();
        cb_lines->insertItems(0, QStringList()
         << QApplication::translate("ModulSetting", "100", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "800", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "1600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "3200", 0, QApplication::UnicodeUTF8)
        );
        cb_fstop->clear();
        cb_fstop->insertItems(0, QStringList()
         << QApplication::translate("ModulSetting", "200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "300", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "500", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "700", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "800", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "900", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "1000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "1500", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "2000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "2500", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "3000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "5000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "10000", 0, QApplication::UnicodeUTF8)
        );
        label_13->setText(QApplication::translate("ModulSetting", "Sampling rate", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("ModulSetting", "Waktu sampling", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("ModulSetting", "Jumlah data", 0, QApplication::UnicodeUTF8));
        labelSamplingRate->setText(QApplication::translate("ModulSetting", "Sample/s", 0, QApplication::UnicodeUTF8));
        labelDataCount->setText(QApplication::translate("ModulSetting", "0", 0, QApplication::UnicodeUTF8));
        labelETA->setText(QApplication::translate("ModulSetting", "0s", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("ModulSetting", "F-min (Hz)", 0, QApplication::UnicodeUTF8));
        cb_fstart->clear();
        cb_fstart->insertItems(0, QStringList()
         << QApplication::translate("ModulSetting", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "20", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "60", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModulSetting", "120", 0, QApplication::UnicodeUTF8)
        );
        pb_update_set_modul->setText(QApplication::translate("ModulSetting", "Update Setting", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ModulSetting: public Ui_ModulSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODULSETTING_H
