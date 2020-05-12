#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDomNode>
#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QWidget>
#include <QTreeWidgetItem>
#include <QVector>
#include <QPair>

#include "information.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Information* info;
    QVector <QPair <QString, QString> > headings;

    int index, amountOfNews;
    QTreeWidgetItem *currentItem;
    QStringList columnNames;
    void addElem(Information info);
    void traverseNode(const QDomNode& node);
    void headingInit();
    void newsSorting(int criterion);

private slots:
    void replyFinished(QNetworkReply*);
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
