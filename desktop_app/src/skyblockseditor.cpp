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
    , currPage(1)
    , images()
    , scaleIndex(3)
    , reply(nullptr)
    , settings()

{
    ui->setupUi(this);

    ui->scrollArea->setMaximumWidth(210 * 3);

    auto image = new QImage(
                listSizes[settings.size] * scaleIndex,
                QImage::Format_RGB32
                );

    images.push_back(image);

    QPainter painter(image);
    painter.fillRect(image->rect(), Qt::white);
    label.setPixmap(QPixmap::fromImage(*image));
    ui->scrollArea->setWidget(&label);

    ui->scrollArea->setBackgroundRole(QPalette::Dark);

    connect(ui->drawSettingsButton, SIGNAL(clicked()), this, SLOT(setDrawSettings()));
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
    obj["meta"] = settings.ToJson();

    QJsonDocument doc;
    doc.setObject(obj);

    qDebug() << QString(doc.toJson());

    reply = networkManager.post(QNetworkRequest(url), doc.toJson());
    connect(reply, SIGNAL(finished()), this, SLOT(drawAlgorithm()));
}

void SkyBlocksEditor::setDrawSettings() {
    DrawSettingsDialog dialog(settings);
    auto accept = dialog.exec();
    if (accept)
        settings = dialog.getSettings();
}

void SkyBlocksEditor::drawAlgorithm() {
    QString msg;
    if (reply->error()) {
        msg = reply->errorString();
        qDebug() << msg << endl;
    }
    else {
        msg = QString(reply->readAll());
        qDebug() << msg;
    }

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
        auto image = new QImage(
                    listSizes[settings.size] * scaleIndex,
                    QImage::Format_RGB32
                );
        newImages.push_back(image);
    }

    images = newImages;

    qDebug() << pagesCount;
    for (size_t i = 0; i < images.size(); i++) {
        QPainter painter(images[i]);
        painter.fillRect(images[i]->rect(), Qt::white);

        for (DrawData *data: *drawData) {
            if (data->page == i+1) {
                QFont drawFont = settings.font;
                drawFont.setPointSize(drawFont.pointSize() * scaleIndex);
                painter.setFont(drawFont);
                Draw(painter, *data);
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

void SkyBlocksEditor::Draw(QPainter &painter, const DrawData &drawData) {
    QVector<QPointF> points;
    for (std::array<int, 2> point : drawData.points)
        points.push_back(QPoint(point[0]*scaleIndex, point[1]*scaleIndex));
    if (drawData.figureType == LINE) {
        painter.drawLine(points[0], points[1]);
    }
    else if (drawData.figureType == BLOCK) {
        painter.drawPolygon(points);
        QRectF rectText(
                    QPointF(drawData.centerX - drawData.width / 2,
                            drawData.centerY - drawData.height / 2) * scaleIndex,
                    QSizeF(drawData.width, drawData.height) * scaleIndex
                    );
        painter.drawText(rectText, Qt::AlignCenter, drawData.text.c_str());

    }
}
