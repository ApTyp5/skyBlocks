#ifndef SKYBLOCKSEDITOR_H
#define SKYBLOCKSEDITOR_H

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class SkyBlocksEditor; }
QT_END_NAMESPACE

class SkyBlocksEditor : public QMainWindow
{
    Q_OBJECT

public:
    SkyBlocksEditor(QWidget *parent = nullptr);
    ~SkyBlocksEditor();

public slots:
    void sendInformation();
    void putMessage(QString msg="OK");

private:
    Ui::SkyBlocksEditor *ui;
    QNetworkAccessManager networkManager;
    QNetworkReply *reply;
};
#endif // SKYBLOCKSEDITOR_H
