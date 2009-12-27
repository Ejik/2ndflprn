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

    for (int i = 1; i < data->numberDoc; i++)
    {
        QString filename = QDir::currentPath() + "\\" + data->params[QString::number(i) + "_TBN"] + "_2ndfl.xls";
        QFile::copy(QDir::currentPath() + "\\tpl_2ndfl.xls", filename);
        QAxObject *workbook = workbooks->querySubObject( "Open(const QString&)", filename);
        QAxObject *mSheets = workbook->querySubObject( "Sheets" );
        QAxObject *StatSheet = mSheets->querySubObject( "Item(const QVariant&)", QVariant("2ndfl") );

        mExcel->dynamicCall( "SetVisible(bool)", TRUE ); //������ ��� �������

        // ������� � ������� ����������� ���� �� 2009 ��� � 1 �� 17.12.2009 � ���� �7610
        QString text = "������� � ������� ����������� ���� �� " + data->params[QString::number(i) + "_Year"] + " ��� � " + data->params[QString::number(i) + "_Number"] + " �� " + data->params[QString::number(i) + "_Date"] + " � ���� �" + data->params[QString::number(i) + "_IFNS"];
        QAxObject *range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("B5")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(Importer::WINtoUnicode(text)));


        // 1.1. ���/��� ��� ����������� ��� ��� ��� ����������� ����
        text = data->params[QString::number(i) + "_INN/CPP"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("Y8")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 1.2. ������������ ����������� / �������, ���, �������� ����������� ����
        text = data->params[QString::number(i) + "_Orgname"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("B10")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 1.3. ��� �����
        text = data->params[QString::number(i) + "_OKATO"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("H11")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 1.4. �������
        text = data->params[QString::number(i) + "_Tel"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AG11")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2. ������ � ���������� ���� - ���������� �������
        // 2.1. ���
        text = data->params[QString::number(i) + "_INN"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("F14")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.2. �������, ���, ��������
        text = data->params[QString::number(i) + "_FIO"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AB14")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.3. ������ (1-��������, 2-����������)
        text = data->params[QString::number(i) + "_Status"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("Q15")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.4. ���� ��������
        text = data->params[QString::number(i) + "_Birthday"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AB15")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.5. ����������� (��� ������)
        text = data->params[QString::number(i) + "_Grajdanstvo"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AR15")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.6. ��� ���������, ��������������� ��������
        text = data->params[QString::number(i) + "_CodeDoc"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("T16")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.7. �����, ����� ���������
        text = data->params[QString::number(i) + "_SeriesAndNumberDoc"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ16")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.8. ����� ����� ���������� � ���������� ���������:
        // �������� ������
        text = data->params[QString::number(i) + "_Index"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AF17")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // ��� �������
        text = data->params[QString::number(i) + "_RegCode"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AQ17")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // �����
        text = data->params[QString::number(i) + "_Raion"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("D18")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // �����
        text = data->params[QString::number(i) + "_City"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("V18")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        //   ���������� �����
        //    text = data->params[""];
        //    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ18")));
        //    range->dynamicCall( "SetValue(const QVariant&)", QVariant(Importer::WINtoUnicode(text)));

        // �����
        text = data->params[QString::number(i) + "_Street"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("D19")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // ���
        text = data->params[QString::number(i) + "_���"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AB19")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // ������
        text = data->params[QString::number(i) + "_������"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AI19")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // ��������
        text = data->params[QString::number(i) + "_��������"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AR19")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.9. ����� � ������ ����������: ��� ������:
        //    text = data->params[""];
        //    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AC20")));
        //    range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 3. ������, ���������� �� ������ 13%
        for (int j = 1; j < data->incomeTableRowsCount; j++)
        {
            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_1"];
            range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("B" + QString::number(23 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_2"];
            range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("D" + QString::number(23 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_3"];
            range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("I" + QString::number(23 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_4"];
            range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("P" + QString::number(23 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_5"];
            range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("T" + QString::number(23 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));


            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_6"];
            range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AB" + QString::number(23 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_7"];
            range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AD" + QString::number(23 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_8"];
            range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AH" + QString::number(23 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_9"];
            range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AM" + QString::number(23 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_10"];
            range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AQ" + QString::number(23 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        }

        // 4. ����������� � ������������� ��������� ������
        // 4.1. ����� ��������� �������, ����� �� ��������� ������� ������� � �����������������
        text = data->params[QString::number(i) + "_���4.1"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("B46")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_�����������4.1"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("G46")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_���4.2"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("N46")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_�����������4.2"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("S46")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_���4.3"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AA46")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_�����������4.3"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AF46")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_���4.4"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AK46")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_�����������4.4"];
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
        text = data->params[QString::number(i) + "_���������������"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AD50")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 4.6. ����� ����� ��������������� ������������� ��������� �������
        //    text = data->params[QString::number(i) + "_������������"];
        //    range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AD51")));
        //    range->dynamicCall( "SetValue(const QVariant&)", QVariant(Importer::WINtoUnicode(text)));

        // 5. ����� ����� ������ � ������ �� ������ �� ������ ���������� �������
        // 5.1. ����� ����� ������
        text = data->params[QString::number(i) + "_������������"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ54")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.2. ���������� ����� ������
        text = data->params[QString::number(i) + "_����������������������"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ55")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.3. ����� ������ �����������
        text = data->params[QString::number(i) + "_������5.3"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ56")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.4. ����� ������ ����������
        text = data->params[QString::number(i) + "_������5.4"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ57")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.5. ����� �������� ������ �� ����������� � ������� ������� ���
        text = data->params[QString::number(i) + "_������5.5"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ58")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.6. �����, ��������� ��� ������ ������ �� ����������� � ������� ������� ���
        text = data->params[QString::number(i) + "_������5.6"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ59")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.7. �����, ���������� ��� ������ ������ �� ����������� � ������� ������� ���
        text = data->params[QString::number(i) + "_������5.7"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ60")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.8. ������������� �� ������ �� ������������������
        text = data->params[QString::number(i) + "_������5.8"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ61")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.9. ����� ������, ������� ���������� ��������� �������
        text = data->params[QString::number(i) + "_������5.9"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ62")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.10. ����� ������, ���������� �� ��������� � ��������� �����
        text = data->params[QString::number(i) + "_������5.10"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ63")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // ��������� �����
        text = data->params[QString::number(i) + "_���������"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("J66")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // ���
        text = data->params[QString::number(i) + "_���������"];
        range = StatSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AK66")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        workbook->dynamicCall("Save()");
        workbook->dynamicCall("Close()");
    }
    mExcel->dynamicCall("Quit()");

}
