#ifndef IMPORTER_H
#define IMPORTER_H

#include <QObject>
#include <QMap>

class Importer : public QObject
{
private:
    QString inputFile;

    void parseTitle(const QString line);
    void parseINNCPP(const QString line);
    void parseOrgname(const QString line);
    void parseOKATOTEL(const QString line);
    void parseINN(const QString line);
    void parseFIOTBN(const QString line);
    void parseStatusDrGr(const QString line);
    void parseCodeDocSeriesNum(const QString line);
    void parseIndexRegCode(const QString line);
    void parseCity(const QString line);
    void parseStreet(const QString line);
    void parseHomeFlat(const QString line);
    void parseIncomeTable(const QString line);


public:
    QMap<QString, QString> params;

    Importer(const QString filename);

    static QString OEMtoUnicode(const QString string);
    static QString WINtoUnicode(const QString string);

    void parse();

};

#endif // IMPORTER_H
