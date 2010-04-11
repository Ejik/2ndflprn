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

            // СПРАВКА О ДОХОДАХ ФИЗИЧЕСКОГО ЛИЦА за 2009 год № 1 от 17.12.2009 в ИФНС №7610
            //QString text = "СПРАВКА О ДОХОДАХ ФИЗИЧЕСКОГО ЛИЦА за " + data->params[QString::number(i) + "_Year"] + " год № " + data->params[QString::number(i) + "_Number"] + " от " + data->params[QString::number(i) + "_Date"] + " в ИФНС №" + data->params[QString::number(i) + "_IFNS"];
            out << data->params[QString::number(i) + "_Year"];

            exportSection("2", &out);

            out << data->params[QString::number(i) + "_Number"];

            exportSection("3", &out);

            out << data->params[QString::number(i) + "_Date"];

            exportSection("4", &out);
            out << data->params[QString::number(i) + "_IFNS"];            

            //        // 1.1. ИНН/КПП для организации или ИНН для физического лица
            //        text = data->params[QString::number(i) + "_INN/CPP"];
            exportSection("5", &out);
            out << data->params[QString::number(i) + "_INN/CPP"];

            //        // 1.2. Наименование организации / Фамилия, имя, отчество физического лица
            //        text = data->params[QString::number(i) + "_Orgname"];
            exportSection("6", &out);
            out << data->params[QString::number(i) + "_Orgname"];

            //        // 1.3. Код ОКАТО
            //        text = data->params[QString::number(i) + "_OKATO"];
            exportSection("7", &out);
            out << data->params[QString::number(i) + "_OKATO"];

            //        // 1.4. Телефон
            //        text = data->params[QString::number(i) + "_Tel"];
            exportSection("8", &out);
            out << data->params[QString::number(i) + "_Tel"];

            //        // ТБН
            //        text = data->params[QString::number(i) + "_TBN"];
            exportSection("9", &out);
            out << data->params[QString::number(i) + "_TBN"];

                      //        // 2. Данные о физическом лице - получателе доходов
            //        // 2.1. ИНН
            //        text = data->params[QString::number(i) + "_INN"];
            exportSection("10", &out);
            out << data->params[QString::number(i) + "_INN"];

            //
            //        // 2.2. Фамилия, имя, отчество
            //        text = data->params[QString::number(i) + "_FIO"];
            exportSection("11", &out);
            out << data->params[QString::number(i) + "_FIO"];

            //        // 2.3. Статус (1-резидент, 2-нерезидент)
            //        text = data->params[QString::number(i) + "_Status"];
            exportSection("12", &out);
            out << data->params[QString::number(i) + "_Status"];

            //        // 2.4. Дата рождения
            //        text = data->params[QString::number(i) + "_Birthday"];
            exportSection("13", &out);
            out << data->params[QString::number(i) + "_Birthday"];

            //        // 2.5. Гражданство (код страны)
            //        text = data->params[QString::number(i) + "_Grajdanstvo"];
            exportSection("14", &out);
            out << data->params[QString::number(i) + "_Grajdanstvo"];

            //        // 2.6. Код документа, удостоверяющего личность
            //        text = data->params[QString::number(i) + "_CodeDoc"];
            exportSection("15", &out);
            out << data->params[QString::number(i) + "_CodeDoc"];

            //        // 2.7. Серия, номер документа
            //        text = data->params[QString::number(i) + "_SeriesAndNumberDoc"];
            exportSection("16", &out);
            out << data->params[QString::number(i) + "_SeriesAndNumberDoc"];

            //        // 2.8. Адрес места жительства в Российской Федерации:
            //        // почтовый индекс
            //        text = data->params[QString::number(i) + "_Index"];
            exportSection("17", &out);
            out << data->params[QString::number(i) + "_Index"];

            //        // код региона
            //        text = data->params[QString::number(i) + "_RegCode"];
            exportSection("18", &out);
            out << data->params[QString::number(i) + "_RegCode"];
            //
            //        // район
            //        text = data->params[QString::number(i) + "_Raion"];
            exportSection("19", &out);
            out << data->params[QString::number(i) + "_Raion"];
            //
            //        // город            
            //        text = data->params[QString::number(i) + "_City"];
            exportSection("20", &out);
            out << data->params[QString::number(i) + "_City"];

            //        //   населенный пункт           
            //        text = data->params[QString::number(i) + "_НасПункт"];
            exportSection("21", &out);
            out << data->params[QString::number(i) + "_НасПункт"];

            //        // улица
            //        text = data->params[QString::number(i) + "_Street"];
            exportSection("22", &out);
            out << data->params[QString::number(i) + "_Street"];

            //        // дом
            //        text = data->params[QString::number(i) + "_Дом"];
            exportSection("23", &out);
            out << data->params[QString::number(i) + "_Дом"];
            //
            //        // корпус
            //        text = data->params[QString::number(i) + "_Корпус"];
            exportSection("24", &out);
            out << data->params[QString::number(i) + "_Корпус"];

            //        // квартира
            //        text = data->params[QString::number(i) + "_Квартира"];
            exportSection("25", &out);
            out << data->params[QString::number(i) + "_Квартира"];

            //        // 2.9. Адрес в стране проживания: Код страны:
            //        text = data->params[QString::number(i) + "_КодСтраныПроживания"];
            exportSection("26", &out);
            out << data->params[QString::number(i) + "_КодСтраныПроживания"];
            //
            //        // Адрес
            //        text = data->params[QString::number(i) + "_АдресВСтранеПроживания"];
            exportSection("27", &out);
            out << data->params[QString::number(i) + "_АдресВСтранеПроживания"];
            //
            //        // 3. Доходы, облагаемые по ставке 13%
            //        text = data->params[QString::number(i) + "_СтавкаНалога"];
            exportSection("28", &out);
            out << data->params[QString::number(i) + "_СтавкаНалога"];

            exportSection("29", &out);

            for (int j = 1; j < 17; j++)
            //for (int j = 1; j < data->params[QString::number(i) + "_incomeTableRowsCount"].toInt(); j++)
            {
               out << "<tr height=16 style='mso-height-source:userset;height:12.0pt'>" <<
                               "<td height=16 class=xl6324539 style='height:12.0pt'></td>" <<
                               "<td colspan=2 class=xl7624539>";

                out << data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_1"];

                out << "</td>" <<
                        "<td colspan=5 class=xl7624539 style='border-left:none'>";

                out << data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_2"];

                out << "</td>" <<
                        "<td colspan=7 class=xl7724539 style='border-left:none'>";
                out << data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_3"];

                out << "</td>" <<
                        "<td colspan=4 class=xl7624539 style='border-left:none'>";

                out << data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_4"];

                out << "</td>" <<
                        "<td colspan=6 class=xl7724539 style='border-left:none'>";

                out << data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_5"];

                out << "</td>" <<
                        "<td class=xl6324539></td>" <<
                        "<td class=xl6324539></td>" <<
                        "<td colspan=2 class=xl7624539>";

                out << data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_6"];

                out << "</td>" <<
                        "<td colspan=4 class=xl7624539 style='border-left:none'>";

                out << data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_7"];

                out << "</td>" <<
                        "<td colspan=5 class=xl7724539 style='border-left:none'>";
                out << data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_8"];

                out << "</td>" <<
                        "<td colspan=4 class=xl7624539 style='border-left:none'>";

                out << data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_9"];

                out << "</td>" <<
                        "<td colspan=2 class=xl7724539 style='border-left:none'>";

                out << data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_10"];

                out << "</td>" <<
                        "</tr>";
            }

            // 4. Стандартные и имущественные налоговые вычеты
            // 4.1. Суммы налоговых вычетов, право на получение которых имеется у налогоплательщика

            exportSection("30", &out);
            out << data->params[QString::number(i) + "_Код4.1"];

            out << "</td>" <<
                    "<td colspan=6 class=xl7724539 style='border-left:none'>";
            out << data->params[QString::number(i) + "_СуммаВычета4.1"];

            out << "</td>" <<
                    "<td class=xl6324539></td>" <<
                    "<td colspan=5 class=xl7624539>";
            out << data->params[QString::number(i) + "_Код4.2"];

            out << "</td>" <<
                    "<td colspan=7 class=xl7724539 style='border-left:none'>";

            out << data->params[QString::number(i) + "_СуммаВычета4.2"];

            out << "</td>" <<
                    "<td class=xl6324539></td>" <<
                    "<td colspan=5 class=xl7624539>";
            out << data->params[QString::number(i) + "_Код4.3"];

            out << "</td>" <<
                    "<td colspan=4 class=xl7724539 style='border-left:none'>";

            out << data->params[QString::number(i) + "_СуммаВычета4.3"];

            out << "</td>" <<
                    "<td class=xl6324539></td>" <<
                    "<td colspan=5 class=xl7624539>";

            out << data->params[QString::number(i) + "_Код4.4"];

            out << "</td>" <<
                    "<td colspan=3 class=xl7724539 style='border-left:none'>";

            out << data->params[QString::number(i) + "_СуммаВычета4.4"];

            exportSection("31", &out);


            // 4.2. № Уведомления, подтверждающего право на имущественный налоговый вычет
            out << data->params[QString::number(i) + "_НомерУведомления"];

            exportSection("32", &out);

            // 4.3. Дата выдачи Уведомления
            out << data->params[QString::number(i) + "_ДатаВыдачиУведомления"];

            //        // 4.4.Код налогового органа, выдавшего Уведомление
            //        text = data->params[QString::number(i) + "_КодИФНСУведомления"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AP49")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //
            //        // 4.5. Общая сумма предоставленных стандартных налоговых вычетов
            //        text = data->params[QString::number(i) + "_СуммаНалВычетов"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AD50")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 4.6. Общая сумма предоставленных имущественных налоговых вычетов
            //        text = data->params[QString::number(i) + "_СуммаИмущественныхНалВычетов "];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AD51")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 5. Общая сумма дохода и налога на доходы по итогам налогового периода
            //        // 5.1. Общая сумма дохода
            //        text = data->params[QString::number(i) + "_СуммаДоходов"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ54")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 5.2. Облагаемая сумма дохода
            //        text = data->params[QString::number(i) + "_ОблагаемаяСуммаДоходов"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ55")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 5.3. Сумма налога исчисленная
            //        text = data->params[QString::number(i) + "_СуммаП5.3"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ56")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 5.4. Сумма налога удержанная
            //        text = data->params[QString::number(i) + "_СуммаП5.4"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ57")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 5.5. Сумма возврата налога по перерасчету с доходов прошлых лет
            //        text = data->params[QString::number(i) + "_СуммаП5.5"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ58")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 5.6. Сумма, зачтенная при уплате налога по перерасчету с доходов прошлых лет
            //        text = data->params[QString::number(i) + "_СуммаП5.6"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ59")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 5.7. Сумма, удержанная при уплате налога по перерасчету с доходов прошлых лет
            //        text = data->params[QString::number(i) + "_СуммаП5.7"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ60")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 5.8. Задолженность по налогу за налогоплательщиком
            //        text = data->params[QString::number(i) + "_СуммаП5.8"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ61")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 5.9. Сумма налога, излишне удержанная налоговым агентом
            //        text = data->params[QString::number(i) + "_СуммаП5.9"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ62")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // 5.10. Сумма налога, переданная на взыскание в налоговый орган
            //        text = data->params[QString::number(i) + "_СуммаП5.10"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ63")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // Налоговый агент
            //        text = data->params[QString::number(i) + "_Должность"];
            //        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("J66")));
            //        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));
            //
            //        // ФИО
            //        text = data->params[QString::number(i) + "_ФИОАгента"];
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
