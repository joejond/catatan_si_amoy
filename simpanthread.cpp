#include "simpanthread.h"
#include <QVariant>
#include <QSqlError>

SimpanThread::SimpanThread(QObject *parent) :
    QThread(parent)
{
}

void SimpanThread::run(int jml_disimpan, float *data_disimpan, QSqlQuery qry_simpan, int id_waktu, int id_kanal, int urutan)
{
    QByteArray ba;
    QSqlError er;
    for(int n = 0; n < jml_disimpan; n++)
    {
        QByteArray ba1(reinterpret_cast<const char*>(&data_disimpan[n]), sizeof(data_disimpan[n]));
        ba.append(ba1);
    }

    // referensi : http://www.sqlite.org/faq.html#q19
    qry_simpan.exec("PRAGMA synchronous = OFF");

    qry_simpan.prepare("Insert into data (id_waktu, kanal, note, data) Values (?, ?, ?, ?)");
    qry_simpan.bindValue(0, id_waktu);
    qry_simpan.bindValue(1, id_kanal);
    qry_simpan.bindValue(2, urutan);
    qry_simpan.bindValue(3, ba);

    if (!qry_simpan.exec())
    {
        er = qry_simpan.lastError();
        qDebug("Masukin Blob error %s", er.text().toAscii().data());

        return;
    }
    else qDebug("OK sip");

}
