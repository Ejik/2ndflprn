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

        fillAddress();
        line = in.readLine();
        while (!line.contains(WINtoUnicode("Дом")))
        {                        
            if (line.contains(WINtoUnicode("Город")))
                parseCity(line);
            else if (line.contains(WINtoUnicode("Улица")))
                parseStreet(line);
            else if (line.contains(WINtoUnicode("Населенный пункт")))
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
        parseTax(line); // п. 3
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
        line = in.readLine(); // п. 4

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

        //in.readLine(); // п. 5       
        fillPara5();
        line = in.readLine();
        while (line[0] != sym)
        {
            QString para = line.mid(1, 4);

            if (para == "5.1.")
                parseAmountIncome(line);   // п. 5.1
            else if (para == "5.2.")
                parseTaxableAmountIncome(line); // п. 5.2
            else if (para == "5.3.")
                parseAmountOfTaxCalculated(line); // п. 5.3
            else if (para == "5.4.")
                parseAmountOfTaxWithheld(line); // п. 5.4
            else if (para == "5.5.")
                parsePara55Sum(line);  // п. 5.5
            else if (para == "5.6.")
                parsePara56Sum(line);  // п. 5.6
            else if (para == "5.7.")
                parsePara57Sum(line);  // п. 5.7
            else if (para == "5.8.")
                parsePara58Sum(line);  // п. 5.8
            else if (para == "5.9.")
                parsePara59Sum(line);  // п. 5.9
            else if (para == "5.10")
                parsePara510Sum(line);  // п. 5.10
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

    QString sIfns = WINtoUnicode("ИФНС N");

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
    QString sOrgTitle = WINtoUnicode("Наименование организации");
    addParametr("Orgname", utfLine.right(utfLine.length() - utfLine.indexOf(sOrgTitle) - sOrgTitle.length()));
}

void Importer::parseOKATOTEL(const QString line)
{
    QString utfLine = line;
    QString sOKATO = WINtoUnicode("Код ОКАТО");
    addParametr("OKATO", utfLine.mid(utfLine.indexOf(sOKATO) + sOKATO.length() + 1, 12).trimmed());

    QString sTel = WINtoUnicode("Телефон");
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

    QString sBirthday = WINtoUnicode("Дата рождения");
    addParametr("Birthday", line.mid(line.indexOf(sBirthday) + sBirthday.length() + 1, 15).trimmed());

    addParametr("Grajdanstvo", line.right(3));
}

void Importer::parseCodeDocSeriesNum(const QString line)
{
    QString subStr = WINtoUnicode("Код док-та, удост. личность -");
    addParametr("CodeDoc", line.mid(line.indexOf(subStr) + subStr.length() + 1, 3).trimmed());

    addParametr("SeriesAndNumberDoc", line.right(16).trimmed());

}

void Importer::parseIndexRegCode(const QString line)
{
    QString subStr = WINtoUnicode("Почтовый индекс");
    addParametr("Index", line.mid(line.indexOf(subStr) + subStr.length() + 1, 6).trimmed());

    subStr = WINtoUnicode("Код региона");
    addParametr("RegCode", line.mid(line.indexOf(subStr) + subStr.length() + 1, 2).trimmed());

    subStr = WINtoUnicode("Район");
    addParametr("Raion", line.mid(line.indexOf(subStr) + subStr.length() + 1, 28).trimmed());
}

void Importer::parseCity(const QString line)
{
    addParametr("City", line.right(line.length() - 10).trimmed());
}

void Importer::parseLocality(const QString line)
{
    addParametr("НасПункт", line.right(line.length() - 22).trimmed());
}

void Importer::parseStreet(const QString line)
{
    addParametr("Street", line.right(line.length() - 10).trimmed());
}

void Importer::parseHomeFlat(const QString line)
{
    QString subStr = WINtoUnicode("Дом");
    addParametr("Дом", line.mid(line.indexOf(subStr) + subStr.length() + 1, 6).trimmed());

    subStr = WINtoUnicode("Корпус");
    addParametr("Корпус", line.mid(line.indexOf(subStr) + subStr.length() + 1, 3).trimmed());

    subStr = WINtoUnicode("Квартира");
    addParametr("Квартира", line.mid(line.indexOf(subStr) + subStr.length() + 1, 3).trimmed());

}

void Importer::parseTax(const QString line)
{
    addParametr("СтавкаНалога", line.mid(40, 4).trimmed());

}

void Importer::parseIncomeTable(const QString n, const QString line)
{
    QStringList list1 = line.split(QChar(0x2502));
    //
    addParametr("Строка_" + n + "_Столбец_1", list1[1].trimmed());
    addParametr("Строка_" + n + "_Столбец_2", list1[2].trimmed());
    addParametr("Строка_" + n + "_Столбец_3", list1[3].trimmed());
    addParametr("Строка_" + n + "_Столбец_4", list1[4].trimmed());
    addParametr("Строка_" + n + "_Столбецv5", list1[5].trimmed());

    addParametr("Строка_" + n + "_Столбец_6", list1[7].trimmed());
    addParametr("Строка_" + n + "_Столбец_7", list1[8].trimmed());
    addParametr("Строка_" + n + "_Столбец_8", list1[9].trimmed());
    addParametr("Строка_" + n + "_Столбец_9", list1[10].trimmed());
    addParametr("Строка_" + n + "_Столбец_10",list1[11].trimmed());

}

void Importer::parseTaxDeductions(const QString line)
{
    //QStringList list1 = line.split(" ");
    addParametr("Код4.1", line.mid(2, 4).trimmed());
    addParametr("СуммаВычета4.1", line.mid(8, 12).trimmed());

    addParametr("Код4.2", line.mid(22, 3).trimmed());
    addParametr("СуммаВычета4.2", line.mid(27, 12).trimmed());

    addParametr("Код4.3", line.mid(41, 3).trimmed());
    addParametr("СуммаВычета4.3", line.mid(46, 12).trimmed());

    addParametr("Код4.4", line.mid(60, 3).trimmed());
    addParametr("СуммаВычета4.4", line.mid(65, 12).trimmed());
}

void Importer::parseAmountIncome(const QString line)
{
    addParametr("СуммаДоходов", line.mid(66, 12).trimmed());
}

void Importer::parseTaxableAmountIncome(const QString line)
{
    addParametr("ОблагаемаяСуммаДоходов", line.mid(66, 12).trimmed());
}

void Importer::parseAmountOfTaxCalculated(const QString line)
{
    addParametr("СуммаП5.3", line.mid(66, 12).trimmed());
}

void Importer::parseAmountOfTaxWithheld(const QString line)
{
    addParametr("СуммаП5.4", line.mid(66, 12).trimmed());
}

void Importer::parsePara55Sum(const QString line)
{
    addParametr("СуммаП5.5", line.mid(66, 12).trimmed());
}

void Importer::parsePara56Sum(const QString line)
{
    addParametr("СуммаП5.6", line.mid(66, 12).trimmed());
}

void Importer::parsePara57Sum(const QString line)
{
    addParametr("СуммаП5.7", line.mid(66, 12).trimmed());
}

void Importer::parsePara58Sum(const QString line)
{
    addParametr("СуммаП5.8", line.mid(66, 12).trimmed());
}

void Importer::parsePara59Sum(const QString line)
{
    addParametr("СуммаП5.9", line.mid(66, 12).trimmed());
}

void Importer::parsePara510Sum(const QString line)
{
    addParametr("СуммаП5.10", line.mid(66, 12).trimmed());
}

void Importer::parseBottom(const QString line)
{
    addParametr("Должность", line.mid(17, 20).trimmed());
    addParametr("ФИОАгента", line.mid(57, 20).trimmed());
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
    addParametr("НомерУведомления", line.right(8).trimmed());
}

void Importer::parsePara43_44(const QString line)
{
    addParametr("ДатаВыдачиУведомления", line.mid(16, 14).trimmed());
    addParametr("КодИФНСУведомления", line.right(6).trimmed());
}

void Importer::parsePara45(const QString line)
{
    addParametr("СуммаНалВычетов", line.right(14).trimmed());
}

void Importer::parsePara46(const QString line)
{
    addParametr("СуммаИмущественныхНалВычетов", line.right(14).trimmed());
}

void Importer::fillPara5()
{
    parseAmountIncome(blankLine);   // п. 5.1
    parseTaxableAmountIncome(blankLine); // п. 5.2
    parseAmountOfTaxCalculated(blankLine); // п. 5.3
    parseAmountOfTaxWithheld(blankLine); // п. 5.4
    parsePara55Sum(blankLine);  // п. 5.5
    parsePara56Sum(blankLine);  // п. 5.6
    parsePara57Sum(blankLine);  // п. 5.7
    parsePara58Sum(blankLine);  // п. 5.8
    parsePara59Sum(blankLine);  // п. 5.9
    parsePara510Sum(blankLine);  // п. 5.10
}

void Importer::fillPara29()
{
    parseCoutryCode(blankLine);
    parseAddress(blankLine);
}

void Importer::parseCoutryCode(const QString line)
{
    addParametr("КодСтраныПроживания", line.mid(43, 3).trimmed());
}

void Importer::parseAddress(const QString line)
{
    addParametr("АдресВСтранеПроживания", line.trimmed());
}

void Importer::fillAddress()
{
    parseCity(blankLine);
    parseLocality(blankLine);
    parseStreet(blankLine);
}
