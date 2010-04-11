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
            exportSection("12", &out);
            out << data->params[QString::number(i) + "_Status"];

            //        // 2.4. ���� ��������
            //        text = data->params[QString::number(i) + "_Birthday"];
            exportSection("13", &out);
            out << data->params[QString::number(i) + "_Birthday"];

            //        // 2.5. ����������� (��� ������)
            //        text = data->params[QString::number(i) + "_Grajdanstvo"];
            exportSection("14", &out);
            out << data->params[QString::number(i) + "_Grajdanstvo"];

            //        // 2.6. ��� ���������, ��������������� ��������
            //        text = data->params[QString::number(i) + "_CodeDoc"];
            exportSection("15", &out);
            out << data->params[QString::number(i) + "_CodeDoc"];

            //        // 2.7. �����, ����� ���������
            //        text = data->params[QString::number(i) + "_SeriesAndNumberDoc"];
            exportSection("16", &out);
            out << data->params[QString::number(i) + "_SeriesAndNumberDoc"];

            //        // 2.8. ����� ����� ���������� � ���������� ���������:
            //        // �������� ������
            //        text = data->params[QString::number(i) + "_Index"];
            exportSection("17", &out);
            out << data->params[QString::number(i) + "_Index"];

            //        // ��� �������
            //        text = data->params[QString::number(i) + "_RegCode"];
            exportSection("18", &out);
            out << data->params[QString::number(i) + "_RegCode"];
            //
            //        // �����
            //        text = data->params[QString::number(i) + "_Raion"];
            exportSection("19", &out);
            out << data->params[QString::number(i) + "_Raion"];
            //
            //        // �����            
            //        text = data->params[QString::number(i) + "_City"];
            exportSection("20", &out);
            out << data->params[QString::number(i) + "_City"];

            //        //   ���������� �����           
            //        text = data->params[QString::number(i) + "_��������"];
            exportSection("21", &out);
            out << data->params[QString::number(i) + "_��������"];

            //        // �����
            //        text = data->params[QString::number(i) + "_Street"];
            exportSection("22", &out);
            out << data->params[QString::number(i) + "_Street"];

            //        // ���
            //        text = data->params[QString::number(i) + "_���"];
            exportSection("23", &out);
            out << data->params[QString::number(i) + "_���"];
            //
            //        // ������
            //        text = data->params[QString::number(i) + "_������"];
            exportSection("24", &out);
            out << data->params[QString::number(i) + "_������"];

            //        // ��������
            //        text = data->params[QString::number(i) + "_��������"];
            exportSection("25", &out);
            out << data->params[QString::number(i) + "_��������"];

            //        // 2.9. ����� � ������ ����������: ��� ������:
            //        text = data->params[QString::number(i) + "_�������������������"];
            exportSection("26", &out);
            out << data->params[QString::number(i) + "_�������������������"];
            //
            //        // �����
            //        text = data->params[QString::number(i) + "_����������������������"];
            exportSection("27", &out);
            out << data->params[QString::number(i) + "_����������������������"];
            //
            //        // 3. ������, ���������� �� ������ 13%
            //        text = data->params[QString::number(i) + "_������������"];
            exportSection("28", &out);
            out << data->params[QString::number(i) + "_������������"];

            exportSection("29", &out);

            for (int j = 1; j < 17; j++)
            //for (int j = 1; j < data->params[QString::number(i) + "_incomeTableRowsCount"].toInt(); j++)
            {
               out << "<tr height=16 style='mso-height-source:userset;height:12.0pt'>" <<
                               "<td height=16 class=xl6324539 style='height:12.0pt'></td>" <<
                               "<td colspan=2 class=xl7624539>";

                out << data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_1"];

                out << "</td>" <<
                        "<td colspan=5 class=xl7624539 style='border-left:none'>";

                out << data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_2"];

                out << "</td>" <<
                        "<td colspan=7 class=xl7724539 style='border-left:none'>";
                out << data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_3"];

                out << "</td>" <<
                        "<td colspan=4 class=xl7624539 style='border-left:none'>";

                out << data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_4"];

                out << "</td>" <<
                        "<td colspan=6 class=xl7724539 style='border-left:none'>";

                out << data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_5"];

                out << "</td>" <<
                        "<td class=xl6324539></td>" <<
                        "<td class=xl6324539></td>" <<
                        "<td colspan=2 class=xl7624539>";

                out << data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_6"];

                out << "</td>" <<
                        "<td colspan=4 class=xl7624539 style='border-left:none'>";

                out << data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_7"];

                out << "</td>" <<
                        "<td colspan=5 class=xl7724539 style='border-left:none'>";
                out << data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_8"];

                out << "</td>" <<
                        "<td colspan=4 class=xl7624539 style='border-left:none'>";

                out << data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_9"];

                out << "</td>" <<
                        "<td colspan=2 class=xl7724539 style='border-left:none'>";

                out << data->params[QString::number(i) + "_������_" + QString::number(j) + "_�������_10"];

                out << "</td>" <<
                        "</tr>";
            }

            // 4. ����������� � ������������� ��������� ������
            // 4.1. ����� ��������� �������, ����� �� ��������� ������� ������� � �����������������

            exportSection("30", &out);
            out << data->params[QString::number(i) + "_���4.1"];

            out << "</td>" <<
                    "<td colspan=6 class=xl7724539 style='border-left:none'>";
            out << data->params[QString::number(i) + "_�����������4.1"];

            out << "</td>" <<
                    "<td class=xl6324539></td>" <<
                    "<td colspan=5 class=xl7624539>";
            out << data->params[QString::number(i) + "_���4.2"];

            out << "</td>" <<
                    "<td colspan=7 class=xl7724539 style='border-left:none'>";

            out << data->params[QString::number(i) + "_�����������4.2"];

            out << "</td>" <<
                    "<td class=xl6324539></td>" <<
                    "<td colspan=5 class=xl7624539>";
            out << data->params[QString::number(i) + "_���4.3"];

            out << "</td>" <<
                    "<td colspan=4 class=xl7724539 style='border-left:none'>";

            out << data->params[QString::number(i) + "_�����������4.3"];

            out << "</td>" <<
                    "<td class=xl6324539></td>" <<
                    "<td colspan=5 class=xl7624539>";

            out << data->params[QString::number(i) + "_���4.4"];

            out << "</td>" <<
                    "<td colspan=3 class=xl7724539 style='border-left:none'>";

            out << data->params[QString::number(i) + "_�����������4.4"];

            exportSection("31", &out);


            // 4.2. � �����������, ��������������� ����� �� ������������� ��������� �����
            out << data->params[QString::number(i) + "_����������������"];

            exportSection("32", &out);

            // 4.3. ���� ������ �����������
            out << data->params[QString::number(i) + "_���������������������"];

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
