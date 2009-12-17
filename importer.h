#ifndef IMPORTER_H
#define IMPORTER_H

#include <QObject>
#include <QMap>

class Importer : public QObject
{
private:
    QString inputFile;

public:
    QMap<QString, QString> params;

    Importer(const QString filename);

    static QString OEMtoUnicode(const QString string);
    static QString WINtoUnicode(const QString string);

    void parse();
    void parseTitle(const QString line);
    void parseINNCPP(const QString line);
    void parseOrgname(const QString line);
};

#endif // IMPORTER_H
