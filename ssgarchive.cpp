#include "ssgarchive.h"
#include "ui_ssgarchive.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDateTimeEdit>
#include <QIcon>

//       QMessageBox msgBox;
//       msgBox.setText("In default of switch " + QString::number(index));
//       msgBox.exec();

// Global used for current path to file locations
QString filePath;

// Global to use for holding version number for program: putting  here so easy to change
QString aifVersion = "AIF-200127";

SSGArchive::SSGArchive(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SSGArchive)
{
    // Initialize

    QStringList contentList;

    ui->setupUi(this);

    this->setWindowTitle("SSG Archive Information Form");

    QIcon ssgIcon;
    ssgIcon.addFile("/usr/share/icons/hicolor/512x512/apps/ssg.png");
    this->setWindowIcon(ssgIcon);

    ui->submissionDate->setDate(QDate::currentDate());

    // Set up Resource Type List
    ui->resourceType->addItem("Text");
    ui->resourceType->addItem("Sound");
    ui->resourceType->addItem("Video");

    // Set up Domain List
    contentList.clear();
    contentList << "--select--" <<
                   "Literacy" <<
                   "Translation" <<
                   "Linguistics" <<
                   "Anthropology" <<
                   "Lit & Anthro" <<
                   "Lit & Ling" <<
                   "Lit & Tran";

    ui->domain->addItems(contentList);

    // Don't initialize completion date so user has to think about it
    QDate dt1(QDate::currentDate().year(), 1, 1);
    ui->completionDate->setDate(dt1);

    // Set up Edition List
    contentList.clear();
    contentList << "--select--" <<
                   "Unpublished" <<
                   "No Edition Specified" <<
                   "Trial Edition" <<
                   "Second Trial Edition" <<
                   "Third Trial Edition" <<
                   "Fourth Trial Edition" <<
                   "Fifth Trial Edition" <<
                   "Sixth Trial Edition" <<
                   "Seventh Trial Edition" <<
                   "Eighth Trial Edition" <<
                   "Ninth Trial Edition" <<
                   "Tenth Trial Edition" <<
                   "11th Trial Edition" <<
                   "First Edition" <<
                   "Second Edition" <<
                   "Third Edition" <<
                   "Fourth Edition" <<
                   "Fifth Edition" <<
                   "Sixth Edition" <<
                   "Seventh Edition" <<
                   "Eighth Edition" <<
                   "Ninth Edition" <<
                   "Tenth Edition" <<
                   "11th Edition";

    ui->edition->addItems(contentList);

    // Set up Source State List
    contentList.clear();
    contentList << "--select--" <<
                   "No Source" <<
                   "Incomplete" <<
                   "Rough Draft" <<
                   "Team Revised" <<
                   "Community Checked" <<
                   "Consultant Checked" <<
                   "Content Missing" <<
                   "Formatting and Picture Problems" <<
                   "Formatting Problems" <<
                   "Picture Problems" <<
                   "Complete";

    ui->sourceState->addItems(contentList);

    // Set up PDF State List
    contentList.clear();
    contentList << "--select--" <<
                   "Text Incomplete" <<
                   "Text Complete" <<
                   "Scanned, not Print Ready" <<
                   "Scanned, Print Ready" <<
                   "Print Ready";

    ui->pdfState->addItems(contentList);

    // Set up Publication Place List
    contentList.clear();
    contentList << "--select--" <<
                   "Arua" <<
                   "Entebbe" <<
                   "Khartoum" <<
                   "Juba" <<
                   "Kitale" <<
                   "Nairobi" <<
                   "Maridi" <<
                   "Wau" <<
                   "Yei" <<
                   "homeland village" <<
                   "Other";

    ui->publicationPlace->addItems(contentList);

    // Set up Writing Language List
    contentList.clear();
    contentList << "--select--" <<
                   "English" <<
                   "Various" <<
                   "Other" <<
                   "Acheron" <<
                   "Acholi" <<
                   "Ama" <<
                   "Anuak" <<
                   "Arabic (Juba)" <<
                   "Arabic (Omdurman)" <<
                   "Arabic (Standard)" <<
                   "Aringa" <<
                   "Avokaya" <<
                   "Baka" <<
                   "Banda-Ndele" <<
                   "Bari" <<
                   "Belanda Bor" <<
                   "Belanda Viri" <<
                   "Beli" <<
                   "Bongo" <<
                   "Burun" <<
                   "Dagik" <<
                   "Daju (Dar Fur)" <<
                   "Didinga" <<
                   "Dilling" <<
                   "Dinka Agar" <<
                   "Dinka Bor" <<
                   "Dinka Cam" <<
                   "Dinka Padang" <<
                   "Dinka Rek" <<
                   "Gaam" <<
                   "Gbaya" <<
                   "Hadra" <<
                   "Heiban" <<
                   "Jumjum" <<
                   "Jur Modo" <<
                   "Kadugli" <<
                   "Kamda" <<
                   "Kanga" <<
                   "Karko" <<
                   "Katcha" <<
                   "Katla" <<
                   "Keiga" <<
                   "Keliko" <<
                   "Koalib" <<
                   "Krongo" <<
                   "Kufa" <<
                   "Kuku" <<
                   "Lango" <<
                   "Laro" <<
                   "Logorik" <<
                   "Lopit" <<
                   "Lumun" <<
                   "Luwo" <<
                   "Mabaan" <<
                   "Mandari" <<
                   "Ma'di" <<
                   "Miri" <<
                   "Mitto" <<
                   "Moro" <<
                   "Morokodo" <<
                   "Moru" <<
                   "Mundu" <<
                   "Murle" <<
                   "Narim" <<
                   "Ndogo" <<
                   "Nuer" <<
                   "Otoro" <<
                   "Otuho" <<
                   "Pari" <<
                   "Reel" <<
                   "Shatt" <<
                   "Shilluk" <<
                   "Shwai" <<
                   "Tennet" <<
                   "Tese" <<
                   "Tira" <<
                   "Tocho" <<
                   "Toposa" <<
                   "Uduk" <<
                   "Wa'di" <<
                   "Wira" <<
                   "Zande";

    ui->writingLanguage->addItems(contentList);

    // Set up Vernacular Language List
    contentList.clear();
    contentList << "--select--" <<
                   "Various" <<
                   "None" <<
                   "Other" <<
                   "Acheron" <<
                   "Acholi" <<
                   "Ama" <<
                   "Anuak" <<
                   "Arabic (Juba)" <<
                   "Arabic (Omdurman)" <<
                   "Arabic (Standard)" <<
                   "Aringa" <<
                   "Avokaya" <<
                   "Baka" <<
                   "Banda-Ndele" <<
                   "Bari" <<
                   "Belanda Bor" <<
                   "Belanda Viri" <<
                   "Beli" <<
                   "Bongo" <<
                   "Burun" <<
                   "Dagik" <<
                   "Daju (Dar Fur)" <<
                   "Didinga" <<
                   "Dilling" <<
                   "Dinka Agar" <<
                   "Dinka Bor" <<
                   "Dinka Cam" <<
                   "Dinka Padang" <<
                   "Dinka Rek" <<
                   "Gaam" <<
                   "Gbaya" <<
                   "Hadra" <<
                   "Heiban" <<
                   "Jumjum" <<
                   "Jur Modo" <<
                   "Kadugli" <<
                   "Kamda" <<
                   "Kanga" <<
                   "Karko" <<
                   "Katcha" <<
                   "Katla" <<
                   "Keiga" <<
                   "Keliko" <<
                   "Koalib" <<
                   "Krongo" <<
                   "Kufa" <<
                   "Kuku" <<
                   "Lango" <<
                   "Laro" <<
                   "Logorik" <<
                   "Lopit" <<
                   "Lumun" <<
                   "Luwo" <<
                   "Mabaan" <<
                   "Mandari" <<
                   "Ma'di" <<
                   "Miri" <<
                   "Mitto" <<
                   "Moro" <<
                   "Morokodo" <<
                   "Moru" <<
                   "Mundu" <<
                   "Murle" <<
                   "Narim" <<
                   "Ndogo" <<
                   "Nuer" <<
                   "Otoro" <<
                   "Otuho" <<
                   "Pari" <<
                   "Reel" <<
                   "Shatt" <<
                   "Shilluk" <<
                   "Shwai" <<
                   "Tennet" <<
                   "Tese" <<
                   "Tira" <<
                   "Tocho" <<
                   "Toposa" <<
                   "Uduk" <<
                   "Wa'di" <<
                   "Wira" <<
                   "Zande";

    ui->vernacularLanguage->addItems(contentList);

    // Set up Content Classification List
    on_domain_activated(0);

    // Set up Teachers Guide List
    contentList.clear();
    contentList << "no" <<
                   "is" <<
                   "has";

    ui->teachersGuide->addItems(contentList);

}

