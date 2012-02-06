#include <QDebug>
#include "exporter.h"
#include <QDir>
#include <qt_windows.h>
#include "common.h"

Exporter::Exporter(Processor* instance)
{
    processor_ = instance;

}

Exporter::~Exporter()
{
    processor_ = NULL;
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

void Exporter::export_to_html()
{    
    QString filename = QDir::toNativeSeparators(replaceExt(processor_->input_file()));

    //QFile::remove(filename);
    outputFile.setFileName(filename);
    if (outputFile.open(QFile::WriteOnly | QFile::Truncate)) {

        QTextStream out(&outputFile);
        out.setCodec("windows-1251");

        PrintHeader(&out);

        for (int i = 0; i < processor_->spraw_count(); i++) {

            SprawModel current_spraw = processor_->spraw(i);
            QStringList sprawlines = PrintSpraw(current_spraw);

            // удалим последнюю строку, иначе на печать попадает лишний чистый лист
            sprawlines.removeLast();
            QStringListIterator it(sprawlines);
            while (it.hasNext()) {

                out << it.next();

            }

        }


        out << "</body></html>";

//        exportSection("0", &out);

//        for (int i = 1; i < data->numberDoc; i++)
//        {
//            exportSection("1", &out);

//            // признак
//            out << data->params[QString::number(i) + "_Priznak"];

//            // в ИФНС(код)
//            exportSection("1.1", &out);

//            out << data->params[QString::number(i) + "_IFNS"];
//            exportSection("1.2", &out);

//            // СПРАВКА О ДОХОДАХ ФИЗИЧЕСКОГО ЛИЦА за 2009 год № 1 от 17.12.2009 в ИФНС №7610
//            //QString text = "СПРАВКА О ДОХОДАХ ФИЗИЧЕСКОГО ЛИЦА за " + data->params[QString::number(i) + "_Year"] + " год № " + data->params[QString::number(i) + "_Number"] + " от " + data->params[QString::number(i) + "_Date"] + " в ИФНС №" + data->params[QString::number(i) + "_IFNS"];
//            out << data->params[QString::number(i) + "_Year"];

//            exportSection("2", &out);

//            out << data->params[QString::number(i) + "_Number"];

//            exportSection("3", &out);

//            out << data->params[QString::number(i) + "_Date"];

//            exportSection("4", &out);

//            //        // 1.1. ИНН/КПП для организации или ИНН для физического лица
//            //        text = data->params[QString::number(i) + "_INN/CPP"];
//            exportSection("5", &out);
//            out << data->params[QString::number(i) + "_INN/CPP"];

//            //        // 1.2. Наименование организации / Фамилия, имя, отчество физического лица
//            //        text = data->params[QString::number(i) + "_Orgname"];
//            exportSection("6", &out);
//            out << data->params[QString::number(i) + "_Orgname"];

//            //        // 1.3. Код ОКАТО
//            //        text = data->params[QString::number(i) + "_OKATO"];
//            exportSection("7", &out);
//            out << data->params[QString::number(i) + "_OKATO"];

//            //        // 1.4. Телефон
//            //        text = data->params[QString::number(i) + "_Tel"];
//            exportSection("8", &out);
//            out << data->params[QString::number(i) + "_Tel"];

//            //        // ТБН
//            //        text = data->params[QString::number(i) + "_TBN"];
//            exportSection("9", &out);
//            out << data->params[QString::number(i) + "_TBN"];

//                      //        // 2. Данные о физическом лице - получателе доходов
//            //        // 2.1. ИНН
//            //        text = data->params[QString::number(i) + "_INN"];
//            exportSection("10", &out);
//            out << data->params[QString::number(i) + "_INN"];

//            //
//            //        // 2.2. Фамилия, имя, отчество
//            //        text = data->params[QString::number(i) + "_FIO"];
//            exportSection("11", &out);
//            out << data->params[QString::number(i) + "_FIO"];

//            // 2.3. Статус налогоплательщика
//            exportSection("12", &out);
//            out << data->params[QString::number(i) + "_Status"];

//            // 2.4. Дата рождения
//            exportSection("13", &out);
//            out << data->params[QString::number(i) + "_Birthday"];

//            // 2.5. Гражданство (код страны)
//            exportSection("14", &out);
//            out << data->params[QString::number(i) + "_Grajdanstvo"];

//            // 2.6. Код документа, удостоверяющего личность
//            exportSection("15", &out);
//            out << data->params[QString::number(i) + "_CodeDoc"];

//            // 2.7. Серия, номер документа
//            exportSection("16", &out);
//            out << data->params[QString::number(i) + "_SeriesAndNumberDoc"];

//            // 2.8. Адрес места жительства в Российской Федерации:
//            // почтовый индекс
//            exportSection("17", &out);
//            out << data->params[QString::number(i) + "_Index"];

//            // код региона
//            exportSection("18", &out);
//            out << data->params[QString::number(i) + "_RegCode"];

//            // район
//            exportSection("19", &out);
//            out << data->params[QString::number(i) + "_Raion"];

//            // город
//            exportSection("20", &out);
//            out << data->params[QString::number(i) + "_City"];

//            //   населенный пункт
//            exportSection("21", &out);
//            out << data->params[QString::number(i) + "_НасПункт"];

//            // улица
//            //        text = data->params[QString::number(i) + "_Street"];
//            exportSection("22", &out);
//            out << data->params[QString::number(i) + "_Street"];

//            // дом
//            exportSection("23", &out);
//            out << data->params[QString::number(i) + "_Дом"];

//            // корпус
//            exportSection("24", &out);
//            out << data->params[QString::number(i) + "_Корпус"];

//            // квартира
//            exportSection("25", &out);
//            out << data->params[QString::number(i) + "_Квартира"];

//            // 2.9. Адрес в стране проживания: Код страны:
//            exportSection("26", &out);
//            out << data->params[QString::number(i) + "_КодСтраныПроживания"];

//            // Адрес
//            exportSection("27", &out);
//            out << data->params[QString::number(i) + "_АдресВСтранеПроживания"];

//            // 3. Доходы, облагаемые по ставке 13%
//            //        text = data->params[QString::number(i) + "_СтавкаНалога"];
//            exportSection("28", &out);
//            out << data->params[QString::number(i) + "_СтавкаНалога"];

//            exportSection("29", &out);

//            //for (int j = 1; j < 21; j++)
//            for (int j = 1; j < data->params[QString::number(i) + "_incomeTableRowsCount"].toInt(); j++)
//            {
//               out << "<tr height=16 style='mso-height-source:userset;height:12.0pt'>" <<
//                               "<td height=16 class=xl6324539 style='height:12.0pt'></td>" <<
//                               "<td colspan=2 class=xl7624539>";

//                out << data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_1"];

//                out << "</td>" <<
//                        "<td colspan=5 class=xl7624539 style='border-left:none'>";

//                out << data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_2"];

//                out << "</td>" <<
//                        "<td colspan=7 class=xl7724539 style='border-left:none'>";
//                out << data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_3"];

//                out << "</td>" <<
//                        "<td colspan=4 class=xl7624539 style='border-left:none'>";

//                out << data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_4"];

//                out << "</td>" <<
//                        "<td colspan=6 class=xl7724539 style='border-left:none'>";

//                out << data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_5"];

//                out << "</td>" <<
//                        "<td class=xl6324539></td>" <<
//                        "<td class=xl6324539></td>" <<
//                        "<td colspan=2 class=xl7624539>";

//                out << data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_6"];

//                out << "</td>" <<
//                        "<td colspan=4 class=xl7624539 style='border-left:none'>";

//                out << data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_7"];

//                out << "</td>" <<
//                        "<td colspan=5 class=xl7724539 style='border-left:none'>";
//                out << data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_8"];

//                out << "</td>" <<
//                        "<td colspan=4 class=xl7624539 style='border-left:none'>";

//                out << data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_9"];

//                out << "</td>" <<
//                        "<td colspan=2 class=xl7724539 style='border-left:none'>";

//                out << data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_10"];

//                out << "</td>" <<
//                        "</tr>";
//            }

//            // 4. Стандартные, социальные и имущественные налоговые вычеты
//            // 4.1. Суммы налоговых вычетов, право на получение которых имеется у налогоплательщика

//            exportSection("30", &out);
//            out << data->params[QString::number(i) + "_Код4.1"];

//            out << "</td>" <<
//                    "<td colspan=6 class=xl7724539 style='border-left:none'>";
//            out << data->params[QString::number(i) + "_СуммаВычета4.1"];

//            out << "</td>" <<
//                    "<td class=xl6324539></td>" <<
//                    "<td colspan=5 class=xl7624539>";
//            out << data->params[QString::number(i) + "_Код4.2"];

//            out << "</td>" <<
//                    "<td colspan=7 class=xl7724539 style='border-left:none'>";

//            out << data->params[QString::number(i) + "_СуммаВычета4.2"];

//            out << "</td>" <<
//                    "<td class=xl6324539></td>" <<
//                    "<td colspan=5 class=xl7624539>";
//            out << data->params[QString::number(i) + "_Код4.3"];

//            out << "</td>" <<
//                    "<td colspan=4 class=xl7724539 style='border-left:none'>";

//            out << data->params[QString::number(i) + "_СуммаВычета4.3"];

//            out << "</td>" <<
//                    "<td class=xl6324539></td>" <<
//                    "<td colspan=5 class=xl7624539>";

//            out << data->params[QString::number(i) + "_Код4.4"];

//            out << "</td>" <<
//                    "<td colspan=3 class=xl7724539 style='border-left:none'>";

//            out << data->params[QString::number(i) + "_СуммаВычета4.4"];

//            // 4.2. № Уведомления, подтверждающего право на имущественный налоговый вычет
//            exportSection("31", &out);
//            out << data->params[QString::number(i) + "_НомерУведомления"];

//            // 4.3. Дата выдачи Уведомления
//            exportSection("32", &out);
//            out << data->params[QString::number(i) + "_ДатаВыдачиУведомления"];

//            // 4.4.Код налогового органа, выдавшего Уведомление
//            exportSection("33", &out);
//            out << data->params[QString::number(i) + "_КодИФНСУведомления"];

//            // 5. Общая сумма дохода и налога на доходы по итогам налогового периода
//            // 5.1. Общая сумма дохода
//            exportSection("36", &out);
//            out << data->params[QString::number(i) + "_ТекстП5.1"];
//            out << "</td><td colspan=9 class=xl7624539 style='border-left:none'>";
//            out << data->params[QString::number(i) + "_СуммаДоходов"];

//            // 5.2. Облагаемая сумма дохода
//            exportSection("37", &out);
//            out << data->params[QString::number(i) + "_ТекстП5.2"];
//            out << "<td colspan=9 class=xl7624539 style='border-left:none'>";
//            out << data->params[QString::number(i) + "_ОблагаемаяСуммаДоходов"];

//            // 5.3. Сумма налога исчисленная
//            exportSection("37", &out);
//            out << data->params[QString::number(i) + "_ТекстП5.3"];
//            out << "<td colspan=9 class=xl7624539 style='border-left:none'>";
//            out << data->params[QString::number(i) + "_СуммаП5.3"];

//            // 5.4. Сумма налога удержанная
//            exportSection("37", &out);
//            out << data->params[QString::number(i) + "_ТекстП5.4"];
//            out << "<td colspan=9 class=xl7624539 style='border-left:none'>";
//            out << data->params[QString::number(i) + "_СуммаП5.4"];

//            // 5.5. Сумма налога перечисленная*
//            exportSection("37", &out);
//            out << data->params[QString::number(i) + "_ТекстП5.5"];
//            out << "<td colspan=9 class=xl7624539 style='border-left:none'>";
//            out << data->params[QString::number(i) + "_СуммаП5.5"];

//            // 5.6. Сумма налога, излишне удержанная налоговым агентом
//            exportSection("37", &out);
//            out << data->params[QString::number(i) + "_ТекстП5.6"];
//            out << "<td colspan=9 class=xl7624539 style='border-left:none'>";
//            out << data->params[QString::number(i) + "_СуммаП5.6"];

//            // 5.7. Сумма налога, не удержанная налоговым агентом
//            exportSection("37", &out);
//            out << data->params[QString::number(i) + "_ТекстП5.7"];
//            out << "<td colspan=9 class=xl7624539 style='border-left:none'>";
//            out << data->params[QString::number(i) + "_СуммаП5.7"];
//            out << "</td></tr>";

//            // Налоговый агент
//            exportSection("38", &out);
//            out << data->params[QString::number(i) + "_Должность"];

//            // ФИО
//            exportSection("39", &out);
//            out << data->params[QString::number(i) + "_ФИОАгента"];

//            exportSection("40", &out);

//            if (i != data->numberDoc - 1) {
//                out << "<hr class=""pb""><br>";
//            }

//        }

//        out << "</body></html>";

        quintptr returnValue = (quintptr)ShellExecute(0, 0, (wchar_t*)filename.utf16(), 0, 0, SW_SHOWNORMAL);

        qDebug() << filename;
    }
}

QStringList Exporter::PrintSpraw(SprawModel spraw ) {

    const QString k_tablename1 = UTFtoUnicode("{{ТАБЛИЦА1}}");
    const QString k_tablename2 = UTFtoUnicode("{{ТАБЛИЦА2}}");
    const QString k_para4_name = UTFtoUnicode("{{ПУНКТ4.1}}");
    const QString k_para5_name1 = UTFtoUnicode("{{ПУНКТЫ5СТРАНИЦА1}}");
    const QString k_para5_name2 = UTFtoUnicode("{{ПУНКТЫ5СТРАНИЦА2}}");
    const QString k_stavka1 = UTFtoUnicode("{{СТАВКА1}}");
    const QString k_stavka2 = UTFtoUnicode("{{СТАВКА2}}");
    const QString k_para5_text1 = UTFtoUnicode("{{ПУНКТ5СТРАНИЦА1}}");
    const QString k_para5_text2 = UTFtoUnicode("{{ПУНКТ5СТРАНИЦА2}}");



    QStringList page1_result;
    QStringList page2_result;

    QFile sec(k_body);
    sec.open(QIODevice::ReadOnly);

    QTextStream reader(&sec);

    QString current_line;
    while (!reader.atEnd()) {

        current_line = reader.readLine();
        page1_result << current_line;

        if (spraw.PageCount() == 2) {

            if (current_line.contains(k_tablename1))
                current_line = current_line.replace(k_tablename1, k_tablename2);
            else if (current_line.contains(k_para5_name1))
                current_line = current_line.replace(k_para5_name1, k_para5_name2);
            else if (current_line.contains(k_stavka1))
                current_line = current_line.replace(k_stavka1, k_stavka2);
            else if (current_line.contains(k_para5_text1))
                current_line = current_line.replace(k_para5_text1, k_para5_text2);

            page2_result << current_line;
        }
    }

    page1_result << "<hr class=""pb""><br>";

    if (spraw.PageCount() == 2) {

        page2_result << "<hr class=""pb""><br>";
        page1_result << page2_result;

    }

    spraw.SetParam(k_tablename1, GetHTMLTable1(spraw.tbl(1)));
    spraw.SetParam(k_tablename2, GetHTMLTable1(spraw.tbl(2)));
    spraw.SetParam(k_para4_name, GetHTMLPara4(spraw.para4()));
    spraw.SetParam(k_para5_name1, GetHTMLPara5(spraw.para5(1)));
    spraw.SetParam(k_para5_name2, GetHTMLPara5(spraw.para5(2)));

    QList<QString> keys = spraw.GetParamKeys();
    QListIterator<QString> it(keys);

    QString key;
    QString param_value;

    while(it.hasNext()) {

        key = it.next();
        param_value = spraw.GetParam(key);

        qDebug() << "key " << key << " value " << param_value;

        QMutableStringListIterator iter(page1_result);
        QString current_line;

        while (iter.hasNext()) {

            current_line = iter.next();
            if (current_line.contains(key)) {

                iter.setValue(current_line.replace(key, param_value));

            }
        }
    }


    return page1_result;
}

int Exporter::PrintHeader(QTextStream *out) {

    QFile sec(k_head);
    sec.open(QIODevice::ReadOnly);

    QTextStream reader(&sec);

    while (!reader.atEnd()) {

        out->operator << (reader.readLine());

    }
   sec.close();

   return 0;
}

QString Exporter::GetHTMLTable1(QList<QStringList> tbl1) {

    QString html_table1;

    QListIterator<QStringList> tbl_iterator1(tbl1);
    while (tbl_iterator1.hasNext()) {

        QStringList values = tbl_iterator1.next();

        html_table1 += "<tr height=16 style='mso-height-source:userset;height:12.0pt'>";
        html_table1 += "<td height=16 class=xl6324539 style='height:12.0pt'></td>";
        html_table1 += "<td colspan=2 class=xl7624539>";

        html_table1 += values[1].trimmed();

        html_table1 += "</td>";
        html_table1 += "<td colspan=5 class=xl7624539 style='border-left:none'>";

        html_table1 += values[2].trimmed();

        html_table1 += "</td>";
        html_table1 += "<td colspan=7 class=xl7724539 style='border-left:none'>";

        html_table1 += values[3].trimmed();

        html_table1 += "</td>";
        html_table1 += "<td colspan=4 class=xl7624539 style='border-left:none'>";

        html_table1 += values[4].trimmed();

        html_table1 += "</td>";
        html_table1 += "<td colspan=6 class=xl7724539 style='border-left:none'>";

        html_table1 += values[5].trimmed();

        html_table1 += "</td>";
        html_table1 += "<td class=xl6324539></td>";
        html_table1 += "<td class=xl6324539></td>";
        html_table1 += "<td colspan=2 class=xl7624539>";

        html_table1 += values[7].trimmed();

        html_table1 += "</td>";
        html_table1 += "<td colspan=4 class=xl7624539 style='border-left:none'>";

        html_table1 += values[8].trimmed();

        html_table1 += "</td>";
        html_table1 += "<td colspan=5 class=xl7724539 style='border-left:none'>";

        html_table1 += values[9].trimmed();

        html_table1 += "</td>";
        html_table1 += "<td colspan=4 class=xl7624539 style='border-left:none'>";

        html_table1 += values[10].trimmed();

        html_table1 += "</td>";
        html_table1 += "<td colspan=2 class=xl7724539 style='border-left:none'>";

        html_table1 += values[11].trimmed();

        html_table1 += "</td></tr>";

    }

    return html_table1;
}

QString Exporter::GetHTMLPara4(QStringList data) {

    QString result;

    result = data[1].trimmed() + "</td>";

    result += "<td colspan=6 class=xl7724539 style='border-left:none'>";
    result += data[2].trimmed() + "</td>";

    result += "<td class=xl6324539></td>";
    result += "<td colspan=5 class=xl7624539>";

    result += data[3].trimmed() + "</td>";

    result += "<td colspan=7 class=xl7724539 style='border-left:none'>";

    result += data[4].trimmed() + "</td>";

    result += "<td class=xl6324539></td>";
    result += "<td colspan=5 class=xl7624539>";

    result += data[5].trimmed() + "</td>";

    result += "<td colspan=4 class=xl7724539 style='border-left:none'>";

    result += data[6].trimmed() + "</td>";

    result += "<td class=xl6324539></td>";
    result += "<td colspan=5 class=xl7624539>";

    result += data[7].trimmed() + "</td>";

    result += "<td colspan=3 class=xl7724539 style='border-left:none'>";

    result += data[8].trimmed() + "</td>";

    return result;
}

QString Exporter::GetHTMLPara5(QList<QStringList> data) {

    QString html_table;

    QListIterator<QStringList> i(data);
    while (i.hasNext()) {

        QStringList list = i.next();

        html_table += list[1].trimmed();
        html_table += "</td><td colspan=9 class=xl7624539 style='border-left:none'>";
        html_table += list[2].trimmed();

        if (i.hasNext()) {
            html_table += "</td></tr>";
            html_table += "<tr height=16 style='mso-height-source:userset;height:12.0pt'>";
            html_table += "<td height=16 class=xl6324539 style='height:12.0pt'></td>";
            html_table += "<td colspan=34 class=xl7924539>";
        }
    }

    //html_table = html_table.isEmpty() ? "" : "</td></tr>";

    return html_table;
}
