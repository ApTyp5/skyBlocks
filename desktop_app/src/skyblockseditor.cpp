#include "skyblockseditor.h"
#include "ui_skyblockseditor.h"

#include "Algorithm.h"
#include "qtblocksjson.h"

#include <array>

#include <QByteArray>
#include <QDebug>
#include <QErrorMessage>
#include <QFileDialog>
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
    , currPage(0)
    , pagesCount(0)
    , scaleIndex(3)
    , drawData(nullptr)
    , settings()
    , reply(nullptr)

{
    ui->setupUi(this);

    ui->scrollArea->setFixedWidth(210 * 3);
    ui->imageButtonsWidget->setMaximumWidth(210 * 3);

    ui->scrollArea->setWidget(&label);

    ui->scrollArea->setBackgroundRole(QPalette::Dark);

    connect(ui->drawSettingsButton, SIGNAL(clicked()), this, SLOT(setDrawSettings()));
    connect(ui->sendCodeButton, SIGNAL(clicked()), this, SLOT(sendInformation()));
    connect(ui->nextPageButton, SIGNAL(clicked()), this, SLOT(nextImagePage()));
    connect(ui->prevPageButton, SIGNAL(clicked()), this, SLOT(prevImagePage()));
    connect(ui->increaseScaleButton, SIGNAL(clicked()), this, SLOT(increaseImageScale()));
    connect(ui->reduceScaleButton, SIGNAL(clicked()), this, SLOT(reduceImageScale()));
    connect(ui->saveDiagramButton, SIGNAL(clicked()), this, SLOT(saveDiagram()));
}

SkyBlocksEditor::~SkyBlocksEditor()
{
    if (drawData)
        delete drawData;
    delete ui;
}

void SkyBlocksEditor::sendInformation() {
    ui->messagesBrowser->clear();
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

    QNetworkRequest req;
    req.setUrl(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    reply = networkManager.post(req, doc.toJson());
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

    QJsonValue errors = obj["error"];

    if (errors != QJsonValue::Undefined) {
        for (QJsonValue error : errors.toArray()) {
            QString row = QString("Row: ") + error["row"].toString();
            QString column = QString("Column: ") + error["col"].toString();
            QString text = row + QString(" ") + column + QString(" ")
                    + error["text"].toString() + QString("\n");
            ui->messagesBrowser->setTextColor(Qt::red);
            ui->messagesBrowser->append(text);
        }
    } else {

    }

    ui->saveDiagramButton->setEnabled(true);

    QJsonValue figures = obj["figure"];

    QtBlocksJson blocks(figures);

    if (blocks.CheckCorrect())
        qDebug() << "Drawing objects created correctly" << endl;

    auto algorithm = blockFactory.CreateAlgorithm(blocks);
    if (!algorithm)
        return;

    if (drawData)
        delete drawData;

    drawData = algorithm->DrawAll();

    pagesCount = algorithm->getPagesCount();

    DrawAll();

    delete algorithm;
}

void SkyBlocksEditor::nextImagePage() {
    qDebug() << currPage;
    if (currPage < images.size()) {
        label.setPixmap(QPixmap::fromImage(*images[currPage++]));
        auto pl = std::to_string(currPage) + "/" + std::to_string(images.size());
        ui->pageLabel->setText(pl.c_str());
    }
}

void SkyBlocksEditor::prevImagePage() {
    qDebug() << currPage;
    if (currPage > 1) {
        label.setPixmap(QPixmap::fromImage(*images[--currPage - 1]));
        auto pl = std::to_string(currPage) + "/" + std::to_string(images.size());
        ui->pageLabel->setText(pl.c_str());
    }
}

void SkyBlocksEditor::increaseImageScale() {
    if (!drawData)
        return;
    if (scaleIndex + 1 > 10)
        return;
    scaleIndex += 1;
    DrawAll();
}

void SkyBlocksEditor::reduceImageScale() {
    if (!drawData)
        return;
    if (scaleIndex - 1 < 3)
        return;
    scaleIndex -= 1;
    DrawAll();
}

void SkyBlocksEditor::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
    case Qt::Key_F1:
        nextImagePage();
        break;
    case Qt::Key_F2:
        prevImagePage();
        break;
    }
}