SSGArchive::~SSGArchive()
{
    delete ui;
}

void SSGArchive::on_saveButton_clicked()
{
    // QString output = ui->nameField->text() + "," + ui->resourceField->itemData(ui->resourceField->currentIndex());
    QString output = QLatin1Char('"') +
            aifVersion + QString("\",\"") +
            prepStringForCSV(ui->submittersName->text(),false) + QString("\",\"") +
            ui->submissionDate->text() + QString("\",\"") +
            ui->resourceType->currentText() + QString("\",\"") +
            ui->domain->currentText() + QString("\",\"") +
            prepStringForCSV(ui->vernacularTitle->text(),false) + QString("\",\"") +
            prepStringForCSV(ui->englishTitle->text(),false) + QString("\",\"") +
            prepStringForCSV(ui->authors->text(),false) + QString("\",\"") +
            ui->completionDate->text() + QString("\",\"") +
            ui->edition->currentText() + QString("\",\"") +
            ui->sourceState->currentText() + QString("\",\"") +
            ui->publicationPlace->currentText() + QString("\",\"") +
            ui->writingLanguage->currentText() + QString("\",\"") +
            ui->vernacularLanguage->currentText() + QString("\",\"") +
            ui->contentClassification->currentText() + QString("\",\"") +
            ui->teachersGuide->currentText() + QString("\",\"") +
            prepStringForCSV(ui->topic->text(),1) + QString("\",\"") +
            ui->publisher->text() + QString("\",\"") +
            prepStringForCSV(ui->primaryComments->toPlainText(),false) + QString("\",\"") +
            prepStringForCSV(ui->outdates->text(),1) + QString("\",\"") +
            ui->pdfState->currentText() + QString("\",\"") +
            prepStringForCSV(ui->secondaryComments->toPlainText(),true) + QString("\",\"") +
            ui->pages->text() +
            QString("\"\r\n");

    // default filePath to user's home directory
    if ( filePath.isEmpty() ) {
        filePath = QDir::homePath();
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Save File",QDir::toNativeSeparators(filePath + "/AIF-" + ui->englishTitle->text() + ".csv"),
                                                    "All Files (*.*);;CSV Files (*.csv);;Text Files (*.txt *.dat)");

    filePath =  QFileInfo(fileName).path(); // store path for next time

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            // error message
        } else {
            QTextStream stream(&file);
            stream.setCodec("UTF-16");
            stream << output;
            stream.flush();
            file.close();
        }
    }
}

