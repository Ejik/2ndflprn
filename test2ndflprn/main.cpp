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
    QVERIFY(importer.params["INN/CPP"].trimmed() == "5190309146/519001001");
    QVERIFY(importer.params["Orgname"].trimmed() == Importer::WINtoUnicode("ООО 'АСОТ-ЦЕНТР CЕРВИС'"));
    QVERIFY(importer.params["OKATO"].trimmed() == "47401367000");
    QVERIFY(importer.params["Tel"].trimmed() == "45-04-27");
    QVERIFY(importer.params["INN"].trimmed() == "519041604350");
    QVERIFY(importer.params["FIO"].trimmed() == Importer::WINtoUnicode("Беляева Наталья Сергеевна"));
    QVERIFY(importer.params["TBN"].trimmed() == "0102");
    QVERIFY(importer.params["Status"].trimmed() == "1");
    QVERIFY(importer.params["Birthday"].trimmed() == Importer::WINtoUnicode("03.10.1980 г."));
    QVERIFY(importer.params["Grajdanstvo"].trimmed() == "643");    
    QVERIFY(importer.params["CodeDoc"].trimmed() == "21");
    QVERIFY(importer.params["SeriesAndNumberDoc"].trimmed() == "47 04  915496");
    QVERIFY(importer.params["Index"].trimmed() == "183053");
    QVERIFY(importer.params["RegCode"].trimmed() == "51");
    QVERIFY(importer.params["Raion"].trimmed() == "");
    QVERIFY(importer.params["City"].trimmed() == Importer::WINtoUnicode("Мурманск г"));
    QVERIFY(importer.params["Street"].trimmed() == Importer::WINtoUnicode("Шабалина ул"));
    QVERIFY(importer.params["Дом"].trimmed() == "47");
    QVERIFY(importer.params["Корпус"].trimmed() == "");
    QVERIFY(importer.params["Квартира"].trimmed() == "27");

}

QTEST_MAIN(TestImporter)
#include "main.moc"
