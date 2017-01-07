#ifndef PARSERWINDOW_H
#define PARSERWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QTextCodec>  //для преобразования кодировки

namespace Ui {
class ParserWindow;
}

class ParserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ParserWindow(QWidget *parent = 0);
    ~ParserWindow();

    void startRequest(QUrl url); //стартовый запрос

private slots:
    void downloadFile(); //когда щелкаем по кнопке Download
    void ReplyFinished(); //cлот, выполняемый при завершении запроса

private:
    Ui::ParserWindow *ui; //создается экземпляр, через который
                          //мы обращаемся к форме
    QUrl url;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;

};

#endif // PARSERWINDOW_H
