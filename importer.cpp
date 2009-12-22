#include "importer.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QStringList>

void Importer::debug(const QString line, QChar symb)
{
    QFile file1("1251.txt");
    if (!file1.open(QFile::WriteOnly | QFile::Truncate))
        return;
    QTextStream out(&file1);
    out.setCodec("UTF-8");
    out << "line0 " << line[0].unicode() << " " << symb.unicode();
    file1.close();
}

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
    params.insert(QString::number(currentDoc, 10) + "_" + key, value);
}

void Importer::parse()
{
    QFile file(inputFile);

    if (!file.open(QFile::ReadOnly))
        return;
    QTextStream in(&file);
    in.setCodec("IBM 866");

    currentDoc = 1;
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

        QChar pageBreak(0x0C);
        line = in.readLine();
        while (!in.atEnd() && line != pageBreak)
        {
            line = in.readLine();
        }
        currentDoc++;
    }
    file.close();

}

void Importer::parseTitle(QString line)
{
    QString utfLine = line;//OEMtoUnicode(line);

    addParametr("Year", utfLine.mid(38, 4));
    addParametr("Number", utfLine.mid(49, 2));
    addParametr("Date", utfLine.mid(55, 10));

    QString sIfns = WINtoUnicode("���� N");

    //addParametr("IFNS", utfLine.mid(utfLine.indexOf(sIfns, 55) + sIfns.length() + 1, 4));
    addParametr("IFNS", utfLine.mid(utfLine.indexOf(sIfns) + sIfns.length() + 1, 4).trimmed());

}

void Importer::parseINNCPP(const QString line)
{
    addParametr("INN/CPP", line.mid(25, 22));
}

void Importer::parseOrgname(const QString line)
{
    QString utfLine = line;//OEMtoUnicode(line);
    QString sOrgTitle = WINtoUnicode("������������ �����������");
    addParametr("Orgname", utfLine.right(utfLine.length() - utfLine.indexOf(sOrgTitle) - sOrgTitle.length()));
}

void Importer::parseOKATOTEL(const QString line)
{
    QString utfLine = line;
    QString sOKATO = WINtoUnicode("��� �����");
    addParametr("OKATO", utfLine.mid(utfLine.indexOf(sOKATO) + sOKATO.length() + 1, 12).trimmed());

    QString sTel = WINtoUnicode("�������");
    addParametr("Tel", utfLine.right(utfLine.length() - utfLine.indexOf(sTel) - sTel.length()));
}

void Importer::parseINN(const QString line)
{
     addParametr("INN", line.mid(9, 12));
}

void Importer::parseFIOTBN(const QString line)
{

    addParametr("FIO", line.left(50).trimmed());
    addParametr("TBN", line.right(4).trimmed());
}

void Importer::parseStatusDrGr(const QString line)
{
    addParametr("Status", line.mid(12, 3).trimmed());

    QString sBirthday = WINtoUnicode("���� ��������");
    addParametr("Birthday", line.mid(line.indexOf(sBirthday) + sBirthday.length() + 1, 15).trimmed());

    addParametr("Grajdanstvo", line.right(3));
}

void Importer::parseCodeDocSeriesNum(const QString line)
{
    QString subStr = WINtoUnicode("��� ���-��, �����. �������� -");
    addParametr("CodeDoc", line.mid(line.indexOf(subStr) + subStr.length() + 1, 3).trimmed());

    addParametr("SeriesAndNumberDoc", line.right(16).trimmed());

}

void Importer::parseIndexRegCode(const QString line)
{
    QString subStr = WINtoUnicode("�������� ������");
    addParametr("Index", line.mid(line.indexOf(subStr) + subStr.length() + 1, 6).trimmed());

    subStr = WINtoUnicode("��� �������");
    addParametr("RegCode", line.mid(line.indexOf(subStr) + subStr.length() + 1, 2).trimmed());

    subStr = WINtoUnicode("�����");
    addParametr("Raion", line.mid(line.indexOf(subStr) + subStr.length() + 1, 28).trimmed());
}

void Importer::parseCity(const QString line)
{
    addParametr("City", line.right(line.length() - 10).trimmed());
}

