#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDomDocument>
#include <QListView>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    count = 0;
    i = 0;
    currentItem = NULL;
    currentColumn = 0;
    ui->treeWidget->setColumnCount(4);
    columnNames << "Заголовок" << "Дата и Время" << "Категория" << "Сайт";
    ui->treeWidget->setColumnWidth(0, 450);
    ui->treeWidget->setColumnWidth(1, 140);
    ui->treeWidget->setColumnWidth(2, 120);
    ui->treeWidget->setColumnWidth(3, 150);
    ui->treeWidget->setHeaderLabels(columnNames);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addElem(Information info) {
    QTreeWidgetItem *newItem = new QTreeWidgetItem(ui->treeWidget, ui->treeWidget->currentItem());
    newItem->setText(0, info.getTitle());
    newItem->setText(1, info.getDate());
    newItem->setText(2, info.getSite());
    newItem->setText(3, info.getInfo());
    newItem->setExpanded(true);
}
/*QString str[5] = {"Раскрыты вероятные сроки второй волны коронавируса в России", "01 May 2020 13:56:51", "Россия", "Lenta.ru"};
for (int i = 0; i < 40; i++)
    addElem(str);
currentItem = NULL;
*/
void MainWindow::on_pushButton_clicked()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    manager->get(QNetworkRequest(QUrl("http://news.yandex.ru/Novosibirsk/index.rss")));
    currentItem = NULL;

}

void MainWindow::replyFinished(QNetworkReply* reply) {
    QString data = QString::fromUtf8( reply->readAll() );
    QFile file("test.xml");
    //ui->plainTextEdit->document()->setPlainText(data);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(data.toLocal8Bit().data());
        file.close();
    }

    QDomDocument domDoc;
    if(file.open(QIODevice::ReadOnly)) {
        if(domDoc.setContent(&file)) {
            QDomElement domElement= domDoc.documentElement();
            traverseNode(domElement);
            for(int j = 0; j < i; j++) {
                addElem(info[j]);
            }
        }
        file.close();
    }
}

void MainWindow::traverseNode(const QDomNode& node)
{
    QDomNode domNode = node.firstChild();
    while(!domNode.isNull() && i < 10) {
        if(domNode.isElement()) {
           QDomElement domElement = domNode.toElement();
           if(!domElement.isNull()) {
               if(domElement.tagName() == "contact") {
                   qDebug() << "Attr: "
                            << domElement.attribute("number", "");
               }
               else {
                   qDebug() << "TagName: " << domElement.tagName()
                            << "\tText: " << domElement.text();
                   if (domElement.tagName() == "title")
                       info[i].setTitle(domElement.text());
                   else if (domElement.tagName() == "pubDate") {
                       info[i].setDate(domElement.text());
                       i++;
                   }
                   else if (domElement.tagName() == "guid")
                       info[i].setSite(domElement.text());
                   else if (domElement.tagName() == "link")
                       info[i].setInfo(domElement.text());
              }
           }
        }
        traverseNode(domNode);
        domNode = domNode.nextSibling();
     }
    //ui->plainTextEdit->document()->setPlainText(res);
}

