#ifndef SIMPANTHREAD_H
#define SIMPANTHREAD_H

#include <QThread>
#include <QSqlQuery>
#include <QByteArray>


class SimpanThread : public QThread
{
    Q_OBJECT
public:
    explicit SimpanThread(QObject *parent = 0);
    void run(int jml_disimpan, float *data_disimpan, QSqlQuery qry_simpan, int id_waktu, int id_kanal, int urutan);

signals:

public slots:

};

#endif // SIMPANTHREAD_H
