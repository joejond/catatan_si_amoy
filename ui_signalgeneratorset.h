/********************************************************************************
** Form generated from reading UI file 'signalgeneratorset.ui'
**
** Created: Thu Aug 29 12:14:04 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNALGENERATORSET_H
#define UI_SIGNALGENERATORSET_H

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
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignalGeneratorSet
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QCheckBox *chk_flag_simul;
    QLabel *label;
    QLineEdit *le_f1;
    QLineEdit *le_a1;
    QLineEdit *le_fasa1;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QCheckBox *chk_sig2;
    QCheckBox *chk_sig3;
    QCheckBox *chk_sig4;
    QFrame *line;
    QLabel *label_5;
    QComboBox *cb_sig_type;
    QFrame *line_2;
    QLineEdit *le_f2;
    QLineEdit *le_f3;
    QLineEdit *le_f4;
    QLineEdit *le_a2;
    QLineEdit *le_a3;
    QLineEdit *le_a4;
    QLineEdit *le_fasa2;
    QLineEdit *le_fasa3;
    QLineEdit *le_fasa4;
    QCheckBox *chk_sig5;
    QLineEdit *le_f5;
    QLineEdit *le_a5;
    QLineEdit *le_fasa5;
    QHBoxLayout *horizontalLayout;
    QPushButton *pb_update_set_siggen;

    void setupUi(QWidget *SignalGeneratorSet)
    {
        if (SignalGeneratorSet->objectName().isEmpty())
            SignalGeneratorSet->setObjectName(QString::fromUtf8("SignalGeneratorSet"));
        SignalGeneratorSet->resize(267, 265);
        verticalLayout = new QVBoxLayout(SignalGeneratorSet);
        verticalLayout->setSpacing(3);
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        frame = new QFrame(SignalGeneratorSet);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        chk_flag_simul = new QCheckBox(frame);
        chk_flag_simul->setObjectName(QString::fromUtf8("chk_flag_simul"));

        gridLayout_2->addWidget(chk_flag_simul, 0, 0, 1, 4);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 3, 0, 1, 1);

        le_f1 = new QLineEdit(frame);
        le_f1->setObjectName(QString::fromUtf8("le_f1"));

        gridLayout_2->addWidget(le_f1, 3, 1, 1, 1);

        le_a1 = new QLineEdit(frame);
        le_a1->setObjectName(QString::fromUtf8("le_a1"));

        gridLayout_2->addWidget(le_a1, 3, 2, 1, 1);

        le_fasa1 = new QLineEdit(frame);
        le_fasa1->setObjectName(QString::fromUtf8("le_fasa1"));

        gridLayout_2->addWidget(le_fasa1, 3, 3, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_2, 2, 1, 1, 1);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_3, 2, 2, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_4, 2, 3, 1, 1);

        chk_sig2 = new QCheckBox(frame);
        chk_sig2->setObjectName(QString::fromUtf8("chk_sig2"));

        gridLayout_2->addWidget(chk_sig2, 4, 0, 1, 1);

        chk_sig3 = new QCheckBox(frame);
        chk_sig3->setObjectName(QString::fromUtf8("chk_sig3"));

        gridLayout_2->addWidget(chk_sig3, 5, 0, 1, 1);

        chk_sig4 = new QCheckBox(frame);
        chk_sig4->setObjectName(QString::fromUtf8("chk_sig4"));

        gridLayout_2->addWidget(chk_sig4, 6, 0, 1, 1);

        line = new QFrame(frame);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line, 1, 0, 1, 4);

        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 9, 0, 1, 1);

        cb_sig_type = new QComboBox(frame);
        cb_sig_type->setObjectName(QString::fromUtf8("cb_sig_type"));

        gridLayout_2->addWidget(cb_sig_type, 9, 1, 1, 2);

        line_2 = new QFrame(frame);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_2, 8, 0, 1, 4);

        le_f2 = new QLineEdit(frame);
        le_f2->setObjectName(QString::fromUtf8("le_f2"));

        gridLayout_2->addWidget(le_f2, 4, 1, 1, 1);

        le_f3 = new QLineEdit(frame);
        le_f3->setObjectName(QString::fromUtf8("le_f3"));

        gridLayout_2->addWidget(le_f3, 5, 1, 1, 1);

        le_f4 = new QLineEdit(frame);
        le_f4->setObjectName(QString::fromUtf8("le_f4"));

        gridLayout_2->addWidget(le_f4, 6, 1, 1, 1);

        le_a2 = new QLineEdit(frame);
        le_a2->setObjectName(QString::fromUtf8("le_a2"));

        gridLayout_2->addWidget(le_a2, 4, 2, 1, 1);

        le_a3 = new QLineEdit(frame);
        le_a3->setObjectName(QString::fromUtf8("le_a3"));

        gridLayout_2->addWidget(le_a3, 5, 2, 1, 1);

        le_a4 = new QLineEdit(frame);
        le_a4->setObjectName(QString::fromUtf8("le_a4"));

        gridLayout_2->addWidget(le_a4, 6, 2, 1, 1);

        le_fasa2 = new QLineEdit(frame);
        le_fasa2->setObjectName(QString::fromUtf8("le_fasa2"));

        gridLayout_2->addWidget(le_fasa2, 4, 3, 1, 1);

        le_fasa3 = new QLineEdit(frame);
        le_fasa3->setObjectName(QString::fromUtf8("le_fasa3"));

        gridLayout_2->addWidget(le_fasa3, 5, 3, 1, 1);

        le_fasa4 = new QLineEdit(frame);
        le_fasa4->setObjectName(QString::fromUtf8("le_fasa4"));

        gridLayout_2->addWidget(le_fasa4, 6, 3, 1, 1);

        chk_sig5 = new QCheckBox(frame);
        chk_sig5->setObjectName(QString::fromUtf8("chk_sig5"));

        gridLayout_2->addWidget(chk_sig5, 7, 0, 1, 1);

        le_f5 = new QLineEdit(frame);
        le_f5->setObjectName(QString::fromUtf8("le_f5"));

        gridLayout_2->addWidget(le_f5, 7, 1, 1, 1);

        le_a5 = new QLineEdit(frame);
        le_a5->setObjectName(QString::fromUtf8("le_a5"));

        gridLayout_2->addWidget(le_a5, 7, 2, 1, 1);

        le_fasa5 = new QLineEdit(frame);
        le_fasa5->setObjectName(QString::fromUtf8("le_fasa5"));

        gridLayout_2->addWidget(le_fasa5, 7, 3, 1, 1);


        verticalLayout->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(50, -1, 50, -1);
        pb_update_set_siggen = new QPushButton(SignalGeneratorSet);
        pb_update_set_siggen->setObjectName(QString::fromUtf8("pb_update_set_siggen"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        pb_update_set_siggen->setFont(font);

        horizontalLayout->addWidget(pb_update_set_siggen);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(SignalGeneratorSet);

        QMetaObject::connectSlotsByName(SignalGeneratorSet);
    } // setupUi

    void retranslateUi(QWidget *SignalGeneratorSet)
    {
        SignalGeneratorSet->setWindowTitle(QApplication::translate("SignalGeneratorSet", "Form", 0, QApplication::UnicodeUTF8));
        chk_flag_simul->setText(QApplication::translate("SignalGeneratorSet", "Signal generator aktif", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SignalGeneratorSet", "Signal-1", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SignalGeneratorSet", "[frekuensi]", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SignalGeneratorSet", "[amplitudo]", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("SignalGeneratorSet", "[fasa]", 0, QApplication::UnicodeUTF8));
        chk_sig2->setText(QApplication::translate("SignalGeneratorSet", "Signal-2", 0, QApplication::UnicodeUTF8));
        chk_sig3->setText(QApplication::translate("SignalGeneratorSet", "Signal-3", 0, QApplication::UnicodeUTF8));
        chk_sig4->setText(QApplication::translate("SignalGeneratorSet", "Signal-4", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("SignalGeneratorSet", "Tipe signal", 0, QApplication::UnicodeUTF8));
        cb_sig_type->clear();
        cb_sig_type->insertItems(0, QStringList()
         << QApplication::translate("SignalGeneratorSet", "sinus", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SignalGeneratorSet", "triangle", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SignalGeneratorSet", "square", 0, QApplication::UnicodeUTF8)
        );
        chk_sig5->setText(QApplication::translate("SignalGeneratorSet", "Signal-5", 0, QApplication::UnicodeUTF8));
        pb_update_set_siggen->setText(QApplication::translate("SignalGeneratorSet", "Update Setting", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SignalGeneratorSet: public Ui_SignalGeneratorSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNALGENERATORSET_H
