#include "settingwindow.h"
#include "./ui_settingwindow.h"
#include <QInputDialog>
#include <QWebEngineScriptCollection>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEditHeight->setText(QString::fromStdString(setting.get(KEY_HEIGHT)));
    ui->lineEditWidth->setText(QString::fromStdString(setting.get(KEY_WIDTH)));
    ui->lineEditUrl->setText(QString::fromStdString(setting.get(KEY_URL)));
    ui->plainTextEditStyle->setPlainText(QString::fromStdString(setting.get(KEY_STYLE)));
    setAttribute(Qt::WA_ShowModal);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBoxUrlView_clicked(bool checked)
{
    if (checked)
    {
        ui->lineEditUrl->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEditUrl->setEchoMode(QLineEdit::Password);
    }
}


void MainWindow::on_pushButtonApply_clicked()
{
    setting.put(KEY_WIDTH, ui->lineEditWidth->text().toStdString());
    setting.put(KEY_HEIGHT, ui->lineEditHeight->text().toStdString());
    setting.put(KEY_URL, ui->lineEditUrl->text().toStdString());
    setting.put(KEY_STYLE, ui->plainTextEditStyle->toPlainText().toStdString());
    setting.store();
    qDebug() << pos().x();
    QMessageBox::information(this, "Information", "If you want configurate in one day, "
                                                  "you can use command 'danmu setting'");
    this->close();
}

