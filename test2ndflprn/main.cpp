#include <QtCore/QCoreApplication>
#include <QFile>
#include <QtTest/QtTest>
#include "../importer.h"
#include "../exporter.h"

class Test2ndflprn : public QObject
{
    Q_OBJECT

private slots:
    // importer
    void testParsing();
    void testTableEndSymbol();

    // excel exporter
    void testReplaceExtensions();

};


void Test2ndflprn::testParsing()
{
    Importer importer("2NDFL_01.LST");
    importer.parse();

    QVERIFY(importer.params["1_Year"] == "2009");
    QVERIFY(importer.params["1_Number"] == " 1");
    QVERIFY(importer.params["1_Date"] == "13.12.2009");
    QVERIFY(importer.params["1_IFNS"] == "5190");
    QVERIFY(importer.params["1_INN/CPP"].trimmed() == "5190309146/519001001");
    QVERIFY(importer.params["1_Orgname"].trimmed() == Importer::WINtoUnicode("��� '����-����� C�����'"));
    QVERIFY(importer.params["1_OKATO"].trimmed() == "47401367000");
    QVERIFY(importer.params["1_Tel"].trimmed() == "45-04-27");
    QVERIFY(importer.params["1_INN"].trimmed() == "519041604350");
    QVERIFY(importer.params["1_FIO"].trimmed() == Importer::WINtoUnicode("������� ������� ���������"));
    QVERIFY(importer.params["1_TBN"].trimmed() == "0102");
    QVERIFY(importer.params["1_Status"].trimmed() == "1");
    QVERIFY(importer.params["1_Birthday"].trimmed() == Importer::WINtoUnicode("03.10.1980 �."));
    QVERIFY(importer.params["1_Grajdanstvo"].trimmed() == "643");
    QVERIFY(importer.params["1_CodeDoc"].trimmed() == "21");
    QVERIFY(importer.params["1_SeriesAndNumberDoc"].trimmed() == "47 04  915496");
    QVERIFY(importer.params["1_Index"].trimmed() == "183053");
    QVERIFY(importer.params["1_RegCode"].trimmed() == "51");
    QVERIFY(importer.params["1_Raion"].trimmed() == "");
    QVERIFY(importer.params["1_City"].trimmed() == Importer::WINtoUnicode("�������� �"));
    QVERIFY(importer.params["1_Street"].trimmed() == Importer::WINtoUnicode("�������� ��"));
    QVERIFY(importer.params["1_���"].trimmed() == "47");
    QVERIFY(importer.params["1_������"].trimmed() == "");
    QVERIFY(importer.params["1_��������"].trimmed() == "27");

    QVERIFY(importer.params["1_������������"] == "13");
    QVERIFY(importer.params["1_������_1_�������_1"] == "01");
    QVERIFY(importer.params["1_������_6_�������_3"] == "25102.94");
    QVERIFY(importer.params["1_������_1_�������_7"] == "2012");

    QVERIFY(importer.params["1_���4.1"] == "108");
    QVERIFY(importer.params["1_�����������4.1"] == "11000.00");

    QVERIFY(importer.params["1_���4.2"] == "103");
    QVERIFY(importer.params["1_�����������4.2"] == "400.00");

    QVERIFY(importer.params["1_���4.3"] == "");
    QVERIFY(importer.params["1_�����������4.3"] == "");

    QVERIFY(importer.params["1_���4.4"] == "");
    QVERIFY(importer.params["1_�����������4.4"] == "");

    QVERIFY(importer.params["1_���������������"] == "11400.00");

    QVERIFY(importer.params["1_������������"] == "258555.52");
    QVERIFY(importer.params["1_����������������������"] == "247155.52");
    QVERIFY(importer.params["1_������5.3"] == "32130");
    QVERIFY(importer.params["1_������5.4"] == "32130");
    QVERIFY(importer.params["1_������5.5"] == "");
    QVERIFY(importer.params["1_������5.6"] == "");
    QVERIFY(importer.params["1_������5.7"] == "");
    QVERIFY(importer.params["1_������5.8"] == "");
    QVERIFY(importer.params["1_������5.9"] == "");
    QVERIFY(importer.params["1_������5.10"] == "");
    QVERIFY(importer.params["1_���������"] == Importer::WINtoUnicode("���������"));
    QVERIFY(importer.params["1_���������"] == Importer::WINtoUnicode("������� �.�."));

}

void Test2ndflprn::testTableEndSymbol()
{
    QFile file("2NDFL_02.LST");

    if (!file.open(QFile::ReadOnly))
        return;
    QTextStream in(&file);
    in.setCodec("IBM 866");

    for (int i = 0; i < 34; i++)
        in.readLine();

    QChar sym(0x2514);
    QString line = in.readLine();

    QVERIFY(line[0] == sym);

//        QFile file1("1251.txt");
//        if (!file1.open(QFile::WriteOnly | QFile::Truncate))
//            return;
//        QTextStream out(&file1);
//        out.setCodec("UTF-8");
//        out << "line0 " << line[0] << " " << QChar(0x2514);

}


void Test2ndflprn::testReplaceExtensions()
{

    QString filename = "2NDFL_01.LST";

    Exporter exporter(NULL);
    filename = exporter.replaceExt(filename);
    QVERIFY(filename == "2NDFL_01.xls");
}

QTEST_MAIN(Test2ndflprn)
#include "main.moc"
