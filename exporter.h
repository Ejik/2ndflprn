#ifndef EXPORTER_H
#define EXPORTER_H

#include <QObject>
#include <QAxObject>
#include <QStringList>
#include "importer.h"

class Exporter : public QObject
{
Q_OBJECT
public:
    Exporter(Importer* instance);
    ~Exporter();

    void exportToHtml();


private:
    Importer* data;
    QAxObject* mExcel;
    QStringList sheetsNames;

    QVariant getSheetName(int docNum, QAxObject* sheets);
    QString replaceExt(const QString name);

signals: 

public slots:

};

#endif // EXPORTER_H
