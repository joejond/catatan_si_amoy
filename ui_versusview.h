/********************************************************************************
** Form generated from reading UI file 'versusview.ui'
**
** Created: Thu Aug 29 12:14:04 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VERSUSVIEW_H
#define UI_VERSUSVIEW_H

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
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VersusView
{
public:
    QHBoxLayout *mainLayout;
    QFrame *kanal_chart_view;
    QGridLayout *gridLayout;
    QSplitter *splitter_a;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *vl_wave;
    QVBoxLayout *verticalLayout;
    QFrame *frame_vew_set;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLabel *label_9;
    QComboBox *cb_sat_x_wave;
    QLabel *label;
    QLabel *label_11;
    QFrame *line_4;
    QLabel *label_12;
    QComboBox *cb_data_tipe;
    QLabel *label_13;
    QComboBox *cb_sat_accel;
    QLabel *label_14;
    QComboBox *cb_sat_velo;
    QLabel *label_15;
    QComboBox *cb_sat_disp;
    QComboBox *cb_ymax;
    QSpacerItem *verticalSpacer;
    QLabel *label_3;
    QComboBox *cb_wave_length;
    QLabel *label_5;
    QCheckBox *check_kanal1;
    QLabel *label_6;
    QCheckBox *check_kanal2;
    QLabel *label_7;
    QLabel *label_8;
    QCheckBox *check_kanal3;
    QCheckBox *check_kanal4;
    QLabel *label_4;
    QComboBox *cb_window;

    void setupUi(QWidget *VersusView)
    {
        if (VersusView->objectName().isEmpty())
            VersusView->setObjectName(QString::fromUtf8("VersusView"));
        VersusView->resize(750, 550);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(VersusView->sizePolicy().hasHeightForWidth());
        VersusView->setSizePolicy(sizePolicy);
        VersusView->setMinimumSize(QSize(750, 550));
        mainLayout = new QHBoxLayout(VersusView);
        mainLayout->setSpacing(3);
        mainLayout->setContentsMargins(5, 5, 5, 5);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        kanal_chart_view = new QFrame(VersusView);
        kanal_chart_view->setObjectName(QString::fromUtf8("kanal_chart_view"));
        gridLayout = new QGridLayout(kanal_chart_view);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter_a = new QSplitter(kanal_chart_view);
        splitter_a->setObjectName(QString::fromUtf8("splitter_a"));
        splitter_a->setLineWidth(2);
        splitter_a->setOrientation(Qt::Vertical);
        splitter_a->setHandleWidth(2);
        splitter_a->setChildrenCollapsible(false);
        verticalLayoutWidget = new QWidget(splitter_a);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        vl_wave = new QVBoxLayout(verticalLayoutWidget);
        vl_wave->setObjectName(QString::fromUtf8("vl_wave"));
        vl_wave->setContentsMargins(0, 0, 0, 0);
        splitter_a->addWidget(verticalLayoutWidget);

        gridLayout->addWidget(splitter_a, 0, 0, 1, 1);


        mainLayout->addWidget(kanal_chart_view);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame_vew_set = new QFrame(VersusView);
        frame_vew_set->setObjectName(QString::fromUtf8("frame_vew_set"));
        frame_vew_set->setFrameShape(QFrame::Box);
        frame_vew_set->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_vew_set);
        gridLayout_2->setSpacing(3);
        gridLayout_2->setContentsMargins(3, 3, 3, 3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(frame_vew_set);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_2, 15, 0, 1, 1);

        label_9 = new QLabel(frame_vew_set);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_9, 18, 0, 1, 1);

        cb_sat_x_wave = new QComboBox(frame_vew_set);
        cb_sat_x_wave->setObjectName(QString::fromUtf8("cb_sat_x_wave"));

        gridLayout_2->addWidget(cb_sat_x_wave, 18, 1, 1, 1);

        label = new QLabel(frame_vew_set);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        gridLayout_2->addWidget(label, 14, 0, 1, 2);

        label_11 = new QLabel(frame_vew_set);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font);

        gridLayout_2->addWidget(label_11, 1, 0, 1, 2);

        line_4 = new QFrame(frame_vew_set);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_4, 12, 0, 1, 2);

        label_12 = new QLabel(frame_vew_set);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_12, 7, 0, 1, 1);

        cb_data_tipe = new QComboBox(frame_vew_set);
        cb_data_tipe->setObjectName(QString::fromUtf8("cb_data_tipe"));

        gridLayout_2->addWidget(cb_data_tipe, 7, 1, 1, 1);

        label_13 = new QLabel(frame_vew_set);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_13, 9, 0, 1, 1);

        cb_sat_accel = new QComboBox(frame_vew_set);
        cb_sat_accel->setObjectName(QString::fromUtf8("cb_sat_accel"));

        gridLayout_2->addWidget(cb_sat_accel, 9, 1, 1, 1);

        label_14 = new QLabel(frame_vew_set);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_14, 10, 0, 1, 1);

        cb_sat_velo = new QComboBox(frame_vew_set);
        cb_sat_velo->setObjectName(QString::fromUtf8("cb_sat_velo"));

        gridLayout_2->addWidget(cb_sat_velo, 10, 1, 1, 1);

        label_15 = new QLabel(frame_vew_set);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_15, 11, 0, 1, 1);

        cb_sat_disp = new QComboBox(frame_vew_set);
        cb_sat_disp->setObjectName(QString::fromUtf8("cb_sat_disp"));

        gridLayout_2->addWidget(cb_sat_disp, 11, 1, 1, 1);

        cb_ymax = new QComboBox(frame_vew_set);
        cb_ymax->setObjectName(QString::fromUtf8("cb_ymax"));

        gridLayout_2->addWidget(cb_ymax, 15, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 20, 0, 1, 2);

        label_3 = new QLabel(frame_vew_set);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_3, 19, 0, 1, 1);

        cb_wave_length = new QComboBox(frame_vew_set);
        cb_wave_length->setObjectName(QString::fromUtf8("cb_wave_length"));

        gridLayout_2->addWidget(cb_wave_length, 19, 1, 1, 1);

        label_5 = new QLabel(frame_vew_set);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_5, 2, 0, 1, 1);

        check_kanal1 = new QCheckBox(frame_vew_set);
        check_kanal1->setObjectName(QString::fromUtf8("check_kanal1"));

        gridLayout_2->addWidget(check_kanal1, 2, 1, 1, 1);

        label_6 = new QLabel(frame_vew_set);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_6, 3, 0, 1, 1);

        check_kanal2 = new QCheckBox(frame_vew_set);
        check_kanal2->setObjectName(QString::fromUtf8("check_kanal2"));

        gridLayout_2->addWidget(check_kanal2, 3, 1, 1, 1);

        label_7 = new QLabel(frame_vew_set);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_7, 4, 0, 1, 1);

        label_8 = new QLabel(frame_vew_set);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_8, 5, 0, 1, 1);

        check_kanal3 = new QCheckBox(frame_vew_set);
        check_kanal3->setObjectName(QString::fromUtf8("check_kanal3"));

        gridLayout_2->addWidget(check_kanal3, 4, 1, 1, 1);

        check_kanal4 = new QCheckBox(frame_vew_set);
        check_kanal4->setObjectName(QString::fromUtf8("check_kanal4"));

        gridLayout_2->addWidget(check_kanal4, 5, 1, 1, 1);

        label_4 = new QLabel(frame_vew_set);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 8, 0, 1, 1);

        cb_window = new QComboBox(frame_vew_set);
        cb_window->setObjectName(QString::fromUtf8("cb_window"));

        gridLayout_2->addWidget(cb_window, 8, 1, 1, 1);


        verticalLayout->addWidget(frame_vew_set);


        mainLayout->addLayout(verticalLayout);

        mainLayout->setStretch(0, 15);
        mainLayout->setStretch(1, 3);

        retranslateUi(VersusView);

        cb_wave_length->setCurrentIndex(5);


        QMetaObject::connectSlotsByName(VersusView);
    } // setupUi

    void retranslateUi(QWidget *VersusView)
    {
        label_2->setText(QApplication::translate("VersusView", "Y-max", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("VersusView", "X-axis", 0, QApplication::UnicodeUTF8));
        cb_sat_x_wave->clear();
        cb_sat_x_wave->insertItems(0, QStringList()
         << QApplication::translate("VersusView", "ms", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "deg", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "points", 0, QApplication::UnicodeUTF8)
        );
        label->setText(QApplication::translate("VersusView", "Waveform :", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("VersusView", "Setting Kanal:", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("VersusView", "Data Type", 0, QApplication::UnicodeUTF8));
        cb_data_tipe->clear();
        cb_data_tipe->insertItems(0, QStringList()
         << QApplication::translate("VersusView", "Acceleration", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "Velocity", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "Displacement", 0, QApplication::UnicodeUTF8)
        );
        label_13->setText(QApplication::translate("VersusView", "Accel. Unit", 0, QApplication::UnicodeUTF8));
        cb_sat_accel->clear();
        cb_sat_accel->insertItems(0, QStringList()
         << QApplication::translate("VersusView", "G", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "mm/s2", 0, QApplication::UnicodeUTF8)
        );
        label_14->setText(QApplication::translate("VersusView", "Velo. Unit", 0, QApplication::UnicodeUTF8));
        cb_sat_velo->clear();
        cb_sat_velo->insertItems(0, QStringList()
         << QApplication::translate("VersusView", "mm/s", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "IPS", 0, QApplication::UnicodeUTF8)
        );
        label_15->setText(QApplication::translate("VersusView", "Disp. Unit", 0, QApplication::UnicodeUTF8));
        cb_sat_disp->clear();
        cb_sat_disp->insertItems(0, QStringList()
         << QApplication::translate("VersusView", "mm", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "micron", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "mils", 0, QApplication::UnicodeUTF8)
        );
        cb_ymax->clear();
        cb_ymax->insertItems(0, QStringList()
         << QApplication::translate("VersusView", "0.01", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "0.05", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "0.1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "0.5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "50", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "100", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "500", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "1000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "5000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "10000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "50000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "100000", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("VersusView", "view length", 0, QApplication::UnicodeUTF8));
        cb_wave_length->clear();
        cb_wave_length->insertItems(0, QStringList()
         << QApplication::translate("VersusView", "10%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "20%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "30%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "40%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "50%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "100%", 0, QApplication::UnicodeUTF8)
        );
        label_5->setText(QApplication::translate("VersusView", "Channel-1", 0, QApplication::UnicodeUTF8));
        check_kanal1->setText(QApplication::translate("VersusView", "view", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("VersusView", "Channel-2", 0, QApplication::UnicodeUTF8));
        check_kanal2->setText(QApplication::translate("VersusView", "view", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("VersusView", "Channel-3", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("VersusView", "Channel-4", 0, QApplication::UnicodeUTF8));
        check_kanal3->setText(QApplication::translate("VersusView", "view", 0, QApplication::UnicodeUTF8));
        check_kanal4->setText(QApplication::translate("VersusView", "view", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("VersusView", "Windowing", 0, QApplication::UnicodeUTF8));
        cb_window->clear();
        cb_window->insertItems(0, QStringList()
         << QApplication::translate("VersusView", "Hanning", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "Blackman", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "Rectangular", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VersusView", "Hamming", 0, QApplication::UnicodeUTF8)
        );
        Q_UNUSED(VersusView);
    } // retranslateUi

};

namespace Ui {
    class VersusView: public Ui_VersusView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VERSUSVIEW_H