void Importer::parseStreet(const QString line)
{
    addParametr("Street", line.right(line.length() - 10).trimmed());
}

void Importer::parseHomeFlat(const QString line)
{
    QString subStr = WINtoUnicode("���");
    addParametr("���", line.mid(line.indexOf(subStr) + subStr.length() + 1, 6).trimmed());

    subStr = WINtoUnicode("������");
    addParametr("������", line.mid(line.indexOf(subStr) + subStr.length() + 1, 3).trimmed());

    subStr = WINtoUnicode("��������");
    addParametr("��������", line.mid(line.indexOf(subStr) + subStr.length() + 1, 3).trimmed());

}

void Importer::parseIncomeTable(const QString line)
{
    QStringList list1 = line.split(QChar(0x2502));
    //
    addParametr("�����" + list1[1].trimmed() + list1[2].trimmed(),        list1[1].trimmed());
    addParametr("���������" + list1[1].trimmed() + list1[2].trimmed(),    list1[2].trimmed());
    addParametr("�����������" + list1[1].trimmed() + list1[2].trimmed(),  list1[3].trimmed());
    addParametr("���������" + list1[1].trimmed() + list1[2].trimmed(),    list1[4].trimmed());
    addParametr("�����������" + list1[1].trimmed() + list1[2].trimmed(),  list1[5].trimmed());

    addParametr("�����" + list1[7].trimmed() + list1[8].trimmed(),        list1[7].trimmed());
    addParametr("���������" + list1[7].trimmed() + list1[8].trimmed(),    list1[8].trimmed());
    addParametr("�����������" + list1[7].trimmed() + list1[8].trimmed(),  list1[9].trimmed());
    addParametr("���������" + list1[7].trimmed() + list1[8].trimmed(),    list1[10].trimmed());
    addParametr("�����������" + list1[7].trimmed() + list1[8].trimmed(),  list1[11].trimmed());

}

void Importer::parseTaxDeductions(const QString line)
{
    //QStringList list1 = line.split(" ");
    addParametr("���4.1", line.mid(2, 4).trimmed());
    addParametr("�����������4.1", line.mid(8, 12).trimmed());

    addParametr("���4.2", line.mid(22, 3).trimmed());
    addParametr("�����������4.2", line.mid(27, 12).trimmed());

    addParametr("���4.3", line.mid(41, 3).trimmed());
    addParametr("�����������4.3", line.mid(46, 12).trimmed());

    addParametr("���4.4", line.mid(60, 3).trimmed());
    addParametr("�����������4.4", line.mid(65, 12).trimmed());
}

void Importer::parseTotalSum(const QString line)
{
    addParametr("���������������", line.right(14).trimmed());
}

void Importer::parseAmountIncome(const QString line)
{
    addParametr("������������", line.mid(66, 12).trimmed());
}

void Importer::parseTaxableAmountIncome(const QString line)
{
    addParametr("����������������������", line.mid(66, 12).trimmed());
}

void Importer::parseAmountOfTaxCalculated(const QString line)
{
    addParametr("������5.3", line.mid(66, 12).trimmed());
}

void Importer::parseAmountOfTaxWithheld(const QString line)
{
    addParametr("������5.4", line.mid(66, 12).trimmed());
}

void Importer::parsePara55Sum(const QString line)
{
    addParametr("������5.5", line.mid(66, 12).trimmed());
}

void Importer::parsePara56Sum(const QString line)
{
    addParametr("������5.6", line.mid(66, 12).trimmed());
}

void Importer::parsePara57Sum(const QString line)
{
    addParametr("������5.7", line.mid(66, 12).trimmed());
}

void Importer::parsePara58Sum(const QString line)
{
    addParametr("������5.8", line.mid(66, 12).trimmed());
}

void Importer::parsePara59Sum(const QString line)
{
    addParametr("������5.9", line.mid(66, 12).trimmed());
}

void Importer::parsePara510Sum(const QString line)
{
    addParametr("������5.10", line.mid(66, 12).trimmed());
}

void Importer::parseBottom(const QString line)
{
    addParametr("���������", line.mid(17, 20).trimmed());
    addParametr("���������", line.mid(57, 20).trimmed());
}