void SSGArchive::on_openButton_clicked()
{
    // default filePath to user's home directory
    if ( filePath.isNull() ) {
        filePath = QDir::homePath();
    }

    QString fileName = QFileDialog::getOpenFileName(this, "Open Existing AIF", filePath,"CSV Files (*.csv)");

    filePath =  QFileInfo(fileName).path(); // store path for next time

    if (!fileName.isEmpty()) {
        QFile file(fileName);

        if (file.open(QIODevice::ReadOnly)) {

            // QTextStream can have unicode codec defined, so handles unicode better than just assigning file to a string.
            QTextStream stream(&file);
            stream.setCodec("UTF-16");
            QString data = stream.readAll().trimmed();
            file.close();

            QString temp;
            int index;

            // Trim leading "
            int currentStart = 1;

            // First field is Version number: won't "read" so just throw away
            int currentEnd = data.indexOf("\",\"", currentStart);

            // Load Submitters Name
            currentStart = currentEnd + 3;
            currentEnd = data.indexOf("\",\"", currentStart);
            ui->submittersName->setText(getCSVString(data, currentStart, currentEnd));

            // Load Submission Date
            currentStart = currentEnd + 3;
            currentEnd = data.indexOf("\",\"", currentStart);
            temp = getCSVString(data, currentStart, currentEnd);
            QDate dt1(temp.mid(0,4).toInt(), temp.mid(5,2).toInt(), temp.mid(8,2).toInt());
            ui->submissionDate->setDate(dt1);

            // Load Resource Type
            currentStart = currentEnd + 3;
            currentEnd = data.indexOf("\",\"", currentStart);
            temp = getCSVString(data, currentStart, currentEnd);
            index = ui->resourceType->findText(temp);
            ui->resourceType->setCurrentIndex(index);

            // Load Domain
            currentStart = currentEnd + 3;
            currentEnd = data.indexOf("\",\"", currentStart);
            temp = getCSVString(data, currentStart, currentEnd);
            index = ui->domain->findText(temp);
            ui->domain->setCurrentIndex(index);
            // set classification list so will work when imported
            on_domain_activated(index);

            // Load Vernacular Title
            currentStart = currentEnd + 3;
            currentEnd = data.indexOf("\",\"", currentStart);
            ui->vernacularTitle->setText(getCSVString(data, currentStart, currentEnd));

            //Load English Title
            currentStart = currentEnd + 3;
            currentEnd = data.indexOf("\",\"", currentStart);
            ui->englishTitle->setText(getCSVString(data, currentStart, currentEnd));

            // Load Authors
            currentStart = currentEnd + 3;
            currentEnd = data.indexOf("\",\"", currentStart);
            ui->authors->setText(getCSVString(data, currentStart, currentEnd));

            // Load Completion Date
            currentStart = currentEnd + 3;
            currentEnd = data.indexOf("\",\"", currentStart);
            temp = getCSVString(data, currentStart, currentEnd);
            QDate dt2(temp.mid(0,4).toInt(), temp.mid(5,2).toInt(), temp.mid(8,2).toInt());
            ui->completionDate->setDate(dt1);

            // Load Edition
            currentStart = currentEnd + 3;
            currentEnd = data.indexOf("\",\"", currentStart);
            temp = getCSVString(data, currentStart, currentEnd);
            index = ui->edition->findText(temp);
            ui->edition->setCurrentIndex(index);

            // Load Source State
            currentStart = currentEnd + 3;
            currentEnd = data.indexOf("\",\"", currentStart);
            temp = getCSVString(data, currentStart, currentEnd);
            index = ui->sourceState->findText(temp);
            ui->sourceState->setCurrentIndex(index);

            // Load Publication Date
            currentStart = currentEnd + 3;
            currentEnd = data.indexOf("\",\"", currentStart);
            temp = getCSVString(data, currentStart, currentEnd);
            index = ui->publicationPlace->findText(temp);
            ui->publicationPlace->setCurrentIndex(index);

            // Load Writing Language
            currentStart = currentEnd + 3;
            currentEnd = data.indexOf("\",\"", currentStart);
            temp = getCSVString(data, currentStart, currentEnd);
            index = ui->writingLanguage->findText(temp);
            ui->writingLanguage->setCurrentIndex(index);

            // Load Vernacular Title
            currentStart = currentEnd + 3;
            currentEnd = data.indexOf("\",\"", currentStart);
            temp = getCSVString(data, currentStart, currentEnd);
            index = ui->vernacularLanguage->findText(temp);
            ui->vernacularLanguage->setCurrentIndex(index);

            // Load Content Classification
            currentStart = currentEnd + 3;
            currentEnd = data.indexOf("\",\"", currentStart);
            temp = getCSVString(data, currentStart, currentEnd);
            index = ui->contentClassification->findText(temp);
            ui->contentClassification->setCurrentIndex(index);

            // Load Teachers Guide
            currentStart = currentEnd + 3;
            currentEnd = data.indexOf("\",\"", currentStart);
            temp = getCSVString(data, currentStart, currentEnd);
            index = ui->teachersGuide->findText(temp);
            ui->teachersGuide->setCurrentIndex(index);

            // Load Topic
            currentStart = currentEnd + 3;
            currentEnd = data.indexOf("\",\"", currentStart);
            ui->topic->setText(getCSVString(data, currentStart, currentEnd));

            // Load Publisher
            currentStart = currentEnd + 3;
            currentEnd = data.indexOf("\",\"", currentStart);
            ui->publisher->setText(getCSVString(data, currentStart, currentEnd));

            // Load Primary Contents
            currentStart = currentEnd + 3;
            currentEnd = data.indexOf("\",\"", currentStart);
            ui->primaryComments->setText(getCSVString(data, currentStart, currentEnd));

            // Load Outdates
            currentStart = currentEnd + 3;
            currentEnd = data.indexOf("\",\"", currentStart);
            ui->outdates->setText(getCSVString(data, currentStart, currentEnd));

            // Load PDF State
            currentStart = currentEnd + 3;
            currentEnd = data.indexOf("\",\"", currentStart);
            temp = getCSVString(data, currentStart, currentEnd);
            index = ui->pdfState->findText(temp);
            ui->pdfState->setCurrentIndex(index);

            // Load Secondary Comments
            currentStart = currentEnd + 3;
            currentEnd = data.indexOf("\",\"", currentStart);
            ui->secondaryComments->setText(getCSVString(data, currentStart, currentEnd));

            // Load Pages
            currentStart = currentEnd + 3;
            // Trim trailing "
            currentEnd = data.length() - 1;
            temp = getCSVString(data, currentStart, currentEnd);
            ui->pages->setValue(temp.toInt());
        }
    }
}

