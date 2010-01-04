#include "importer.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QStringList>

const QString blankLine = "                                                                                ";

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
    params.insert(QString::number(numberDoc, 10) + "_" + key, value);
}

void Importer::parse()
{
    QFile file(inputFile);

    if (!file.open(QFile::ReadOnly))
        return;
    QTextStream in(&file);
    in.setCodec("IBM 866");

    numberDoc = 1;
    while (!in.atEnd())
    {
        QString line;
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

        fillAddress();
        line = in.readLine();
        while (!line.contains(WINtoUnicode("���")))
        {                        
            if (line.contains(WINtoUnicode("�����")))
                parseCity(line);
            else if (line.contains(WINtoUnicode("�����")))
                parseStreet(line);
            else if (line.contains(WINtoUnicode("���������� �����")))
                parseLocality(line);
            line = in.readLine();
        }
        parseHomeFlat(line);

        in.readLine();
        fillPara29();
        line = in.readLine();
        if (line.left(3) == "2.9")
        {
            parseCoutryCode(line);
            parseAddress(in.readLine());
            in.readLine();
            line = in.readLine();
        }
        parseTax(line); // �. 3
        in.readLine();
        in.readLine();
        in.readLine();
        in.readLine();
        in.readLine();

        line = in.readLine();
        QChar sym(0x2514);

        incomeTableRowsCount = 1;
        while (line[0] != sym)
        {          
            parseIncomeTable(QString::number(incomeTableRowsCount++, 10), line);
            line = in.readLine();           
        }

        in.readLine();

        fillPara4();
        line = in.readLine(); // �. 4

        while (line.left(3) != " 5.")
        {
            QString para = line.left(3);
            if (para == "")
            {
            }
            else if (para == "4. ")
            {
            }
            else if (para == "4.1")
            {
                in.readLine();
                line = in.readLine();
                parseTaxDeductions(line);
            }
            else if (para == "4.2")
            {
                parsePara42(line);
            }
            else if ((para == "4.3") || (para == "4.4"))
            {
                parsePara43_44(line);
            }           
            else if (para == "4.5")
            {
                parsePara45(line);
            }
            else if (para == "4.6")
            {
                parsePara46(line);
            }
            line = in.readLine();
        }

        //in.readLine(); // �. 5       
        fillPara5();
        line = in.readLine();
        while (line[0] != sym)
        {
            QString para = line.mid(1, 4);

            if (para == "5.1.")
                parseAmountIncome(line);   // �. 5.1
            else if (para == "5.2.")
                parseTaxableAmountIncome(line); // �. 5.2
            else if (para == "5.3.")
                parseAmountOfTaxCalculated(line); // �. 5.3
            else if (para == "5.4.")
                parseAmountOfTaxWithheld(line); // �. 5.4
            else if (para == "5.5.")
                parsePara55Sum(line);  // �. 5.5
            else if (para == "5.6.")
                parsePara56Sum(line);  // �. 5.6
            else if (para == "5.7.")
                parsePara57Sum(line);  // �. 5.7
            else if (para == "5.8.")
                parsePara58Sum(line);  // �. 5.8
            else if (para == "5.9.")
                parsePara59Sum(line);  // �. 5.9
            else if (para == "5.10")
                parsePara510Sum(line);  // �. 5.10
            line = in.readLine();
        }
        in.readLine();        
        parseBottom(in.readLine());

        QChar pageBreak(0x0C);
        line = in.readLine();
        while (!in.atEnd() && line != pageBreak)        
            line = in.readLine();

        numberDoc++;
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

void Importer::parseLocality(const QString line)
{
    addParametr("��������", line.right(line.length() - 22).trimmed());
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

void Importer::parseTax(const QString line)
{
    addParametr("������������", line.mid(40, 4).trimmed());

}

void Importer::parseIncomeTable(const QString n, const QString line)
{
    QStringList list1 = line.split(QChar(0x2502));
    //
    addParametr("������_" + n + "_�������_1", list1[1].trimmed());
    addParametr("������_" + n + "_�������_2", list1[2].trimmed());
    addParametr("������_" + n + "_�������_3", list1[3].trimmed());
    addParametr("������_" + n + "_�������_4", list1[4].trimmed());
    addParametr("������_" + n + "_�������v5", list1[5].trimmed());

    addParametr("������_" + n + "_�������_6", list1[7].trimmed());
    addParametr("������_" + n + "_�������_7", list1[8].trimmed());
    addParametr("������_" + n + "_�������_8", list1[9].trimmed());
    addParametr("������_" + n + "_�������_9", list1[10].trimmed());
    addParametr("������_" + n + "_�������_10",list1[11].trimmed());

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

void Importer::fillPara4()
{   
    parseTaxDeductions(blankLine);
    parsePara42(blankLine);
    parsePara43_44(blankLine);
    parsePara45(blankLine);
    parsePara46(blankLine);
}

void Importer::parsePara42(const QString line)
{
    addParametr("����������������", line.right(8).trimmed());
}

void Importer::parsePara43_44(const QString line)
{
    addParametr("���������������������", line.mid(16, 14).trimmed());
    addParametr("������������������", line.right(6).trimmed());
}

void Importer::parsePara45(const QString line)
{
    addParametr("���������������", line.right(14).trimmed());
}

void Importer::parsePara46(const QString line)
{
    addParametr("����������������������������", line.right(14).trimmed());
}

void Importer::fillPara5()
{
    parseAmountIncome(blankLine);   // �. 5.1
    parseTaxableAmountIncome(blankLine); // �. 5.2
    parseAmountOfTaxCalculated(blankLine); // �. 5.3
    parseAmountOfTaxWithheld(blankLine); // �. 5.4
    parsePara55Sum(blankLine);  // �. 5.5
    parsePara56Sum(blankLine);  // �. 5.6
    parsePara57Sum(blankLine);  // �. 5.7
    parsePara58Sum(blankLine);  // �. 5.8
    parsePara59Sum(blankLine);  // �. 5.9
    parsePara510Sum(blankLine);  // �. 5.10
}

void Importer::fillPara29()
{
    parseCoutryCode(blankLine);
    parseAddress(blankLine);
}

void Importer::parseCoutryCode(const QString line)
{
    addParametr("�������������������", line.mid(43, 3).trimmed());
}

void Importer::parseAddress(const QString line)
{
    addParametr("����������������������", line.trimmed());
}

void Importer::fillAddress()
{
    parseCity(blankLine);
    parseLocality(blankLine);
    parseStreet(blankLine);
}
