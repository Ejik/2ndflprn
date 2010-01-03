#ifndef EXPORTER_H
#define EXPORTER_H

#include <QObject>
#include <QAxObject>
#include "importer.h"

class Exporter : public QObject
{
Q_OBJECT
public:
    Exporter(Importer* instance);
    ~Exporter();

    void exportToExcel();
    QString replaceExt(const QString name);

private:
    Importer* data;
    QAxObject* mExcel;

signals: 

public slots:

};

#endif // EXPORTER_H
