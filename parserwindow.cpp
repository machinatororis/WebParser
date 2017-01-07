#include "parserwindow.h"
#include "ui_parserwindow.h"
#include <QStringList>
#include <QtDebug>

ParserWindow::ParserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ParserWindow)
{
    ui->setupUi(this); //конструктор, через который устанавливаем форму
                      //здесь можно обращаться к элементам формы
    connect(ui->Download, SIGNAL(clicked()),SLOT(downloadFile()));
        //когда нажимаем на кнопку, вызывается downloadFile()

    manager = new QNetworkAccessManager(this);
}

ParserWindow::~ParserWindow()
{
    delete ui;
}

void ParserWindow::downloadFile()
{
    //берем адрес, введенный в текстовое поле
    url = ui->urlLineEdit->text();

    //создаем объект для запроса
    QNetworkRequest request(url);

    //выполняем запрос, получаем указатель на объект ответственный за ответ
    QNetworkReply *reply = manager->get(request);

    //подписываемся на сигнал о готовности загрузки
    connect(reply, SIGNAL(finished()), this, SLOT(ReplyFinished()));
}

void ParserWindow::ReplyFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if(reply->error() == QNetworkReply::NoError)
    {
        //получаем содержимое ответа
        QByteArray content = reply->readAll();

        //реализуем преобразование кодировки
        //(зависит от кодировки сайта)
        QTextCodec *codec = QTextCodec::codecForName("utf8");

        //выводим результат
        ui->textEdit->setPlainText(codec->toUnicode(content.data()));

        QString mail;
        QRegExp exp("(\\w+@[a-z]+\\.[a-z]+\\.*[a-z]*)");

        int count = 0;
        int pos = 0;
        while ((pos = exp.indexIn(content, pos)) != -1)
        {
            ++count;
            mail = exp.cap();
            pos += exp.matchedLength();
            ui->mailEdit->append(mail);
            qDebug() << pos << endl;
        }

        QString href;
        QRegExp exp_href("http://[(\\w+|\\.+|/+)]+|\\.\\./[(\\w+|\\.+|/+)]+");

        int count_href = 0;
        int pos_href = 0;
        while ((pos_href = exp_href.indexIn(content, pos_href)) != -1)
        {
            ++count_href;
            href = exp_href.cap();
            pos_href += exp_href.matchedLength();
            ui->mailEdit->append(href);
            qDebug() << pos_href << endl;
        }
    }
    else
    {
        //выводим описание ошибки, если она возникает
        ui->textEdit->setPlainText(reply->errorString());
    }

    //разрешаем объекту-ответа "удалиться"
    reply->deleteLater();
}
