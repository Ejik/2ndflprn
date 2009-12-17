#include <QtCore/QCoreApplication>

#include <QtTest/QtTest>
#include "../importer.h"

class TestImporter : public QObject
{
    Q_OBJECT

private slots:
    void testCreate();
    void testParsing();
};


void TestImporter::testCreate()
{
    Importer importer(QString());
}

void TestImporter::testParsing()
{
    Importer importer("c:\\Projects\\2ndflprn\\2NDFL_01.LST");
    importer.parse();

    QVERIFY(importer.params["Year"] == "2009");
    QVERIFY(importer.params["Number"] == " 1");
    QVERIFY(importer.params["Date"] == "13.12.2009");
    QVERIFY(importer.params["IFNS"] == "5190");
    QVERIFY(importer.params["INN/CPP"] == "  5190309146/519001001");

    qDebug(Importer::WINtoUnicode(importer.params["Orgname"]).toLocal8Bit());
    QVERIFY(importer.params["Orgname"] == Importer::WINtoUnicode("ŒŒŒ '¿—Œ“-÷≈Õ“– C≈–¬»—'                      "));
}

QTEST_MAIN(TestImporter)
#include "main.moc"
