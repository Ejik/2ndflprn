#ifndef EXPORTER_H
#define EXPORTER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
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
    QFile outputFile;
    QStringList sheetsNames;

    QString replaceExt(const QString name);
    void exportSection(const QString secNum, QTextStream* out);

signals: 

public slots:

};

#endif // EXPORTER_H
