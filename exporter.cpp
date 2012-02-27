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

            if (i == processor_->spraw_count() - 1) {
                // удалим последнюю строку, иначе на печать попадает лишний чистый лист
                sprawlines.removeLast();
            }

            QStringListIterator it(sprawlines);
            while (it.hasNext()) {

                out << it.next();

            }

        }

        out << "</body></html>";

        quintptr returnValue = (quintptr)ShellExecute(0, 0, (wchar_t*)filename.utf16(), 0, 0, SW_SHOWNORMAL);
        qDebug() << "returnValue = " << returnValue;
    }
}

QStringList Exporter::PrintSpraw(SprawModel spraw ) {

    const QString k_para4_name = UTFtoUnicode("{{ПУНКТ4.1}}");
    const QString k_tablename1 = UTFtoUnicode("{{ТАБЛИЦА1}}");
    const QString k_para5_name1 = UTFtoUnicode("{{ПУНКТЫ5СТРАНИЦА1}}");
    const QString k_stavka1 = UTFtoUnicode("{{СТАВКА1}}");
    const QString k_para5_text1 = UTFtoUnicode("{{ПУНКТ5СТРАНИЦА1}}");
    const QString kPageNum = UTFtoUnicode("{{НОМЕРСТРАНИЦЫ1}}");

    QStringList page1_result;

    QFile sec(kBody);
    QFile sec_page2(kBodyPage2);

    sec.open(QIODevice::ReadOnly);
    sec_page2.open(QIODevice::ReadOnly);

    QTextStream reader(&sec);

    QString current_line;
    while (!reader.atEnd()) {

        current_line = reader.readLine();
        page1_result << current_line;

    }

    page1_result << "<hr class=""pb""><br>";
    reader.setDevice(&sec_page2);

    for (int i = 0; i < spraw.PagesCount() - 1; i++) {

        int page_index = i + 2;
        reader.seek(0);

        while (!reader.atEnd()) {

            current_line = reader.readLine();

            if (current_line.contains(kPageNum)) {

                QString value = kPageNum;
                value = value.replace(QString("1"), QString::number(page_index));
                current_line = current_line.replace(kPageNum, value);

            }
            else if (current_line.contains(k_tablename1)) {

                QString value = k_tablename1;
                value = value.replace(QString("1"), QString::number(page_index));
                current_line = current_line.replace(k_tablename1, value);
            }
            else if (current_line.contains(k_para5_name1)) {

                QString value = k_para5_name1;
                value = value.replace(QString("1"), QString::number(page_index));
                current_line = current_line.replace(k_para5_name1, value);
            }
            else if (current_line.contains(k_stavka1)) {

                QString value = k_stavka1;
                value = value.replace(QString("1"), QString::number(page_index));
                current_line = current_line.replace(k_stavka1, value);
            }
            else if (current_line.contains(k_para5_text1)) {

                QString value = k_para5_text1;
                value = value.replace(QString("1"), QString::number(page_index));
                current_line = current_line.replace(k_para5_text1, value);
            }

            page1_result << current_line;

        }


        page1_result << "<hr class=""pb""><br>";

    }

    spraw.SetParam(k_tablename1, GetHTMLTable1(spraw.tbl(1)));
    spraw.SetParam(k_para4_name, GetHTMLPara4(spraw.para4()));
    spraw.SetParam(k_para5_name1, GetHTMLPara5(spraw.para5(1)));

    for (int i = 0; i < spraw.PagesCount() - 1; i++ ) {

        int page_index = i + 2;
        QString value = k_tablename1;
        value = value.replace(QString("1"), QString::number(page_index));
        spraw.SetParam(value, GetHTMLTable1(spraw.tbl(page_index)));

        value = k_para5_name1;
        value = value.replace(QString("1"), QString::number(page_index));
        spraw.SetParam(value, GetHTMLPara5(spraw.para5(page_index)));

    }

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

    QFile sec(kHead);
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
