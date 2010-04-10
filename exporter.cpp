#include "exporter.h"
#include <QDir>
#include <QDebug>

Exporter::Exporter(Importer* instance)
{
    data = instance;

}

Exporter::~Exporter()
{
    data = NULL;
}

QString Exporter::replaceExt(const QString name)
{
    QString filename = name;
    filename = filename.remove(filename.length() - 3, 3);
    return  filename + "html";
}


void Exporter::exportSection(const QString secNum, QTextStream* out)
{
    QFile sec(":/sections/res/sec" + secNum +".txt");
    sec.open(QIODevice::ReadOnly);

    QTextStream reader(&sec);

    while (!reader.atEnd()) {
      out->operator <<(reader.readLine());
    }
   sec.close();

}

void Exporter::exportToHtml()
{    
    QString filename = QDir::toNativeSeparators(replaceExt(data->inputFile));

    //QFile::remove(filename);
    outputFile.setFileName(filename);
    if (outputFile.open(QFile::WriteOnly | QFile::Truncate)) {

        QTextStream out(&outputFile);
        for (int i = 1; i < data->numberDoc; i++)
        {
            exportSection("1", &out);

            // ������� � ������� ����������� ���� �� 2009 ��� � 1 �� 17.12.2009 � ���� �7610
            //QString text = "������� � ������� ����������� ���� �� " + data->params[QString::number(i) + "_Year"] + " ��� � " + data->params[QString::number(i) + "_Number"] + " �� " + data->params[QString::number(i) + "_Date"] + " � ���� �" + data->params[QString::number(i) + "_IFNS"];
            out << data->params[QString::number(i) + "_Year"];

            exportSection("2", &out);

            out << data->params[QString::number(i) + "_Number"];

            exportSection("3", &out);

            out << data->params[QString::number(i) + "_Date"];

            exportSection("4", &out);
            out << data->params[QString::number(i) + "_IFNS"];            

            //        // 1.1. ���/��� ��� ����������� ��� ��� ��� ����������� ����
            //        text = data->params[QString::number(i) + "_INN/CPP"];
            exportSection("5", &out);
            out << data->params[QString::number(i) + "_INN/CPP"];

            //        // 1.2. ������������ ����������� / �������, ���, �������� ����������� ����
            //        text = data->params[QString::number(i) + "_Orgname"];
            exportSection("6", &out);
            out << data->params[QString::number(i) + "_Orgname"];

            //        // 1.3. ��� �����
            //        text = data->params[QString::number(i) + "_OKATO"];
            exportSection("7", &out);
            out << data->params[QString::number(i) + "_OKATO"];

            //        // 1.4. �������
            //        text = data->params[QString::number(i) + "_Tel"];
            exportSection("8", &out);
            out << data->params[QString::number(i) + "_Tel"];

            //        // ���
            //        text = data->params[QString::number(i) + "_TBN"];
            exportSection("9", &out);
            out << data->params[QString::number(i) + "_TBN"];

                      //        // 2. ������ � ���������� ���� - ���������� �������
            //        // 2.1. ���
            //        text = data->params[QString::number(i) + "_INN"];
            exportSection("10", &out);
            out << data->params[QString::number(i) + "_INN"];

            //
            //        // 2.2. �������, ���, ��������
            //        text = data->params[QString::number(i) + "_FIO"];
            exportSection("11", &out);
            out << data->params[QString::number(i) + "_FIO"];

            //        // 2.3. ������ (1-��������, 2-����������)
            //        text = data->params[QString::number(i) + "_Status"];
            exportSection("11", &out);
            out << data->params[QString::number(i) + "_Status"];

            //        // 2.4. ���� ��������
            //        text = data->params[QString::number(i) + "_Birthday"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AB15")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 2.5. ����������� (��� ������)
            //        text = data->params[QString::number(i) + "_Grajdanstvo"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AR15")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 2.6. ��� ���������, ��������������� ��������
            //        text = data->params[QString::number(i) + "_CodeDoc"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("T16")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 2.7. �����, ����� ���������
            //        text = data->params[QString::number(i) + "_SeriesAndNumberDoc"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ16")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 2.8. ����� ����� ���������� � ���������� ���������:
            //        // �������� ������
            //        text = data->params[QString::number(i) + "_Index"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AF17")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // ��� �������
            //        text = data->params[QString::number(i) + "_RegCode"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AQ17")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // �����
            //        text = data->params[QString::number(i) + "_Raion"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("D18")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // �����
            ////        text = data->WINtoUnicode("�����");
            ////        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("S18")));
            ////        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        text = data->params[QString::number(i) + "_City"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("V18")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        //   ���������� �����
            ////        text = data->WINtoUnicode("���������� �����");
            ////        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("S18")));
            ////        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        text = data->params[QString::number(i) + "_��������"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("I19")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // �����
            //        text = data->params[QString::number(i) + "_Street"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("D20")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // ���
            //        text = data->params[QString::number(i) + "_���"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AB20")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // ������
            //        text = data->params[QString::number(i) + "_������"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AI20")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // ��������
            //        text = data->params[QString::number(i) + "_��������"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AR20")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 2.9. ����� � ������ ����������: ��� ������:
            //        text = data->params[QString::number(i) + "_�������������������"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("S21")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // �����
            //        text = data->params[QString::number(i) + "_����������������������"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("B22")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 3. ������, ���������� �� ������ 13%
            //        text = data->params[QString::number(i) + "_������������"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("Q24")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        for (int j = 1; j < data->params[QString::number(i) + "_incomeTableRowsCount"].toInt(); j++)
            //        {
            //            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_1"];
            //            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("B" + QString::number(25 + j, 10))));
            //            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_2"];
            //            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("D" + QString::number(25 + j, 10))));
            //            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_3"];
            //            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("I" + QString::number(25 + j, 10))));
            //            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_4"];
            //            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("P" + QString::number(25 + j, 10))));
            //            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_5"];
            //            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("T" + QString::number(25 + j, 10))));
            //            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //
            //            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_6"];
            //            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AB" + QString::number(25 + j, 10))));
            //            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_7"];
            //            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AD" + QString::number(25 + j, 10))));
            //            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_8"];
            //            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AH" + QString::number(25 + j, 10))));
            //            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_9"];
            //            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AM" + QString::number(25 + j, 10))));
            //            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //            text = data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_10"];
            //            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AQ" + QString::number(25 + j, 10))));
            //            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        }
            //
            //        // 4. ����������� � ������������� ��������� ������
            //        // 4.1. ����� ��������� �������, ����� �� ��������� ������� ������� � �����������������
            //        text = data->params[QString::number(i) + "_���4.1"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("B46")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        text = data->params[QString::number(i) + "_�����������4.1"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("G46")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        text = data->params[QString::number(i) + "_���4.2"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("N46")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        text = data->params[QString::number(i) + "_�����������4.2"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("S46")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        text = data->params[QString::number(i) + "_���4.3"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AA46")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        text = data->params[QString::number(i) + "_�����������4.3"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AF46")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        text = data->params[QString::number(i) + "_���4.4"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AK46")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        text = data->params[QString::number(i) + "_�����������4.4"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AP46")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 4.2. � �����������, ��������������� ����� �� ������������� ��������� �����
            //        text = data->params[QString::number(i) + "_����������������"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AI48")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 4.3. ���� ������ �����������
            //        text = data->params[QString::number(i) + "_���������������������"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("N49")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 4.4.��� ���������� ������, ��������� �����������
            //        text = data->params[QString::number(i) + "_������������������"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AP49")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //
            //        // 4.5. ����� ����� ��������������� ����������� ��������� �������
            //        text = data->params[QString::number(i) + "_���������������"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AD50")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 4.6. ����� ����� ��������������� ������������� ��������� �������
            //        text = data->params[QString::number(i) + "_���������������������������� "];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AD51")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 5. ����� ����� ������ � ������ �� ������ �� ������ ���������� �������
            //        // 5.1. ����� ����� ������
            //        text = data->params[QString::number(i) + "_������������"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ54")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 5.2. ���������� ����� ������
            //        text = data->params[QString::number(i) + "_����������������������"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ55")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 5.3. ����� ������ �����������
            //        text = data->params[QString::number(i) + "_������5.3"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ56")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 5.4. ����� ������ ����������
            //        text = data->params[QString::number(i) + "_������5.4"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ57")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 5.5. ����� �������� ������ �� ����������� � ������� ������� ���
            //        text = data->params[QString::number(i) + "_������5.5"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ58")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 5.6. �����, ��������� ��� ������ ������ �� ����������� � ������� ������� ���
            //        text = data->params[QString::number(i) + "_������5.6"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ59")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 5.7. �����, ���������� ��� ������ ������ �� ����������� � ������� ������� ���
            //        text = data->params[QString::number(i) + "_������5.7"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ60")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 5.8. ������������� �� ������ �� ������������������
            //        text = data->params[QString::number(i) + "_������5.8"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ61")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 5.9. ����� ������, ������� ���������� ��������� �������
            //        text = data->params[QString::number(i) + "_������5.9"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ62")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 5.10. ����� ������, ���������� �� ��������� � ��������� �����
            //        text = data->params[QString::number(i) + "_������5.10"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ63")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // ��������� �����
            //        text = data->params[QString::number(i) + "_���������"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("J66")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // ���
            //        text = data->params[QString::number(i) + "_���������"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AK66")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        workbook->dynamicCall("Save()");
            //
        }

        //tplSheet->dynamicCall("Delete()");
        //workbook->dynamicCall("Save()");
    }
}
