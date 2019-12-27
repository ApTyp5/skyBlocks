#include "drawsettings.h"
#include "ui_drawsettings.h"

QJsonObject DrawSettings::ToJson() {
    QFontMetrics metrics = QFontMetrics(font);
    QJsonObject result = QJsonObject({
        QPair<QString, QJsonValue>({"lh", QJsonValue(metrics.lineSpacing())}),
        QPair<QString, QJsonValue>({"sw", QJsonValue(metrics.maxWidth())}),
        QPair<QString, QJsonValue>({"xp", QJsonValue(int(xp))}),
        QPair<QString, QJsonValue>({"yp", QJsonValue(int(yp))}),
        QPair<QString, QJsonValue>({"xm", QJsonValue(int(xm))}),
        QPair<QString, QJsonValue>({"ym", QJsonValue(int(ym))}),
        QPair<QString, QJsonValue>({"bs", QJsonValue(int(bs))}),
        QPair<QString, QJsonValue>({"pw", QJsonValue(listSizes[size].width())}),
        QPair<QString, QJsonValue>({"ph", QJsonValue(listSizes[size].height())}),
    });
    return result;
}

DrawSettingsDialog::DrawSettingsDialog(const DrawSettings &s, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DrawSettingsDialog)
{
    ui->setupUi(this);

    this->setFixedSize(this->size());
    ui->listSizesBox->addItems(listSizesStrings);
    ui->languageBox->addItems(languagesList);
    ui->xmBox->setValue(s.xm);
    ui->ymBox->setValue(s.ym);
    ui->xpBox->setValue(s.xp);
    ui->ypBox->setValue(s.yp);
    ui->bsBox->setValue(s.bs);
    ui->languageBox->setCurrentIndex(s.language);

    ui->listSizesBox->setCurrentIndex(s.size);
    ui->fontSizeBox->setValue(s.font.pointSize());
    ui->fontComboBox->setCurrentFont(s.font);
}

DrawSettingsDialog::~DrawSettingsDialog()
{
    delete ui;
}

DrawSettings DrawSettingsDialog::getMetaSettings() const {
    DrawSettings settings;
    settings.xm = ui->xmBox->value();
    settings.ym = ui->ymBox->value();
    settings.xp = ui->xpBox->value();
    settings.yp = ui->ypBox->value();
    settings.bs = ui->bsBox->value();
    settings.language = ui->languageBox->currentIndex();
    settings.font.setPointSize(ui->fontSizeBox->value());
    settings.size = ListSizes(ui->listSizesBox->currentIndex());
    settings.font = ui->fontComboBox->currentFont();
    return settings;
}
