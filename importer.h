#ifndef IMPORTER_H
#define IMPORTER_H

#include <QObject>
#include <QMap>

class Importer : public QObject
{
private:

    void addParametr(const QString key, const QString value);
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
    void parseLocality(const QString line);
    void parseStreet(const QString line);
    void parseHomeFlat(const QString line);
    void parseTax(const QString line);
    void parseIncomeTable(const QString n, const QString line);
    void parseTaxDeductions(const QString line);
    void parseAmountIncome(const QString line);
    void parseTaxableAmountIncome(const QString line);
    void parseAmountOfTaxCalculated(const QString line);
    void parseAmountOfTaxWithheld(const QString line);
    void parsePara55Sum(const QString line);
    void parsePara56Sum(const QString line);
    void parsePara57Sum(const QString line);
    void parsePara58Sum(const QString line);
    void parsePara59Sum(const QString line);
    void parsePara510Sum(const QString line);
    void parseBottom(const QString line);

    void fillPara4();
    void parsePara42(const QString line);
    void parsePara43_44(const QString line);
    void parsePara45(const QString line);
    void parsePara46(const QString line);

    void fillPara5();
    void parseCoutryCode(const QString line);
    void parseAddress(const QString line);
    void fillPara29();
    void fillAddress();

    void debug(const QString line, QChar symb);

public:
    QMap<QString, QString> params;
    int incomeTableRowsCount;
    int numberDoc;
    QString inputFile;

    Importer(const QString filename);

    static QString OEMtoUnicode(const QString string);
    static QString WINtoUnicode(const QString string);

    void parse();

};

#endif // IMPORTER_H
