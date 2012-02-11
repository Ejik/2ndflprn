#ifndef PROCESSORLST_H
#define PROCESSORLST_H

#include <QStringList>
#include "processor.h"
#include "sprawmodel.h"
#include "tablemodel.h"

class ProcessorLST : public Processor
{
public:
    ProcessorLST(const QString filename);
    int Import();
    int ParseData();

private:
    QString GetTitle(QStringList pagedata);
    QMap<int, QString> GetTBNFIO(QStringList pagedata);
    QString GetValue(QStringList pagedata, const QString valuename, int len);
    QList<QStringList> GetTable(QStringList pagedata);
    QStringList GetPara4(QStringList pagedata);
    QList<QStringList> GetPara5(QStringList pagedata);
};

#endif // PROCESSORLST_H
