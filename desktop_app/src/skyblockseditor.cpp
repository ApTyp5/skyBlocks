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
    , images()
    , currPage(1)
    , reply(nullptr)

{
    ui->setupUi(this);

    auto image = new QImage(QSize(420, 594), QImage::Format_RGB32);

    images.push_back(image);

    QPainter painter(image);
    painter.fillRect(image->rect(), Qt::white);
    label.setPixmap(QPixmap::fromImage(*image));
    ui->scrollArea->setWidget(&label);

    ui->scrollArea->setBackgroundRole(QPalette::Dark);
    connect(ui->sendCodeButton, SIGNAL(clicked()), this, SLOT(sendInformation()));
}

SkyBlocksEditor::~SkyBlocksEditor()
{
    delete ui;
}

void SkyBlocksEditor::sendInformation() {
    QString content = ui->codeEdit->toPlainText();
    QUrl url("http://localhost:6000");

    QFont font = QFont("freeMono", 8);
    QFontMetrics metrics = QFontMetrics(font);

    QJsonObject obj;

    obj["text"] = content;
    obj["meta"] = QJsonObject({
        QPair<QString, QJsonValue>({"lh", QJsonValue(metrics.lineSpacing())}),
        QPair<QString, QJsonValue>({"sw", QJsonValue(metrics.maxWidth())}),
        QPair<QString, QJsonValue>({"xp", QJsonValue(0)}),
        QPair<QString, QJsonValue>({"yp", QJsonValue(0)}),
        QPair<QString, QJsonValue>({"xm", QJsonValue(0)}),
        QPair<QString, QJsonValue>({"ym", QJsonValue(0)}),
        QPair<QString, QJsonValue>({"bs", QJsonValue(5)}),
        QPair<QString, QJsonValue>({"pw", QJsonValue(210)}),
        QPair<QString, QJsonValue>({"ph", QJsonValue(297)}),
        });

    QJsonDocument doc;
    doc.setObject(obj);

    qDebug() << QString(doc.toJson());

    reply = networkManager.post(QNetworkRequest(url), doc.toJson());
    connect(reply, SIGNAL(finished()), this, SLOT(putMessage()));
}

