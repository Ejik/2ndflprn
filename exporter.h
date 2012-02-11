#ifndef EXPORTER_H
#define EXPORTER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include "importer.h"
#include "processor.h"
#include "processorxml.h"


class Exporter : public QObject
{
Q_OBJECT
public:
    Exporter(Processor* instance);
    ~Exporter();

    void export_to_html();

private:

    QStringList PrintSpraw(SprawModel spraw);
    int PrintHeader(QTextStream* out);

    QString GetHTMLTable1(QList<QStringList> tbl1);
    QString GetHTMLPara4(QStringList data);
    QString GetHTMLPara5(QList<QStringList> data);

    Processor* processor_;
    QFile outputFile;
    QStringList sheetsNames;

    QString replaceExt(const QString name);
    void exportSection(const QString secNum, QTextStream* out);

signals: 

public slots:

};

#endif // EXPORTER_H