void SkyBlocksEditor::DrawAll() {
    for(auto image: images) {
        delete image;
    }

    auto pl = "1/" + std::to_string(pagesCount);
    ui->pageLabel->setText(pl.c_str());

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
            if (data->page == i + 1) {
                QFont drawFont = settings.font;
                drawFont.setPointSize(drawFont.pointSize() * scaleIndex);
                painter.setFont(drawFont);
                Draw(painter, *data);
            }
        }
    }

    label.setPixmap(QPixmap::fromImage(*images[0]));
    currPage = 1;
}

void SkyBlocksEditor::Draw(QPainter &painter, const DrawData &drawData) {
    QVector<QPointF> points;
    for (std::array<double, 2> point : drawData.points)
        points.push_back(QPoint(point[0]*scaleIndex, point[1]*scaleIndex));
    if (drawData.figureType == LINE) {

        painter.drawLine(points[0], points[1]);
        painter.drawText(QPoint(drawData.centerX, drawData.centerY) * scaleIndex,
                         drawData.text.c_str());

    } else if (drawData.figureType == TERMINAL) {
        painter.drawLine(points[0], points[1]);
        painter.drawLine(points[2], points[3]);
        QPainterPath pathLeft;

        pathLeft.moveTo(points[3]);
        QPointF p1 = points[3];
        p1 -= {drawData.width / 2 * scaleIndex, 0};
        QPointF p2 = points[0];
        p2 -= {drawData.width / 2 * scaleIndex, 0};
        pathLeft.cubicTo(p1, p2, points[0]);
        painter.drawPath(pathLeft);

        QPainterPath pathRight;
        pathRight.moveTo(points[2]);
        p1 = points[2];
        p1 += {drawData.width / 2 * scaleIndex, 0};
        p2 = points[1];
        p2 += {drawData.width / 2 * scaleIndex, 0};
        pathRight.cubicTo(p1, p2, points[1]);
        painter.drawPath(pathRight);

        QRectF rectText(
                   QPointF(drawData.centerX - drawData.width / 2,
                           drawData.centerY - drawData.height / 2 + settings.yp) * scaleIndex,
                            QSizeF(drawData.width, drawData.height -  settings.yp) * scaleIndex
                    );

       painter.drawText(rectText, Qt::AlignHCenter, drawData.text.c_str());
    } else if (drawData.figureType == PAGE_CHANGER) {
        QPointF p = points[0];
        p += {0, qreal(settings.yp)};
        QRectF rectText(
                    p,
                    QSizeF(drawData.width, drawData.height - settings.yp) * scaleIndex
                    );
        painter.drawEllipse(rectText);
        painter.drawText(rectText, Qt::AlignCenter, drawData.text.c_str());
    } else {
        painter.drawPolygon(points);

        if (drawData.figureType == IF){
            QRectF rectText(
                        QPointF(drawData.centerX - drawData.width / 4,
                                drawData.centerY - drawData.height / 4) * scaleIndex,
                        QSizeF(drawData.width / 2, drawData.height / 2) * scaleIndex
                        );
            painter.drawText(rectText, Qt::AlignHCenter, drawData.text.c_str());

        } else if (drawData.figureType == BLOCK) {
            QRectF rectText(
                        QPointF(drawData.centerX - drawData.width / 2,
                                drawData.centerY - drawData.height / 2 + settings.yp) * scaleIndex,
                        QSizeF(drawData.width, drawData.height - settings.yp) * scaleIndex
                        );

            painter.drawText(rectText, Qt::AlignHCenter, drawData.text.c_str());
        }
    }
}

void SkyBlocksEditor::saveDiagram() {
    int prevScaleIndex = scaleIndex;
    scaleIndex = 10;
    DrawAll();
    for (int i = 0; i < images.size(); i++) {
        QString title = tr("Сохранение диаграммы (страница ") + QString(i) + tr(")");
        QString fileName = QFileDialog::getSaveFileName(this,
                            title, "",
                            tr("Image Files (*.png *.jpg *.bmp);;All Files (*)"));
        if (fileName == "")
            break;
        if (!images[i]->save(fileName, "png")) {
            QErrorMessage message(this);
            message.showMessage("Не удалось сохранить изображение");
        }
    }
    scaleIndex = prevScaleIndex;
    DrawAll();
}
