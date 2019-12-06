#include "skyblockseditor.h"
#include "ui_skyblockseditor.h"

#include "Algorithm.h"
#include "qtblocksjson.h"

#include <array>

#include <QByteArray>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPainter>
#include <QMessageBox>
#include <QUrl>


SkyBlocksEditor::SkyBlocksEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SkyBlocksEditor)
    , image(QImage(QSize(420, 594), QImage::Format_RGB32))
    , reply(nullptr)

{
    ui->setupUi(this);

    QPainter painter(&image);
    painter.fillRect(image.rect(), Qt::white);
    label.setPixmap(QPixmap::fromImage(image));
    ui->scrollArea->setWidget(&label);

    QFont font = QFont("freeMono");
    QFontMetrics metrics = QFontMetrics(font);

    qDebug() << metrics.underlinePos();

    ui->scrollArea->setBackgroundRole(QPalette::Dark);
   // connect(ui->sendCodeButton, SIGNAL(clicked()), this, SLOT(sendInformation()));
    connect(ui->sendCodeButton, SIGNAL(clicked()), this, SLOT(putMessage()));
}

SkyBlocksEditor::~SkyBlocksEditor()
{
    delete ui;
}

void SkyBlocksEditor::sendInformation() {
    QString content = ui->codeEdit->toPlainText();
    QUrl url("https://postman-echo.com/post");

    QByteArray arr;
    arr.append(content);
    reply = networkManager.post(QNetworkRequest(url), arr);
    connect(reply, SIGNAL(finished()), this, SLOT(putMessage()));
    connect(reply, SIGNAL(error(code)), this, SLOT(putMessage()));
}

void SkyBlocksEditor::putMessage() {
    QString msg;
    /*if (reply->error())
        msg = reply->errorString();
    else
        msg = QString(reply->readAll());
*/
    msg = "{ \"figure\": [{\"size\": {\"width\": 26,\"height\": 14},\"center\": {\"x\": 105,\"y\": 9},\"text\": \"some text, some text\nmoooore text\n\",\"page\": 1,\"type\": \"follow\"},{\"begin\": {\"x\": 105,\"y\": 2},\"end\": {\"x\": 105,\"y\": 7},\"text\": \"\",\"page\": 1,\"type\": \"line\"},{\"size\": {\"width\": 15,\"height\": 17},\"center\": {\"x\": 105,\"y\": 15},\"text\": \"ano block\nof\ntext\n\",\"page\": 1,\"type\": \"follow\"}]}";
    QJsonDocument doc = QJsonDocument::fromJson(msg.toUtf8());

    QJsonObject obj;


    if(!doc.isNull()) {
        if(doc.isObject()) {
            obj = doc.object();
        }
    }
    else
        qDebug() << "BAD" << endl;

    QJsonValue figures = obj["figure"];

    QtBlocksJson blocks(figures);

    auto algorithm = blockFactory.CreateAlgorithm(blocks);
    auto drawData = algorithm->DrawAll();

    QPainter painter(&image);
    painter.fillRect(image.rect(), Qt::white);

    for (DrawData *data: *drawData) {
        QVector<QPointF> points;
        for (std::array<int, 2> point : data->points)
            points.push_back(QPoint(point[0], point[1]));
        if (data->figureType == LINE)
            painter.drawLine(points[0], points[1]);
        else if (data->figureType == BLOCK)
            painter.drawPolygon(points);
    }

    delete drawData;
    delete algorithm;

    label.setPixmap(QPixmap::fromImage(image));
}
