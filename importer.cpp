#include "importer.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>

Importer::Importer(QString filename)
{
    inputFile = filename;
}

QString Importer::OEMtoUnicode(const QString string)
{
    QTextCodec *codec = QTextCodec::codecForName("IBM 866");
      return codec->toUnicode(string.toLocal8Bit());
}

QString Importer::WINtoUnicode(const QString string)
{
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    return codec->toUnicode(string.toAscii());
}

void Importer::parse()
{
    QFile file(inputFile);

    if (!file.open(QFile::ReadOnly))
        return;
    QTextStream in(&file);

    in.readLine(); // шапка
    in.readLine();
    in.readLine();
    QString line = in.readLine(); // Строка с датой и номером справки
    parseTitle(line);
    in.readLine(); //
    in.readLine(); // п 1.1
    parseINNCPP(in.readLine());  // п 1.2
    parseOrgname(in.readLine()); // п 1.3

}

void Importer::parseTitle(QString line)
{
    QString utfLine = OEMtoUnicode(line);

    params.insert("Year", utfLine.mid(38, 4));
    params.insert("Number", utfLine.mid(49, 2));
    params.insert("Date", utfLine.mid(55, 10));

    QString sIfns = WINtoUnicode("ИФНС N");

    params.insert("IFNS", utfLine.mid(utfLine.indexOf(sIfns, 55) + sIfns.length() + 1, 4));
}

void Importer::parseINNCPP(const QString line)
{
    params.insert("INN/CPP", line.mid(25, 22));
}

void Importer::parseOrgname(const QString line)
{
    QString utfLine = OEMtoUnicode(line);
    QString sOrgTitle = WINtoUnicode("Наименование организации ");
    params.insert("Orgname", utfLine.right(utfLine.length() - (utfLine.indexOf(sOrgTitle) - sOrgTitle.length())));

}
