#include "importer.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QStringList>

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
    in.setCodec("IBM 866");

    in.readLine(); // шапка
    in.readLine(); //
    in.readLine();

    parseTitle(in.readLine()); // Строка с датой и номером справки
    in.readLine(); //
    in.readLine(); // п. 1
    parseINNCPP(in.readLine());  // п. 1.1
    parseOrgname(in.readLine()); // п. 1.2
    in.readLine();
    parseOKATOTEL(in.readLine()); // п. 1.3 п. 1.4
    in.readLine(); // п. 2
    parseINN(in.readLine()); // п. 2.1
    in.readLine();
    parseFIOTBN(in.readLine()); // п. 2.2
    parseStatusDrGr(in.readLine()); // п. 2.3 - п. 2.5
    parseCodeDocSeriesNum(in.readLine()); // п. 2.6 - п. 2.7
    in.readLine(); // п. 2.8
    parseIndexRegCode(in.readLine());
    parseCity(in.readLine());
    parseStreet(in.readLine());
    parseHomeFlat(in.readLine());
    in.readLine();
    in.readLine(); // п. 3
    in.readLine();
    in.readLine();
    in.readLine();
    in.readLine();
    in.readLine();

    QString line = in.readLine();
    QString sym("L");

    while (QString(line[0]).toLocal8Bit() !=  sym)
    {
        parseIncomeTable(line);
        line = in.readLine();
    }


    file.close();

}

void Importer::parseTitle(QString line)
{
    QString utfLine = line;//OEMtoUnicode(line);

    params.insert("Year", utfLine.mid(38, 4));
    params.insert("Number", utfLine.mid(49, 2));
    params.insert("Date", utfLine.mid(55, 10));

    QString sIfns = WINtoUnicode("ИФНС N");

    //params.insert("IFNS", utfLine.mid(utfLine.indexOf(sIfns, 55) + sIfns.length() + 1, 4));
    params.insert("IFNS", utfLine.mid(utfLine.indexOf(sIfns) + sIfns.length() + 1, 4).trimmed());

}

void Importer::parseINNCPP(const QString line)
{
    params.insert("INN/CPP", line.mid(25, 22));
}

void Importer::parseOrgname(const QString line)
{
    QString utfLine = line;//OEMtoUnicode(line);
    QString sOrgTitle = WINtoUnicode("Наименование организации");
    params.insert("Orgname", utfLine.right(utfLine.length() - utfLine.indexOf(sOrgTitle) - sOrgTitle.length()));
}

void Importer::parseOKATOTEL(const QString line)
{
    QString utfLine = line;
    QString sOKATO = WINtoUnicode("Код ОКАТО");
    params.insert("OKATO", utfLine.mid(utfLine.indexOf(sOKATO) + sOKATO.length() + 1, 12).trimmed());

    QString sTel = WINtoUnicode("Телефон");
    params.insert("Tel", utfLine.right(utfLine.length() - utfLine.indexOf(sTel) - sTel.length()));
}

void Importer::parseINN(const QString line)
{
     params.insert("INN", line.mid(9, 12));
}

void Importer::parseFIOTBN(const QString line)
{

    params.insert("FIO", line.left(50).trimmed());
    params.insert("TBN", line.right(4).trimmed());
}

void Importer::parseStatusDrGr(const QString line)
{
    params.insert("Status", line.mid(12, 3).trimmed());

    QString sBirthday = WINtoUnicode("Дата рождения");
    params.insert("Birthday", line.mid(line.indexOf(sBirthday) + sBirthday.length() + 1, 15).trimmed());

    params.insert("Grajdanstvo", line.right(3));
}

void Importer::parseCodeDocSeriesNum(const QString line)
{
    QString subStr = WINtoUnicode("Код док-та, удост. личность -");
    params.insert("CodeDoc", line.mid(line.indexOf(subStr) + subStr.length() + 1, 3).trimmed());

    params.insert("SeriesAndNumberDoc", line.right(16).trimmed());

}
void Importer::parseIndexRegCode(const QString line)
{
    QString subStr = WINtoUnicode("Почтовый индекс");
    params.insert("Index", line.mid(line.indexOf(subStr) + subStr.length() + 1, 6).trimmed());

    subStr = WINtoUnicode("Код региона");
    params.insert("RegCode", line.mid(line.indexOf(subStr) + subStr.length() + 1, 2).trimmed());

    subStr = WINtoUnicode("Район");
    params.insert("Raion", line.mid(line.indexOf(subStr) + subStr.length() + 1, 28).trimmed());
}

void Importer::parseCity(const QString line)
{
    params.insert("City", line.right(line.length() - 10).trimmed());
}

void Importer::parseStreet(const QString line)
{
    params.insert("Street", line.right(line.length() - 10).trimmed());
}

void Importer::parseHomeFlat(const QString line)
{
    QString subStr = WINtoUnicode("Дом");
    params.insert("Дом", line.mid(line.indexOf(subStr) + subStr.length() + 1, 6).trimmed());

    subStr = WINtoUnicode("Корпус");
    params.insert("Корпус", line.mid(line.indexOf(subStr) + subStr.length() + 1, 3).trimmed());

    subStr = WINtoUnicode("Квартира");
    params.insert("Квартира", line.mid(line.indexOf(subStr) + subStr.length() + 1, 3).trimmed());

}

void Importer::parseIncomeTable(const QString line)
{
//    QFile file("1251.txt");
//    if (!file.open(QFile::WriteOnly | QFile::Truncate))
//        return;
//    QTextStream out(&file);
//    out.setCodec("UTF-8");
//    out << "line0 " << line[0] << " " << QChar(0x2502);

    QStringList list1 = line.split(QChar(0x2502));
    //
    params.insert("Месяц" + list1[1].trimmed() + list1[2].trimmed(),        list1[1].trimmed());
    params.insert("КодДохода" + list1[1].trimmed() + list1[2].trimmed(),    list1[2].trimmed());
    params.insert("СуммаДохода" + list1[1].trimmed() + list1[2].trimmed(),  list1[3].trimmed());
    params.insert("КодВычета" + list1[1].trimmed() + list1[2].trimmed(),    list1[4].trimmed());
    params.insert("СуммаВычета" + list1[1].trimmed() + list1[2].trimmed(),  list1[5].trimmed());

    params.insert("Месяц" + list1[7].trimmed() + list1[8].trimmed(),        list1[7].trimmed());
    params.insert("КодДохода" + list1[7].trimmed() + list1[8].trimmed(),    list1[8].trimmed());
    params.insert("СуммаДохода" + list1[7].trimmed() + list1[8].trimmed(),  list1[9].trimmed());
    params.insert("КодВычета" + list1[7].trimmed() + list1[8].trimmed(),    list1[10].trimmed());
    params.insert("СуммаВычета" + list1[7].trimmed() + list1[8].trimmed(),  list1[11].trimmed());

}