void SkyBlocksEditor::putMessage() {
    QString msg;
    if (reply->error()) {
        msg = reply->errorString();
        qDebug() << msg << endl;
    }
    else {
        msg = QString(reply->readAll());
        qDebug() << msg;
    }
    //msg = "{ \"figure\": [{\"size\": {\"width\": \"49\",\"height\": \"11\"},\"center\": {\"x\": \"105.0\",\"y\": \"7.5\"},\"text\": \"do smth\n\",\"page\": \"1\",\"type\": \"begincycle\"},{\"begin\": {\"x\": \"105.0\",\"y\": \"13.0\"},\"end\": {\"x\": \"105.0\",\"y\": \"18.0\"},\"text\": \"\",\"page\": \"1\",\"type\": \"line\"},{\"size\": {\"width\": \"77\",\"height\": \"11\"},\"center\": {\"x\": \"105\",\"y\": \"23.5\"},\"text\": \"do ano smth\n\",\"page\": \"1\",\"type\": \"endcycle\"}]}";
    //msg = "{\"figure\":[{\"size\":{\"width\":\"35\",\"height\":\"11\"},\"center\":{\"x\":\"105.000000\",\"y\":\"5.500000\"},\"text\":\"block\",\"page\":\"1\",\"type\":\"follow\"},{\"begin\":{\"x\":\"105.000000\",\"y\":\"11.000000\"},\"end\":{\"x\":\"105.000000\",\"y\":\"16.000000\"},\"text\":\"\",\"page\":\"1\",\"type\":\"line\"},{\"size\":{\"width\":\"56\",\"height\":\"22\"},\"center\":{\"x\":\"105.000000\",\"y\":\"27.000000\"},\"text\":\"cond\",\"page\":\"1\",\"type\":\"fork\"},{\"begin\":{\"x\":\"77.000000\",\"y\":\"27.000000\"},\"end\":{\"x\":\"52.500000\",\"y\":\"27.000000\"},\"text\":\"\",\"page\":\"1\",\"type\":\"line\"},{\"begin\":{\"x\":\"52.500000\",\"y\":\"27.000000\"},\"end\":{\"x\":\"52.500000\",\"y\":\"43.000000\"},\"text\":\"\",\"page\":\"1\",\"type\":\"line\"},{\"begin\":{\"x\":\"133.000000\",\"y\":\"27.000000\"},\"end\":{\"x\":\"157.500000\",\"y\":\"27.000000\"},\"text\":\"Да\",\"page\":\"1\",\"type\":\"line\"},{\"begin\":{\"x\":\"157.500000\",\"y\":\"27.000000\"},\"end\":{\"x\":\"157.500000\",\"y\":\"43.000000\"},\"text\":\"\",\"page\":\"1\",\"type\":\"line\"},{\"size\":{\"width\":\"28\",\"height\":\"11\"},\"center\":{\"x\":\"52.500000\",\"y\":\"48.500000\"},\"text\":\"smth\",\"page\":\"1\",\"type\":\"follow\"},{\"begin\":{\"x\":\"52.500000\",\"y\":\"54.000000\"},\"end\":{\"x\":\"52.500000\",\"y\":\"59.000000\"},\"text\":\"\",\"page\":\"1\",\"type\":\"line\"},{\"begin\":{\"x\":\"52.500000\",\"y\":\"43.000000\"},\"end\":{\"x\":\"52.500000\",\"y\":\"43.000000\"},\"text\":\"\",\"page\":\"1\",\"type\":\"line\"},{\"size\":{\"width\":\"21\",\"height\":\"11\"},\"center\":{\"x\":\"105.000000\",\"y\":\"48.500000\"},\"text\":\"end\",\"page\":\"1\",\"type\":\"follow\"}]}";

  /* msg = "{\n"
              "    \"figure\": [\n"
              "        {\n"
              "            \"size\": {\n"
              "                \"width\": \"21\",\n"
              "                \"height\": \"11\"\n"
              "            },\n"
              "            \"center\": {\n"
              "                \"x\": \"105.000000\",\n"
              "                \"y\": \"5.500000\"\n"
              "            },\n"
              "            \"text\": \"hi!\\n\",\n"
              "            \"page\": \"1\",\n"
              "            \"type\": \"follow\"\n"
              "        },\n"
              "        {\n"
              "            \"begin\": {\n"
              "                \"x\": \"105.000000\",\n"
              "                \"y\": \"11.000000\"\n"
              "            },\n"
              "            \"end\": {\n"
              "                \"x\": \"105.000000\",\n"
              "                \"y\": \"16.000000\"\n"
              "            },\n"
              "            \"text\": \"\",\n"
              "            \"page\": \"1\",\n"
              "            \"type\": \"line\"\n"
              "        },\n"
              "        {\n"
              "            \"size\": {\n"
              "                \"width\": \"56\",\n"
              "                \"height\": \"22\"\n"
              "            },\n"
              "            \"center\": {\n"
              "                \"x\": \"105.000000\",\n"
              "                \"y\": \"27.000000\"\n"
              "            },\n"
              "            \"text\": \"cond\\n\",\n"
              "            \"page\": \"1\",\n"
              "            \"type\": \"fork\"\n"
              "        },\n"
              "        {\n"
              "            \"begin\": {\n"
              "                \"x\": \"77.000000\",\n"
              "                \"y\": \"27.000000\"\n"
              "            },\n"
              "            \"end\": {\n"
              "                \"x\": \"52.500000\",\n"
              "                \"y\": \"27.000000\"\n"
              "            },\n"
              "            \"text\": \"\",\n"
              "            \"page\": \"1\",\n"
              "            \"type\": \"line\"\n"
              "        },\n"
              "        {\n"
              "            \"begin\": {\n"
              "                \"x\": \"52.500000\",\n"
              "                \"y\": \"27.000000\"\n"
              "            },\n"
              "            \"end\": {\n"
              "                \"x\": \"52.500000\",\n"
              "                \"y\": \"43.000000\"\n"
              "            },\n"
              "            \"text\": \"\",\n"
              "            \"page\": \"1\",\n"
              "            \"type\": \"line\"\n"
              "        },\n"
              "        {\n"
              "            \"begin\": {\n"
              "                \"x\": \"133.000000\",\n"
              "                \"y\": \"27.000000\"\n"
              "            },\n"
              "            \"end\": {\n"
              "                \"x\": \"157.500000\",\n"
              "                \"y\": \"27.000000\"\n"
              "            },\n"
              "            \"text\": \"Да\",\n"
              "            \"page\": \"1\",\n"
              "            \"type\": \"line\"\n"
              "        },\n"
              "        {\n"
              "            \"begin\": {\n"
              "                \"x\": \"157.500000\",\n"
              "                \"y\": \"27.000000\"\n"
              "            },\n"
              "            \"end\": {\n"
              "                \"x\": \"157.500000\",\n"
              "                \"y\": \"43.000000\"\n"
              "            },\n"
              "            \"text\": \"\",\n"
              "            \"page\": \"1\",\n"
              "            \"type\": \"line\"\n"
              "        },\n"
              "        {\n"
              "            \"size\": {\n"
              "                \"width\": \"70\",\n"
              "                \"height\": \"22\"\n"
              "            },\n"
              "            \"center\": {\n"
              "                \"x\": \"52.500000\",\n"
              "                \"y\": \"54.000000\"\n"
              "            },\n""            \"text\": \"cond2\\n\",\n"
          "            \"page\": \"1\",\n"
          "            \"type\": \"fork\"\n"
          "        },\n"
          "        {\n"
          "            \"begin\": {\n"
          "                \"x\": \"17.500000\",\n"
          "                \"y\": \"54.000000\"\n"
          "            },\n"
          "            \"end\": {\n"
          "                \"x\": \"26.250000\",\n"
          "                \"y\": \"54.000000\"\n"
          "            },\n"
          "            \"text\": \"\",\n"
          "            \"page\": \"1\",\n"
          "            \"type\": \"line\"\n"
          "        },\n"
          "        {\n"
          "            \"begin\": {\n"
          "                \"x\": \"26.250000\",\n"
          "                \"y\": \"54.000000\"\n"
          "            },\n"
          "            \"end\": {\n"
          "                \"x\": \"26.250000\",\n"
          "                \"y\": \"70.000000\"\n"
          "            },\n"
          "            \"text\": \"\",\n"
          "            \"page\": \"1\",\n"
          "            \"type\": \"line\"\n"
          "        },\n"
          "        {\n"
          "            \"begin\": {\n"
          "                \"x\": \"87.500000\",\n"
          "                \"y\": \"54.000000\"\n"
          "            },\n"
          "            \"end\": {\n"
          "                \"x\": \"78.750000\",\n"
          "                \"y\": \"54.000000\"\n"
          "            },\n"
          "            \"text\": \"Да\",\n"
          "            \"page\": \"1\",\n"
          "            \"type\": \"line\"\n"
          "        },\n"
          "        {\n"
          "            \"begin\": {\n"
          "                \"x\": \"78.750000\",\n"
          "                \"y\": \"54.000000\"\n"
          "            },\n"
          "            \"end\": {\n"
          "                \"x\": \"78.750000\",\n"
          "                \"y\": \"70.000000\"\n"
          "            },\n"
          "            \"text\": \"\",\n"
          "            \"page\": \"1\",\n"
          "            \"type\": \"line\"\n"
          "        },\n"
          "        {\n"
          "            \"size\": {\n"
          "                \"width\": \"42\",\n"
          "                \"height\": \"11\"\n"
          "            },\n"
          "            \"center\": {\n"
          "                \"x\": \"26.250000\",\n"
          "                \"y\": \"75.500000\"\n"
          "            },\n"
          "            \"text\": \"inner2\\n\",\n"
          "            \"page\": \"1\",\n"
          "            \"type\": \"follow\"\n"
          "        },\n"
          "        {\n"
          "            \"begin\": {\n"
          "                \"x\": \"26.250000\",\n"
          "                \"y\": \"81.000000\"\n"
          "            },\n"
          "            \"end\": {\n"
          "                \"x\": \"26.250000\",\n"
          "                \"y\": \"86.000000\"\n"
          "            },\n"
          "            \"text\": \"\",\n"
          "            \"page\": \"1\",\n"
          "            \"type\": \"line\"\n"
          "        },\n"
          "        {\n"
          "            \"begin\": {\n"
          "                \"x\": \"78.750000\",\n"
          "                \"y\": \"70.000000\"\n"
          "            },\n"
          "            \"end\": {\n"
          "                \"x\": \"78.750000\",\n"
          "                \"y\": \"86.000000\"\n"
          "            },\n"
          "            \"text\": \"\",\n"
          "            \"page\": \"1\",\n"
          "            \"type\": \"line\"\n"
          "        },\n"
          "        {\n"
          "            \"begin\": {\n"
          "                \"x\": \"26.250000\",\n"
          "                \"y\": \"86.000000\"\n"
          "            },\n"
          "            \"end\": {\n"
          "                \"x\": \"78.750000\",\n"
          "                \"y\": \"86.000000\"\n"
                    "            },\n"
                    "            \"text\": \"\",\n"
                    "            \"page\": \"1\",\n"
                    "            \"type\": \"line\"\n"
                    "        },\n"
                    "        {\n"
                    "            \"begin\": {\n"
                    "                \"x\": \"52.500000\",\n"
                    "                \"y\": \"86.000000\"\n"
                    "            },\n"
                    "            \"end\": {\n"
                    "                \"x\": \"52.500000\",\n"
                    "                \"y\": \"91.000000\"\n"
                    "            },\n"
                    "            \"text\": \"\",\n"
                    "            \"page\": \"1\",\n"
                    "            \"type\": \"line\"\n"
                    "        },\n"
                    "        {\n"
                    "            \"begin\": {\n"
                    "                \"x\": \"157.500000\",\n"
                    "                \"y\": \"43.000000\"\n"
                    "            },\n"
                    "            \"end\": {\n"
                    "                \"x\": \"157.500000\",\n"
                    "                \"y\": \"91.000000\"\n"
                    "            },\n"
                    "            \"text\": \"\",\n"
                    "            \"page\": \"1\",\n"
                    "            \"type\": \"line\"\n"
                    "        },\n"
                    "        {\n"
                    "            \"begin\": {\n"
                    "                \"x\": \"52.500000\",\n"
                    "                \"y\": \"91.000000\"\n"
                    "            },\n"
                    "            \"end\": {\n"
                    "                \"x\": \"157.500000\",\n"
                    "                \"y\": \"91.000000\"\n"
                    "            },\n"
                    "            \"text\": \"\",\n"
                    "            \"page\": \"1\",\n"
                    "            \"type\": \"line\"\n"
                    "        },\n"
                    "        {\n"
                    "            \"begin\": {\n"
                    "                \"x\": \"105.000000\",\n"
                    "                \"y\": \"91.000000\"\n"
                    "            },\n"
                    "            \"end\": {\n"
                    "                \"x\": \"105.000000\",\n"
                    "                \"y\": \"96.000000\"\n"
                    "            },\n"
                    "            \"text\": \"\",\n"
                    "            \"page\": \"1\",\n"
                    "            \"type\": \"line\"\n"
                    "        },\n"
                    "        {\n"
                    "            \"size\": {\n"
                    "                \"width\": \"28\",\n"
                    "                \"height\": \"11\"\n"
                    "            },\n"
                    "            \"center\": {\n"
                    "                \"x\": \"105.000000\",\n"
                    "                \"y\": \"101.500000\"\n"
                    "            },\n"
                    "            \"text\": \"bye!\\n\",\n"
                    "            \"page\": \"1\",\n"
                    "            \"type\": \"follow\"\n"
                    "        }\n"
                    "    ]\n"
                    "}";*/

    QJsonDocument doc = QJsonDocument::fromJson(msg.toUtf8());

    QJsonObject obj;


    if(!doc.isNull()) {
        if(doc.isObject()) {
            obj = doc.object();
        }
    }
    else {
        qDebug() << "JSON not parsed" << endl;
        return;
    }

    QJsonValue figures = obj["figure"];

    QtBlocksJson blocks(figures);

    if (blocks.CheckCorrect())
        qDebug() << "Drawing objects created correctly" << endl;

    auto algorithm = blockFactory.CreateAlgorithm(blocks);
    if (!algorithm)
        return;
    auto drawData = algorithm->DrawAll();

    int pagesCount = algorithm->getPagesCount();

    for(auto image: images) {
        delete image;
    }

    std::vector<QImage *> newImages;
    for (int i = 0; i < pagesCount; i++) {
        auto image = new QImage(QSize(420, 594), QImage::Format_RGB32);
        newImages.push_back(image);
    }

    images = newImages;

    qDebug() << pagesCount;
    for (int i = 0; i < images.size(); i++) {
        QPainter painter(images[i]);
        painter.fillRect(images[i]->rect(), Qt::white);

        for (DrawData *data: *drawData) {
            if (data->page == i+1) {
                QVector<QPointF> points;
                for (std::array<int, 2> point : data->points)
                    points.push_back(QPoint(point[0]*2, point[1]*2));
                if (data->figureType == LINE)
                    painter.drawLine(points[0], points[1]);
                else if (data->figureType == BLOCK) {
                    painter.drawPolygon(points);
                }
                painter.setFont(QFont("freeMono", 8*2));
                                painter.drawText(
                                QPoint(data->textPosX*2, data->textPosY*2),
                                data->text.c_str()
                                );
            }
        }
    }
    label.setPixmap(QPixmap::fromImage(*images[0]));
    currPage = 1;
    for (DrawData *data: *drawData)
        delete data;

    delete drawData;
    delete algorithm;
}

void SkyBlocksEditor::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
    case Qt::Key_F1:
        qDebug() << currPage;
        if (currPage < images.size()) {
            label.setPixmap(QPixmap::fromImage(*images[currPage++]));
        }
        break;
    case Qt::Key_F2:
        qDebug() << currPage;
        if (currPage > 1) {
            label.setPixmap(QPixmap::fromImage(*images[--currPage - 1]));
        }
        break;
    }
}