QString SSGArchive::getCSVString(QString data, int currentStart, int currentEnd)
{
    QString temp;
    temp = data.mid(currentStart, currentEnd - currentStart);
    temp.replace("\"\"","\"");

    return temp;
}

QString SSGArchive::prepStringForCSV(QString input, bool allowReturns)
{
    QString temp;
    QString temp2;
    QString output;

    // Replace single " with double ""
    temp = input.replace("\"","\"\"");

    if (allowReturns)
    {
        // Ensure "Windows Style Returns
        // Replace \n with \r\n (for Windows)
        temp2 = temp.replace("\n","\r\n");
        output = temp2.replace("\r\r","\r");
    }
    else
    {
        // Wipe out \n and \r Returns
        // Replace \n with a space
        temp2 = temp.replace("\n"," ");
        // Delete \r
        output = temp2.replace("\r","");
    }

    // Trim it
    return output.trimmed();
}


void SSGArchive::on_domain_activated(int domainIndex)
{
    QStringList contentList;

    // first item in list should be the select
    contentList.append("--select--");

    switch (domainIndex)
    {
    case 1:
        // Literacy
        contentList << "Alphabet Chart" <<
                       "Alphabet Book" <<
                       "Alphabet Story Book" <<
                       "Pre-Primer" <<
                       "Primer" <<
                       "Transition Primer" <<
                       "Sentence Book" <<
                       "Easy Reader" <<
                       "Post-Primer" <<
                       "Numeracy" <<
                       "Bulletin" <<
                       "Calendar" <<
                       "Health Book" <<
                       "Health Card" <<
                       "Songbook" <<
                       "P1" <<
                       "P2" <<
                       "P3" <<
                       "P4" <<
                       "P5" <<
                       "P6" <<
                       "P7" <<
                       "P8";
        break;
    case 2:
        // Translation
        contentList << "Genesis" <<
                       "Exodus" <<
                       "Leviticus" <<
                       "Numbers" <<
                       "Deuteronomy" <<
                       "Joshua" <<
                       "Judges" <<
                       "Ruth" <<
                       "1 Samuel" <<
                       "2 Samuel" <<
                       "1 Kings" <<
                       "2 Kings" <<
                       "1 Chronicles" <<
                       "2 Chronicles" <<
                       "Ezra" <<
                       "Nehemiah" <<
                       "Esther" <<
                       "Job" <<
                       "Psalms" <<
                       "Proverbs" <<
                       "Ecclesiastes" <<
                       "Song of Songs" <<
                       "Isaiah" <<
                       "Jeremiah" <<
                       "Lamentations" <<
                       "Ezekiel" <<
                       "Daniel" <<
                       "Hosea" <<
                       "Joel" <<
                       "Amos" <<
                       "Obadiah" <<
                       "Jonah" <<
                       "Micah" <<
                       "Nahum" <<
                       "Habakkuk" <<
                       "Zephaniah" <<
                       "Haggai" <<
                       "Zechariah" <<
                       "Malachi" <<
                       "Matthew" <<
                       "Mark" <<
                       "Luke" <<
                       "John" <<
                       "Acts" <<
                       "Romans" <<
                       "1 Corinthians" <<
                       "2 Corinthians" <<
                       "Galatians" <<
                       "Ephesians" <<
                       "Philippians" <<
                       "Colossians" <<
                       "1 Thessalonians" <<
                       "2 Thessalonians" <<
                       "1 Timothy" <<
                       "2 Timothy" <<
                       "Titus" <<
                       "Philemon" <<
                       "Hebrews" <<
                       "James" <<
                       "1 Peter" <<
                       "2 Peter" <<
                       "1 John" <<
                       "2 John" <<
                       "3 John" <<
                       "Jude" <<
                       "Revelation" <<
                       "5 Ts" <<
                       "Peter's Letters" <<
                       "Luke & Acts" <<
                       "NT" <<
                       "OT" <<
                       "Bible" <<
                       "Assorted Scripture";
        break;
    case 3:
        // Lingustics
        contentList << "Survey Report" <<
                       "Orthography Statement" <<
                       "Word List" <<
                       "Dictionary" <<
                       "Grammar Write-Up" <<
                       "Transcribed Text" <<
                       "Language Learning";
        break;
    case 4:  // CURRENTLY NOT DEFINED
        // Anthropology
        //        break;
    case 5:
        // Lit & Anthro
        contentList << "Folktales";
        break;

    case 6:
        // Lit & Ling
        contentList << "Grammar Book" <<
                       "Writing Principles";
        break;

    case 7:
        // Lit & Tran
        contentList << "Bible Story" <<
                       "Liturgy" <<
                       "Scripture Use" <<
                       "Catechism";
        break;


    }

    // append at the bottom for all choices
    contentList.append("Wkshop or Train Mat");
    contentList.append("Miscellaneous");

    ui->contentClassification->clear();
    ui->contentClassification->addItems(contentList);

}
