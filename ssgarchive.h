#ifndef SSGARCHIVE_H
#define SSGARCHIVE_H

#include <QMainWindow>

namespace Ui {
class SSGArchive;
}

class SSGArchive : public QMainWindow
{
    Q_OBJECT

public:
    explicit SSGArchive(QWidget *parent = 0);
    ~SSGArchive();

private slots:
    void on_saveButton_clicked();

    void on_domain_activated(int index);

    void on_openButton_clicked();

    QString getCSVString(QString data, int currentStart, int currentEnd);

    QString prepStringForCSV(QString input, bool allowReturns);

private:
    Ui::SSGArchive *ui;
};

#endif // SSGARCHIVE_H
