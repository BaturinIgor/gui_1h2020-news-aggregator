#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDomNode>
#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QWidget>
#include <QTreeWidgetItem>

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
    Information info[100];
    int i;
    int count, currentColumn;
    QTreeWidgetItem *currentItem;
    QStringList columnNames;
    void addElem(Information info);
    void traverseNode(const QDomNode& node);

private slots:
    void on_pushButton_clicked();
    void replyFinished(QNetworkReply*);
};

#endif // MAINWINDOW_H
