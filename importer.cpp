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

void Importer::addParametr(const QString key, const QString value)
{
    params.insert(currentDoc + "_" + key, value);
}

void Importer::parse()
{
    QFile file(inputFile);

    if (!file.open(QFile::ReadOnly))
        return;
    QTextStream in(&file);
    in.setCodec("IBM 866");

    int i = 1;
    while (!in.atEnd())
    {
        in.readLine(); // �����
        in.readLine(); //
        in.readLine();

        parseTitle(in.readLine()); // ������ � ����� � ������� �������
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
        in.readLine();
        in.readLine();
        in.readLine();
        in.readLine();
        in.readLine();

        QString line = in.readLine();
        QChar sym(0x2514);

        while (line[0] != sym)
        {
            parseIncomeTable(line);
            line = in.readLine();
        }

        in.readLine();
        in.readLine();
        in.readLine();
        in.readLine();
        //in.readLine();
        parseTaxDeductions(in.readLine());  // �. 4.1
        parseTotalSum(in.readLine());       // �. 4.5

        in.readLine(); // �. 5
        in.readLine();
        in.readLine();

        parseAmountIncome(in.readLine());   // �. 5.1
        in.readLine();
        parseTaxableAmountIncome(in.readLine()); // �. 5.2
        in.readLine();
        parseAmountOfTaxCalculated(in.readLine()); // �. 5.3
        in.readLine();
        parseAmountOfTaxWithheld(in.readLine()); // �. 5.4
        in.readLine();
        parsePara55Sum(in.readLine());  // �. 5.5
        in.readLine();
        parsePara56Sum(in.readLine());  // �. 5.6
        in.readLine();
        parsePara57Sum(in.readLine());  // �. 5.7
        in.readLine();
        parsePara58Sum(in.readLine());  // �. 5.8
        in.readLine();
        parsePara59Sum(in.readLine());  // �. 5.8
        in.readLine();
        parsePara510Sum(in.readLine());  // �. 5.10
        in.readLine();
        in.readLine();
        parseBottom(in.readLine());
        in.readLine();
    }
    file.close();

}

void Importer::parseTitle(QString line)
{
    QString utfLine = line;//OEMtoUnicode(line);

    params.insert("Year", utfLine.mid(38, 4));
    params.insert("Number", utfLine.mid(49, 2));
    params.insert("Date", utfLine.mid(55, 10));

    QString sIfns = WINtoUnicode("���� N");

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
    QString sOrgTitle = WINtoUnicode("������������ �����������");
    params.insert("Orgname", utfLine.right(utfLine.length() - utfLine.indexOf(sOrgTitle) - sOrgTitle.length()));
}

void Importer::parseOKATOTEL(const QString line)
{
    QString utfLine = line;
    QString sOKATO = WINtoUnicode("��� �����");
    params.insert("OKATO", utfLine.mid(utfLine.indexOf(sOKATO) + sOKATO.length() + 1, 12).trimmed());

    QString sTel = WINtoUnicode("�������");
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
    params.insert("�����" + list1[1].trimmed() + list1[2].trimmed(),        list1[1].trimmed());
    params.insert("���������" + list1[1].trimmed() + list1[2].trimmed(),    list1[2].trimmed());
    params.insert("�����������" + list1[1].trimmed() + list1[2].trimmed(),  list1[3].trimmed());
    params.insert("���������" + list1[1].trimmed() + list1[2].trimmed(),    list1[4].trimmed());
    params.insert("�����������" + list1[1].trimmed() + list1[2].trimmed(),  list1[5].trimmed());

    params.insert("�����" + list1[7].trimmed() + list1[8].trimmed(),        list1[7].trimmed());
    params.insert("���������" + list1[7].trimmed() + list1[8].trimmed(),    list1[8].trimmed());
    params.insert("�����������" + list1[7].trimmed() + list1[8].trimmed(),  list1[9].trimmed());
    params.insert("���������" + list1[7].trimmed() + list1[8].trimmed(),    list1[10].trimmed());
    params.insert("�����������" + list1[7].trimmed() + list1[8].trimmed(),  list1[11].trimmed());

}

void Importer::parseTaxDeductions(const QString line)
{
    //QStringList list1 = line.split(" ");
    params.insert("���4.1", line.mid(2, 4).trimmed());
    params.insert("�����������4.1", line.mid(8, 12).trimmed());

    params.insert("���4.2", line.mid(22, 3).trimmed());
    params.insert("�����������4.2", line.mid(27, 12).trimmed());

    params.insert("���4.3", line.mid(41, 3).trimmed());
    params.insert("�����������4.3", line.mid(46, 12).trimmed());

    params.insert("���4.4", line.mid(60, 3).trimmed());
    params.insert("�����������4.4", line.mid(65, 12).trimmed());
}

void Importer::parseTotalSum(const QString line)
{
    params.insert("���������������", line.right(14).trimmed());
}

void Importer::parseAmountIncome(const QString line)
{
    params.insert("������������", line.mid(66, 12).trimmed());
}

void Importer::parseTaxableAmountIncome(const QString line)
{
    params.insert("����������������������", line.mid(66, 12).trimmed());
}

void Importer::parseAmountOfTaxCalculated(const QString line)
{
    params.insert("������5.3", line.mid(66, 12).trimmed());
}

void Importer::parseAmountOfTaxWithheld(const QString line)
{
    params.insert("������5.4", line.mid(66, 12).trimmed());
}

void Importer::parsePara55Sum(const QString line)
{
    params.insert("������5.5", line.mid(66, 12).trimmed());
}

void Importer::parsePara56Sum(const QString line)
{
    params.insert("������5.6", line.mid(66, 12).trimmed());
}

void Importer::parsePara57Sum(const QString line)
{
    params.insert("������5.7", line.mid(66, 12).trimmed());
}

void Importer::parsePara58Sum(const QString line)
{
    params.insert("������5.8", line.mid(66, 12).trimmed());
}

void Importer::parsePara59Sum(const QString line)
{
    params.insert("������5.9", line.mid(66, 12).trimmed());
}

void Importer::parsePara510Sum(const QString line)
{
    params.insert("������5.10", line.mid(66, 12).trimmed());
}

void Importer::parseBottom(const QString line)
{
    params.insert("���������", line.mid(17, 20).trimmed());
    params.insert("���������", line.mid(57, 20).trimmed());
}
