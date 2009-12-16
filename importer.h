#ifndef IMPORTER_H
#define IMPORTER_H

#include <QObject>
#include <QMap>

class Importer : public QObject
{
private:
    QString inputFile;
    QString OEMtoUnicode(const QString string);
    QString WINtoUnicode(const QString string);

public:
    QMap<QString, QString> params;

    Importer(const QString filename);
    void parse();
    void parseTitle(const QString line);
    void parseINNCPP(const QString line);
};

#endif // IMPORTER_H
