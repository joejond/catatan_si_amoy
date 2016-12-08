/********************************************************************************
** Form generated from reading UI file 'kanalview.ui'
**
** Created: Thu Aug 29 12:14:04 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KANALVIEW_H
#define UI_KANALVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
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

class Ui_kanalView
{
public:
    QHBoxLayout *mainLayout;
    QFrame *kanal_chart_view;
    QGridLayout *gridLayout;
    QSplitter *splitter_a;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *vl_wave;
    QWidget *verticalLayoutWidget2;
    QVBoxLayout *vl_spektrum;
    QVBoxLayout *verticalLayout;
    QFrame *frame_vew_set;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLabel *label_4;
    QFrame *line;
    QLabel *label_9;
    QComboBox *cb_sat_x_wave;
    QLabel *label_10;
    QComboBox *cb_sat_x_spek;
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
    QLabel *label_17;
    QComboBox *cb_window;
    QLabel *label_19;
    QLabel *label_20;
    QComboBox *cb_spek_tipe;
    QLabel *label_8;
    QComboBox *cb_averages;
    QComboBox *cb_ymax;
    QSpacerItem *verticalSpacer;
    QLabel *label_5;
    QComboBox *cb_wave_length;
    QLabel *label_6;
    QComboBox *cb_ymax_spek;
    QComboBox *cb_wtf_intv;

    void setupUi(QWidget *kanalView)
    {
        if (kanalView->objectName().isEmpty())
            kanalView->setObjectName(QString::fromUtf8("kanalView"));
        kanalView->resize(750, 550);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(kanalView->sizePolicy().hasHeightForWidth());
        kanalView->setSizePolicy(sizePolicy);
        kanalView->setMinimumSize(QSize(750, 550));
        mainLayout = new QHBoxLayout(kanalView);
        mainLayout->setSpacing(3);
        mainLayout->setContentsMargins(5, 5, 5, 5);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        kanal_chart_view = new QFrame(kanalView);
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
        verticalLayoutWidget2 = new QWidget(splitter_a);
        verticalLayoutWidget2->setObjectName(QString::fromUtf8("verticalLayoutWidget2"));
        vl_spektrum = new QVBoxLayout(verticalLayoutWidget2);
        vl_spektrum->setObjectName(QString::fromUtf8("vl_spektrum"));
        vl_spektrum->setContentsMargins(0, 0, 0, 0);
        splitter_a->addWidget(verticalLayoutWidget2);

        gridLayout->addWidget(splitter_a, 0, 0, 1, 1);


        mainLayout->addWidget(kanal_chart_view);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame_vew_set = new QFrame(kanalView);
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

        gridLayout_2->addWidget(label_2, 12, 0, 1, 1);

        label_4 = new QLabel(frame_vew_set);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_4->setFont(font);

        gridLayout_2->addWidget(label_4, 18, 0, 1, 2);

        line = new QFrame(frame_vew_set);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line, 17, 0, 1, 2);

        label_9 = new QLabel(frame_vew_set);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_9, 15, 0, 1, 1);

        cb_sat_x_wave = new QComboBox(frame_vew_set);
        cb_sat_x_wave->setObjectName(QString::fromUtf8("cb_sat_x_wave"));

        gridLayout_2->addWidget(cb_sat_x_wave, 15, 1, 1, 1);

        label_10 = new QLabel(frame_vew_set);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_10, 20, 0, 1, 1);

        cb_sat_x_spek = new QComboBox(frame_vew_set);
        cb_sat_x_spek->setObjectName(QString::fromUtf8("cb_sat_x_spek"));

        gridLayout_2->addWidget(cb_sat_x_spek, 20, 1, 1, 1);

        label = new QLabel(frame_vew_set);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        gridLayout_2->addWidget(label, 11, 0, 1, 2);

        label_11 = new QLabel(frame_vew_set);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font);

        gridLayout_2->addWidget(label_11, 1, 0, 1, 2);

        line_4 = new QFrame(frame_vew_set);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_4, 9, 0, 1, 2);

        label_12 = new QLabel(frame_vew_set);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_12, 5, 0, 1, 1);

        cb_data_tipe = new QComboBox(frame_vew_set);
        cb_data_tipe->setObjectName(QString::fromUtf8("cb_data_tipe"));

        gridLayout_2->addWidget(cb_data_tipe, 5, 1, 1, 1);

        label_13 = new QLabel(frame_vew_set);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_13, 6, 0, 1, 1);

        cb_sat_accel = new QComboBox(frame_vew_set);
        cb_sat_accel->setObjectName(QString::fromUtf8("cb_sat_accel"));

        gridLayout_2->addWidget(cb_sat_accel, 6, 1, 1, 1);

        label_14 = new QLabel(frame_vew_set);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_14, 7, 0, 1, 1);

        cb_sat_velo = new QComboBox(frame_vew_set);
        cb_sat_velo->setObjectName(QString::fromUtf8("cb_sat_velo"));

        gridLayout_2->addWidget(cb_sat_velo, 7, 1, 1, 1);

        label_15 = new QLabel(frame_vew_set);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_15, 8, 0, 1, 1);

        cb_sat_disp = new QComboBox(frame_vew_set);
        cb_sat_disp->setObjectName(QString::fromUtf8("cb_sat_disp"));

        gridLayout_2->addWidget(cb_sat_disp, 8, 1, 1, 1);

        label_17 = new QLabel(frame_vew_set);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_17, 2, 0, 1, 1);

        cb_window = new QComboBox(frame_vew_set);
        cb_window->setObjectName(QString::fromUtf8("cb_window"));

        gridLayout_2->addWidget(cb_window, 2, 1, 1, 1);

        label_19 = new QLabel(frame_vew_set);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_19, 3, 0, 1, 1);

        label_20 = new QLabel(frame_vew_set);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_20, 19, 0, 1, 1);

        cb_spek_tipe = new QComboBox(frame_vew_set);
        cb_spek_tipe->setObjectName(QString::fromUtf8("cb_spek_tipe"));

        gridLayout_2->addWidget(cb_spek_tipe, 19, 1, 1, 1);

        label_8 = new QLabel(frame_vew_set);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_8, 22, 0, 1, 1);

        cb_averages = new QComboBox(frame_vew_set);
        cb_averages->setObjectName(QString::fromUtf8("cb_averages"));

        gridLayout_2->addWidget(cb_averages, 3, 1, 1, 1);

        cb_ymax = new QComboBox(frame_vew_set);
        cb_ymax->setObjectName(QString::fromUtf8("cb_ymax"));

        gridLayout_2->addWidget(cb_ymax, 12, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 23, 0, 1, 2);

        label_5 = new QLabel(frame_vew_set);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_5, 16, 0, 1, 1);

        cb_wave_length = new QComboBox(frame_vew_set);
        cb_wave_length->setObjectName(QString::fromUtf8("cb_wave_length"));

        gridLayout_2->addWidget(cb_wave_length, 16, 1, 1, 1);

        label_6 = new QLabel(frame_vew_set);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_6, 21, 0, 1, 1);

        cb_ymax_spek = new QComboBox(frame_vew_set);
        cb_ymax_spek->setObjectName(QString::fromUtf8("cb_ymax_spek"));

        gridLayout_2->addWidget(cb_ymax_spek, 21, 1, 1, 1);

        cb_wtf_intv = new QComboBox(frame_vew_set);
        cb_wtf_intv->setObjectName(QString::fromUtf8("cb_wtf_intv"));

        gridLayout_2->addWidget(cb_wtf_intv, 22, 1, 1, 1);


        verticalLayout->addWidget(frame_vew_set);


        mainLayout->addLayout(verticalLayout);

        mainLayout->setStretch(0, 15);
        mainLayout->setStretch(1, 3);

        retranslateUi(kanalView);

        cb_wave_length->setCurrentIndex(5);


        QMetaObject::connectSlotsByName(kanalView);
    } // setupUi

    void retranslateUi(QWidget *kanalView)
    {
        label_2->setText(QApplication::translate("kanalView", "Y-max", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("kanalView", "Spectrum :", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("kanalView", "X-axis", 0, QApplication::UnicodeUTF8));
        cb_sat_x_wave->clear();
        cb_sat_x_wave->insertItems(0, QStringList()
         << QApplication::translate("kanalView", "ms", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "deg", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "points", 0, QApplication::UnicodeUTF8)
        );
        label_10->setText(QApplication::translate("kanalView", "X-axis", 0, QApplication::UnicodeUTF8));
        cb_sat_x_spek->clear();
        cb_sat_x_spek->insertItems(0, QStringList()
         << QApplication::translate("kanalView", "Hz", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "cpm", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "points", 0, QApplication::UnicodeUTF8)
        );
        label->setText(QApplication::translate("kanalView", "Waveform :", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("kanalView", "Setting Kanal:", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("kanalView", "Data Type", 0, QApplication::UnicodeUTF8));
        cb_data_tipe->clear();
        cb_data_tipe->insertItems(0, QStringList()
         << QApplication::translate("kanalView", "Acceleration", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "Velocity", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "Displacement", 0, QApplication::UnicodeUTF8)
        );
        label_13->setText(QApplication::translate("kanalView", "Accel. Unit", 0, QApplication::UnicodeUTF8));
        cb_sat_accel->clear();
        cb_sat_accel->insertItems(0, QStringList()
         << QApplication::translate("kanalView", "G", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "mm/s2", 0, QApplication::UnicodeUTF8)
        );
        label_14->setText(QApplication::translate("kanalView", "Velo. Unit", 0, QApplication::UnicodeUTF8));
        cb_sat_velo->clear();
        cb_sat_velo->insertItems(0, QStringList()
         << QApplication::translate("kanalView", "mm/s", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "IPS", 0, QApplication::UnicodeUTF8)
        );
        label_15->setText(QApplication::translate("kanalView", "Disp. Unit", 0, QApplication::UnicodeUTF8));
        cb_sat_disp->clear();
        cb_sat_disp->insertItems(0, QStringList()
         << QApplication::translate("kanalView", "mm", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "micron", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "mils", 0, QApplication::UnicodeUTF8)
        );
        label_17->setText(QApplication::translate("kanalView", "Windowing", 0, QApplication::UnicodeUTF8));
        cb_window->clear();
        cb_window->insertItems(0, QStringList()
         << QApplication::translate("kanalView", "Hanning", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "Blackman", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "Rectangular", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "Hamming", 0, QApplication::UnicodeUTF8)
        );
        label_19->setText(QApplication::translate("kanalView", "Averages", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("kanalView", "Type", 0, QApplication::UnicodeUTF8));
        cb_spek_tipe->clear();
        cb_spek_tipe->insertItems(0, QStringList()
         << QApplication::translate("kanalView", "Single", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "Waterfall", 0, QApplication::UnicodeUTF8)
        );
        label_8->setText(QApplication::translate("kanalView", "Waterfall (s)", 0, QApplication::UnicodeUTF8));
        cb_averages->clear();
        cb_averages->insertItems(0, QStringList()
         << QApplication::translate("kanalView", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "4", 0, QApplication::UnicodeUTF8)
        );
        cb_ymax->clear();
        cb_ymax->insertItems(0, QStringList()
         << QApplication::translate("kanalView", "0.01", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "0.05", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "0.1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "0.5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "50", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "100", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "500", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "1000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "5000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "10000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "50000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "100000", 0, QApplication::UnicodeUTF8)
        );
        label_5->setText(QApplication::translate("kanalView", "view length", 0, QApplication::UnicodeUTF8));
        cb_wave_length->clear();
        cb_wave_length->insertItems(0, QStringList()
         << QApplication::translate("kanalView", "10%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "20%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "30%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "40%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "50%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "100%", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QApplication::translate("kanalView", "Y-max", 0, QApplication::UnicodeUTF8));
        cb_ymax_spek->clear();
        cb_ymax_spek->insertItems(0, QStringList()
         << QApplication::translate("kanalView", "0.01", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "0.05", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "0.1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "0.5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "50", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "100", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "500", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "1000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "5000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "10000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "50000", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "100000", 0, QApplication::UnicodeUTF8)
        );
        cb_wtf_intv->clear();
        cb_wtf_intv->insertItems(0, QStringList()
         << QApplication::translate("kanalView", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "30", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "60", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("kanalView", "120", 0, QApplication::UnicodeUTF8)
        );
        Q_UNUSED(kanalView);
    } // retranslateUi

};

namespace Ui {
    class kanalView: public Ui_kanalView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KANALVIEW_H
