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


private:
    Importer* data;
    QAxObject* mExcel;

    QVariant getSheetName(int docNum, QAxObject* sheets);
    QString replaceExt(const QString name);

signals: 

public slots:

};

#endif // EXPORTER_H
