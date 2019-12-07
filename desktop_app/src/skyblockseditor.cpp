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
#include <QPoint>
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

    /*QFont font = QFont("freeMono", 8);
    QFontMetrics metrics = QFontMetrics(font);

    qDebug() << metrics.lineSpacing() << endl << metrics.maxWidth() << endl;
*/
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
    //msg = "{ \"figure\": [{\"size\": {\"width\": \"49\",\"height\": \"11\"},\"center\": {\"x\": \"105.0\",\"y\": \"7.5\"},\"text\": \"do smth\n\",\"page\": \"1\",\"type\": \"begincycle\"},{\"begin\": {\"x\": \"105.0\",\"y\": \"13.0\"},\"end\": {\"x\": \"105.0\",\"y\": \"18.0\"},\"text\": \"\",\"page\": \"1\",\"type\": \"line\"},{\"size\": {\"width\": \"77\",\"height\": \"11\"},\"center\": {\"x\": \"105\",\"y\": \"23.5\"},\"text\": \"do ano smth\n\",\"page\": \"1\",\"type\": \"endcycle\"}]}";
    msg = "{\"figure\":[{\"size\":{\"width\":\"35\",\"height\":\"11\"},\"center\":{\"x\":\"105.000000\",\"y\":\"5.500000\"},\"text\":\"block\",\"page\":\"1\",\"type\":\"follow\"},{\"begin\":{\"x\":\"105.000000\",\"y\":\"11.000000\"},\"end\":{\"x\":\"105.000000\",\"y\":\"16.000000\"},\"text\":\"\",\"page\":\"1\",\"type\":\"line\"},{\"size\":{\"width\":\"56\",\"height\":\"22\"},\"center\":{\"x\":\"105.000000\",\"y\":\"27.000000\"},\"text\":\"cond\",\"page\":\"1\",\"type\":\"fork\"},{\"begin\":{\"x\":\"77.000000\",\"y\":\"27.000000\"},\"end\":{\"x\":\"52.500000\",\"y\":\"27.000000\"},\"text\":\"\",\"page\":\"1\",\"type\":\"line\"},{\"begin\":{\"x\":\"52.500000\",\"y\":\"27.000000\"},\"end\":{\"x\":\"52.500000\",\"y\":\"43.000000\"},\"text\":\"\",\"page\":\"1\",\"type\":\"line\"},{\"begin\":{\"x\":\"133.000000\",\"y\":\"27.000000\"},\"end\":{\"x\":\"157.500000\",\"y\":\"27.000000\"},\"text\":\"Да\",\"page\":\"1\",\"type\":\"line\"},{\"begin\":{\"x\":\"157.500000\",\"y\":\"27.000000\"},\"end\":{\"x\":\"157.500000\",\"y\":\"43.000000\"},\"text\":\"\",\"page\":\"1\",\"type\":\"line\"},{\"size\":{\"width\":\"28\",\"height\":\"11\"},\"center\":{\"x\":\"52.500000\",\"y\":\"43.500000\"},\"text\":\"smth\",\"page\":\"1\",\"type\":\"follow\"},{\"begin\":{\"x\":\"52.500000\",\"y\":\"49.000000\"},\"end\":{\"x\":\"52.500000\",\"y\":\"54.000000\"},\"text\":\"\",\"page\":\"1\",\"type\":\"line\"},{\"begin\":{\"x\":\"52.500000\",\"y\":\"38.000000\"},\"end\":{\"x\":\"52.500000\",\"y\":\"38.000000\"},\"text\":\"\",\"page\":\"1\",\"type\":\"line\"},{\"size\":{\"width\":\"21\",\"height\":\"11\"},\"center\":{\"x\":\"105.000000\",\"y\":\"43.500000\"},\"text\":\"end\",\"page\":\"1\",\"type\":\"follow\"}]}";

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

    qDebug() << blocks.CheckCorrect() << endl;


    auto algorithm = blockFactory.CreateAlgorithm(blocks);
    auto drawData = algorithm->DrawAll();

    QPainter painter(&image);
    painter.fillRect(image.rect(), Qt::white);

    for (DrawData *data: *drawData) {
        QVector<QPointF> points;
        for (std::array<int, 2> point : data->points)
            points.push_back(QPoint(point[0]*2, point[1]*2));
        if (data->figureType == LINE)
            painter.drawLine(points[0], points[1]);
        else if (data->figureType == BLOCK) {
            painter.drawPolygon(points);
            painter.setFont(QFont("freeMono", 8*2));
                        painter.drawText(
                        QPoint(data->textPosX*2, data->textPosY*2),
                        data->text.c_str()
                        );
        }
    }

    label.setPixmap(QPixmap::fromImage(image));

    delete drawData;
    delete algorithm;
}
