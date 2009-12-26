#include "exporter.h"
#include <QDir>

Exporter::Exporter(Importer* instance)
{
    data = instance;

}

Exporter::~Exporter()
{
    delete mExcel;
    data = NULL;
}

void Exporter::exportToExcel()
{
    mExcel = new QAxObject( "Excel.Application", this ); //�������� ����������� �� excel

    QAxObject *workbooks = mExcel->querySubObject( "Workbooks" );
    QAxObject *workbook = workbooks->querySubObject( "Open(const QString&)", QDir::currentPath() + "\\tpl_2ndfl.xls" );
    QAxObject *mSheets = workbook->querySubObject( "Sheets" );
    QAxObject *StatSheet = mSheets->querySubObject( "Item(const QVariant&)", QVariant("2ndfl") );

    mExcel->dynamicCall( "SetVisible(bool)", TRUE ); //������ ��� ������

    // ������� � ������� ����������� ���� �� 2009 ��� � 1 �� 17.12.2009 � ���� �7610
    QString text = "������� � ������� ����������� ���� �� " + data->params["1_Year"] + " ��� � " + data->params["1_Number"] + " �� " + data->params["1_Date"] + " � ���� �" + data->params["1_IFNS"];
    QAxObject *range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("B5")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(Importer::WINtoUnicode(text)));


    // 1.1. ���/��� ��� ����������� ��� ��� ��� ����������� ����
    text = data->params["1_INN/CPP"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("Y8")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 1.2. ������������ ����������� / �������, ���, �������� ����������� ����
    text = data->params["1_Orgname"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("B10")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 1.3. ��� �����
    text = data->params["1_OKATO"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("H11")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 1.4. �������
    text = data->params["1_Tel"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AG11")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 2. ������ � ���������� ���� - ���������� �������
    // 2.1. ���
    text = data->params["1_INN"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("F14")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 2.2. �������, ���, ��������
    text = data->params["1_FIO"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AB14")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 2.3. ������ (1-��������, 2-����������)
    text = data->params["1_Status"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("Q15")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 2.4. ���� ��������
    text = data->params["1_Birthday"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AB15")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 2.5. ����������� (��� ������)
    text = data->params["1_Grajdanstvo"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AR15")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 2.6. ��� ���������, ��������������� ��������
    text = data->params["1_CodeDoc"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("T16")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 2.7. �����, ����� ���������
    text = data->params["1_SeriesAndNumberDoc"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ16")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 2.8. ����� ����� ���������� � ���������� ���������:
    // �������� ������
    text = data->params["1_Index"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AF17")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // ��� �������
    text = data->params["1_RegCode"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AQ17")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // �����
    text = data->params["1_Raion"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("D18")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // �����
    text = data->params["1_City"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("V18")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    //   ���������� �����
//    text = data->params[""];
//    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ18")));
//    range->dynamicCall( "SetValue(const QVariant&)", QVariant(Importer::WINtoUnicode(text)));

    // �����
    text = data->params["1_Street"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("D19")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // ���
    text = data->params["1_���"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AB19")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // ������
    text = data->params["1_������"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AI19")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // ��������
    text = data->params["1_��������"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AR19")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 2.9. ����� � ������ ����������: ��� ������:
    text = data->params[""];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AC20")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 3. ������, ���������� �� ������ 13%
    for (int i = 0; i < data->incomeTable; i++)
    {
        text = data->params[""];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AC20")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(Importer::WINtoUnicode(text)));
    }

    // 4. ����������� � ������������� ��������� ������
    // 4.1. ����� ��������� �������, ����� �� ��������� ������� ������� � �����������������
    text = data->params["1_���4.1"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("B46")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    text = data->params["1_�����������4.1"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("G46")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    text = data->params["1_���4.2"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("N46")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    text = data->params["1_�����������4.2"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("S46")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    text = data->params["1_���4.3"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AA46")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    text = data->params["1_�����������4.3"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AF46")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    text = data->params["1_���4.4"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AK46")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    text = data->params["1_�����������4.4"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AP46")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 4.2. � �����������, ��������������� ����� �� ������������� ��������� �����
//    text = data->params[""];
//    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AI48")));
//    range->dynamicCall( "SetValue(const QVariant&)", QVariant(Importer::WINtoUnicode(text)));

    // 4.3. ���� ������ �����������
//    text = data->params[""];
//    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("N49")));
//    range->dynamicCall( "SetValue(const QVariant&)", QVariant(Importer::WINtoUnicode(text)));

    // 4.4.��� ���������� ������, ��������� �����������
//    text = data->params[""];
//    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AP49")));
//    range->dynamicCall( "SetValue(const QVariant&)", QVariant(Importer::WINtoUnicode(text)));


    // 4.5. ����� ����� ��������������� ����������� ��������� �������
    text = data->params["1_���������������"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AD50")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 4.6. ����� ����� ��������������� ������������� ��������� �������
//    text = data->params["1_������������"];
//    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AD51")));
//    range->dynamicCall( "SetValue(const QVariant&)", QVariant(Importer::WINtoUnicode(text)));

    // 5. ����� ����� ������ � ������ �� ������ �� ������ ���������� �������
    // 5.1. ����� ����� ������
    text = data->params["1_������������"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ54")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 5.2. ���������� ����� ������
    text = data->params["1_����������������������"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ55")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 5.3. ����� ������ �����������
    text = data->params["1_������5.3"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ56")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 5.4. ����� ������ ����������
    text = data->params["1_������5.4"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ57")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 5.5. ����� �������� ������ �� ����������� � ������� ������� ���
    text = data->params["1_������5.5"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ58")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 5.6. �����, ��������� ��� ������ ������ �� ����������� � ������� ������� ���
    text = data->params["1_������5.6"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ59")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 5.7. �����, ���������� ��� ������ ������ �� ����������� � ������� ������� ���
    text = data->params["1_������5.7"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ60")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 5.8. ������������� �� ������ �� ������������������
    text = data->params["1_������5.8"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ61")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 5.9. ����� ������, ������� ���������� ��������� �������
    text = data->params["1_������5.9"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ62")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // 5.10. ����� ������, ���������� �� ��������� � ��������� �����
    text = data->params["1_������5.10"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ63")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // ��������� �����
    text = data->params["1_���������"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("J66")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // ���
    text = data->params["1_���������"];
    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AK66")));
    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

    // save doc
    //mExcel

}
