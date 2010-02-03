#include "exporter.h"
#include <QDir>
#include<QDebug>

Exporter::Exporter(Importer* instance)
{
    data = instance;

}

Exporter::~Exporter()
{
    delete mExcel;
    data = NULL;
}

QString Exporter::replaceExt(const QString name)
{
    QString filename = name;
    filename = filename.remove(filename.length() - 3, 3);
    return  filename + "xls";
}

QVariant Exporter::getSheetName(int docNum, QAxObject *sheets)
{
    if (docNum > 1)
    {
      QAxObject* sheet = sheets->querySubObject("Item(const QVariant&)", QVariant(docNum - 1));
      sheetsNames.append( sheet->property("Name").toString());
    }

    QString name = data->params[QString::number(docNum) + "_TBN"];
    QString newName = name;
    int i = 2;
    while (sheetsNames.contains(newName))
        newName = name + "(" + QString::number(i++) + ")";

    return newName;
}

void Exporter::exportToExcel()
{    
    QString filename = QDir::toNativeSeparators(replaceExt(data->inputFile));

    QFile::remove(filename);
    QFile::copy(QDir::toNativeSeparators(QDir::currentPath() + "\\tpl_2ndfl.xls"), filename);

    mExcel = new QAxObject( "Excel.Application", this ); //�������� ����������� �� excel      
    QAxObject *workbooks = mExcel->querySubObject( "Workbooks" );
    QAxObject *workbook = workbooks->querySubObject( "Open(const QString&)", filename);
    QAxObject *mSheets = workbook->querySubObject( "Sheets" );
    QAxObject *tplSheet = mSheets->querySubObject( "Item(const QVariant&)", QVariant("2ndfl") );
    mExcel->setProperty("DisplayAlerts", "0");

    for (int i = 1; i < data->numberDoc; i++)
    {        
        tplSheet->dynamicCall("Copy(IDispatch *)", tplSheet->asVariant());
        
        QAxObject *currentSheet = mSheets->querySubObject( "Item(const QVariant&)", QVariant(i) );
        currentSheet->setProperty("Name", getSheetName(i, mSheets));
        mExcel->dynamicCall( "SetVisible(bool)", TRUE ); //������ ��� �������

        // ������� � ������� ����������� ���� �� 2009 ��� � 1 �� 17.12.2009 � ���� �7610
        QString text = "������� � ������� ����������� ���� �� " + data->params[QString::number(i) + "_Year"] + " ��� � " + data->params[QString::number(i) + "_Number"] + " �� " + data->params[QString::number(i) + "_Date"] + " � ���� �" + data->params[QString::number(i) + "_IFNS"];
        QAxObject *range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("B5")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(Importer::WINtoUnicode(text)));


        // 1.1. ���/��� ��� ����������� ��� ��� ��� ����������� ����
        text = data->params[QString::number(i) + "_INN/CPP"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("Y8")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 1.2. ������������ ����������� / �������, ���, �������� ����������� ����
        text = data->params[QString::number(i) + "_Orgname"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("B10")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 1.3. ��� �����
        text = data->params[QString::number(i) + "_OKATO"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("H11")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 1.4. �������
        text = data->params[QString::number(i) + "_Tel"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AG11")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2. ������ � ���������� ���� - ���������� �������
        // 2.1. ���
        text = data->params[QString::number(i) + "_INN"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("F14")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // ���
        text = data->params[QString::number(i) + "_TBN"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AR13")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.2. �������, ���, ��������
        text = data->params[QString::number(i) + "_FIO"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AB14")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.3. ������ (1-��������, 2-����������)
        text = data->params[QString::number(i) + "_Status"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("Q15")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.4. ���� ��������
        text = data->params[QString::number(i) + "_Birthday"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AB15")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.5. ����������� (��� ������)
        text = data->params[QString::number(i) + "_Grajdanstvo"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AR15")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.6. ��� ���������, ��������������� ��������
        text = data->params[QString::number(i) + "_CodeDoc"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("T16")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.7. �����, ����� ���������
        text = data->params[QString::number(i) + "_SeriesAndNumberDoc"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ16")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.8. ����� ����� ���������� � ���������� ���������:
        // �������� ������
        text = data->params[QString::number(i) + "_Index"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AF17")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // ��� �������
        text = data->params[QString::number(i) + "_RegCode"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AQ17")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // �����
        text = data->params[QString::number(i) + "_Raion"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("D18")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // �����
//        text = data->WINtoUnicode("�����");
//        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("S18")));
//        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_City"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("V18")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        //   ���������� �����
//        text = data->WINtoUnicode("���������� �����");
//        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("S18")));
//        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_��������"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("I19")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // �����
        text = data->params[QString::number(i) + "_Street"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("D20")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // ���
        text = data->params[QString::number(i) + "_���"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AB20")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // ������
        text = data->params[QString::number(i) + "_������"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AI20")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // ��������
        text = data->params[QString::number(i) + "_��������"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AR20")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.9. ����� � ������ ����������: ��� ������:
        text = data->params[QString::number(i) + "_�������������������"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("S21")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // �����
        text = data->params[QString::number(i) + "_����������������������"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("B22")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 3. ������, ���������� �� ������ 13%
        text = data->params[QString::number(i) + "_������������"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("Q24")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        for (int j = 1; j < data->params[QString::number(i) + "_incomeTableRowsCount"].toInt(); j++)
        {
            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_1"];
            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("B" + QString::number(25 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_2"];
            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("D" + QString::number(25 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_3"];
            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("I" + QString::number(25 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_4"];
            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("P" + QString::number(25 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_5"];
            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("T" + QString::number(25 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));


            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_6"];
            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AB" + QString::number(25 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_7"];
            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AD" + QString::number(25 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_8"];
            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AH" + QString::number(25 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_9"];
            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AM" + QString::number(25 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_10"];
            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AQ" + QString::number(25 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        }

        // 4. ����������� � ������������� ��������� ������
        // 4.1. ����� ��������� �������, ����� �� ��������� ������� ������� � �����������������
        text = data->params[QString::number(i) + "_���4.1"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("B46")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_�����������4.1"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("G46")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_���4.2"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("N46")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_�����������4.2"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("S46")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_���4.3"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AA46")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_�����������4.3"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AF46")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_���4.4"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AK46")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_�����������4.4"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AP46")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 4.2. � �����������, ��������������� ����� �� ������������� ��������� �����
        text = data->params[QString::number(i) + "_����������������"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AI48")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 4.3. ���� ������ �����������
        text = data->params[QString::number(i) + "_���������������������"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("N49")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 4.4.��� ���������� ������, ��������� �����������
        text = data->params[QString::number(i) + "_������������������"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AP49")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));


        // 4.5. ����� ����� ��������������� ����������� ��������� �������
        text = data->params[QString::number(i) + "_���������������"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AD50")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 4.6. ����� ����� ��������������� ������������� ��������� �������
        text = data->params[QString::number(i) + "_���������������������������� "];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AD51")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5. ����� ����� ������ � ������ �� ������ �� ������ ���������� �������
        // 5.1. ����� ����� ������
        text = data->params[QString::number(i) + "_������������"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ54")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.2. ���������� ����� ������
        text = data->params[QString::number(i) + "_����������������������"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ55")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.3. ����� ������ �����������
        text = data->params[QString::number(i) + "_������5.3"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ56")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.4. ����� ������ ����������
        text = data->params[QString::number(i) + "_������5.4"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ57")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.5. ����� �������� ������ �� ����������� � ������� ������� ���
        text = data->params[QString::number(i) + "_������5.5"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ58")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.6. �����, ��������� ��� ������ ������ �� ����������� � ������� ������� ���
        text = data->params[QString::number(i) + "_������5.6"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ59")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.7. �����, ���������� ��� ������ ������ �� ����������� � ������� ������� ���
        text = data->params[QString::number(i) + "_������5.7"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ60")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.8. ������������� �� ������ �� ������������������
        text = data->params[QString::number(i) + "_������5.8"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ61")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.9. ����� ������, ������� ���������� ��������� �������
        text = data->params[QString::number(i) + "_������5.9"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ62")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.10. ����� ������, ���������� �� ��������� � ��������� �����
        text = data->params[QString::number(i) + "_������5.10"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ63")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // ��������� �����
        text = data->params[QString::number(i) + "_���������"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("J66")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // ���
        text = data->params[QString::number(i) + "_���������"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AK66")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        workbook->dynamicCall("Save()");

    }

    tplSheet->dynamicCall("Delete()");
    workbook->dynamicCall("Save()");

}
