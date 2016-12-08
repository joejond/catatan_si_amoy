/********************************************************************************
** Form generated from reading UI file 'dbcontrol.ui'
**
** Created: Thu Aug 29 12:14:04 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DBCONTROL_H
#define UI_DBCONTROL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DbControl
{
public:
    QHBoxLayout *horizontalLayout;
    QTableView *table_db;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_info;
    QFrame *frame_2;
    QGridLayout *gridLayout;
    QPushButton *pb_open_db;
    QPushButton *pb_new_db;
    QPushButton *pb_save_db;
    QPushButton *pb_load_db;
    QFrame *line;
    QPushButton *pb_delete_record;

    void setupUi(QWidget *DbControl)
    {
        if (DbControl->objectName().isEmpty())
            DbControl->setObjectName(QString::fromUtf8("DbControl"));
        DbControl->resize(424, 404);
        horizontalLayout = new QHBoxLayout(DbControl);
        horizontalLayout->setSpacing(5);
        horizontalLayout->setContentsMargins(3, 3, 3, 3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        table_db = new QTableView(DbControl);
        table_db->setObjectName(QString::fromUtf8("table_db"));

        horizontalLayout->addWidget(table_db);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(3);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        frame = new QFrame(DbControl);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_info = new QLabel(groupBox);
        label_info->setObjectName(QString::fromUtf8("label_info"));
        label_info->setMinimumSize(QSize(0, 120));
        label_info->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_3->addWidget(label_info);


        verticalLayout_2->addWidget(groupBox);


        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(DbControl);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pb_open_db = new QPushButton(frame_2);
        pb_open_db->setObjectName(QString::fromUtf8("pb_open_db"));

        gridLayout->addWidget(pb_open_db, 0, 0, 1, 1);

        pb_new_db = new QPushButton(frame_2);
        pb_new_db->setObjectName(QString::fromUtf8("pb_new_db"));

        gridLayout->addWidget(pb_new_db, 0, 1, 1, 1);

        pb_save_db = new QPushButton(frame_2);
        pb_save_db->setObjectName(QString::fromUtf8("pb_save_db"));

        gridLayout->addWidget(pb_save_db, 2, 0, 1, 1);

        pb_load_db = new QPushButton(frame_2);
        pb_load_db->setObjectName(QString::fromUtf8("pb_load_db"));

        gridLayout->addWidget(pb_load_db, 2, 1, 1, 1);

        line = new QFrame(frame_2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 0, 1, 2);

        pb_delete_record = new QPushButton(frame_2);
        pb_delete_record->setObjectName(QString::fromUtf8("pb_delete_record"));

        gridLayout->addWidget(pb_delete_record, 3, 0, 1, 1);


        verticalLayout->addWidget(frame_2);

        verticalLayout->setStretch(0, 2);

        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 1);

        retranslateUi(DbControl);

        QMetaObject::connectSlotsByName(DbControl);
    } // setupUi

    void retranslateUi(QWidget *DbControl)
    {
        DbControl->setWindowTitle(QApplication::translate("DbControl", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("DbControl", "Selected data info :", 0, QApplication::UnicodeUTF8));
        label_info->setText(QApplication::translate("DbControl", "<html>\n"
"<body style=\" font-family:'Ubuntu'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p>F-start = - Hz</p>\n"
"<p>F-Stop = - Hz</p>\n"
"<p>Fase Enabled = No</p>\n"
"<p>Accelerometer1 = - (mV/G)</p>\n"
"<p>Accelerometer2 = - (mV/G)</p>\n"
"<p>Accelerometer3 = - (mV/G)</p>\n"
"<p>Accelerometer4 = - (mV/G)</p>\n"
"</body>\n"
"</html>", 0, QApplication::UnicodeUTF8));
        pb_open_db->setText(QApplication::translate("DbControl", "Buka Database", 0, QApplication::UnicodeUTF8));
        pb_new_db->setText(QApplication::translate("DbControl", "Database Baru", 0, QApplication::UnicodeUTF8));
        pb_save_db->setText(QApplication::translate("DbControl", "Simpan", 0, QApplication::UnicodeUTF8));
        pb_load_db->setText(QApplication::translate("DbControl", "Load", 0, QApplication::UnicodeUTF8));
        pb_delete_record->setText(QApplication::translate("DbControl", "delete record", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DbControl: public Ui_DbControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DBCONTROL_H
