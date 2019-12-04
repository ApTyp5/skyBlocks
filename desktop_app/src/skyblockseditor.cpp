#include "skyblockseditor.h"
#include "./ui_skyblockseditor.h"
#include <QMessageBox>
#include <QByteArray>
#include <QUrl>

SkyBlocksEditor::SkyBlocksEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SkyBlocksEditor)
    , reply(nullptr)

{
    ui->setupUi(this);    

    connect(ui->sendCodeButton, SIGNAL(clicked()), this, SLOT(sendInformation()));
}

SkyBlocksEditor::~SkyBlocksEditor()
{
    delete ui;
}

void SkyBlocksEditor::sendInformation() {
    QString content = ui->codeEdit->toPlainText();
    QUrl url("https://postman-echo.com/post");


//    reply = networkManager.get(QNetworkRequest(url));
    QByteArray arr;
    arr.append(content);
    reply = networkManager.post(QNetworkRequest(url), arr);
    connect(reply, SIGNAL(finished()), this, SLOT(putMessage()));
    connect(reply, SIGNAL(error(code)), this, SLOT(putMessage()));

}

void SkyBlocksEditor::putMessage(QString msg) {
    if (reply->error())
        msg = reply->errorString();
    else
        msg = QString(reply->readAll());
    QMessageBox msgBox(QMessageBox::Information, "Message", msg, QMessageBox::Ok, nullptr);

    msgBox.exec();

}
