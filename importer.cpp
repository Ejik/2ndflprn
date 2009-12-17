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

    in.readLine(); // �����
    in.readLine(); //
    in.readLine();
    QString line = in.readLine(); // ������ � ����� � ������� �������
    parseTitle(line);
    in.readLine(); //
    in.readLine(); // �. 1
    parseINNCPP(in.readLine());  // �. 1.1
    parseOrgname(in.readLine()); // �. 1.2
    in.readLine();
    parseOKATOTEL(in.readLine()); // �. 1.3 �. 1.4
    in.readLine(); // �. 2
    parseINN(in.readLine()); // �. 2.1
    in.readLine();
    parseFIOTBN(in.readLine()); // �. 2.2
    parseStatusDrGr(in.readLine()); // �. 2.3 - �. 2.5
    parseCodeDocSeriesNum(in.readLine()); // �. 2.6 - �. 2.7
    in.readLine(); // �. 2.8
    parseIndexRegCode(in.readLine());
    parseCity(in.readLine());
    parseStreet(in.readLine());
    parseHomeFlat(in.readLine());
    in.readLine();
    in.readLine(); // �. 3

}

void Importer::parseTitle(QString line)
{
    QString utfLine = line;//OEMtoUnicode(line);

    params.insert("Year", utfLine.mid(38, 4));
    params.insert("Number", utfLine.mid(49, 2));
    params.insert("Date", utfLine.mid(55, 10));

    QString sIfns = WINtoUnicode("���� N");

    params.insert("IFNS", utfLine.mid(utfLine.indexOf(sIfns, 55) + sIfns.length() + 1, 4));
}

void Importer::parseINNCPP(const QString line)
{
    params.insert("INN/CPP", line.mid(25, 22));
}

void Importer::parseOrgname(const QString line)
{
    QString utfLine = line; //OEMtoUnicode(line);
    QString sOrgTitle = WINtoUnicode("������������ ����������� ");
    params.insert("Orgname", utfLine.right(utfLine.length() - utfLine.indexOf(sOrgTitle) - sOrgTitle.length()));
}

void Importer::parseOKATOTEL(const QString line)
{
    QString sOKATO = WINtoUnicode("��� �����");
    params.insert("OKATO", line.mid(line.indexOf(sOKATO) + sOKATO.length() + 1, 12));

    QString sTel = WINtoUnicode("�������");
    params.insert("Tel", line.right(line.length() - line.indexOf(sTel) - sTel.length()));
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

    QString sBirthday = WINtoUnicode("���� ��������");
    params.insert("Birthday", line.mid(line.indexOf(sBirthday) + sBirthday.length() + 1, 15).trimmed());

    params.insert("Grajdanstvo", line.right(3));
}

void Importer::parseCodeDocSeriesNum(const QString line)
{
    QString subStr = WINtoUnicode("��� ���-��, �����. �������� -");
    params.insert("CodeDoc", line.mid(line.indexOf(subStr) + subStr.length() + 1, 3).trimmed());

    params.insert("SeriesAndNumberDoc", line.right(16).trimmed());

}
void Importer::parseIndexRegCode(const QString line)
{
    QString subStr = WINtoUnicode("�������� ������");
    params.insert("Index", line.mid(line.indexOf(subStr) + subStr.length() + 1, 6).trimmed());

    subStr = WINtoUnicode("��� �������");
    params.insert("RegCode", line.mid(line.indexOf(subStr) + subStr.length() + 1, 2).trimmed());

    subStr = WINtoUnicode("�����");
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
    QString subStr = WINtoUnicode("���");
    params.insert("���", line.mid(line.indexOf(subStr) + subStr.length() + 1, 6).trimmed());

    subStr = WINtoUnicode("������");
    params.insert("������", line.mid(line.indexOf(subStr) + subStr.length() + 1, 3).trimmed());

    subStr = WINtoUnicode("��������");
    params.insert("��������", line.mid(line.indexOf(subStr) + subStr.length() + 1, 3).trimmed());

}
