#include "webenginewrapper.h"

#include <QWebEngineScript>
#include <QWebEngineScriptCollection>
#include <QMessageBox>
#include <QWindow>

WebEngineWrapper::WebEngineWrapper(QApplication* a)
{
    this->application = a;
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);

    setMaximumSize(
        QString::fromStdString(setting.get(KEY_WIDTH)).toInt(),
        QString::fromStdString(setting.get(KEY_HEIGHT)).toInt()
    );
    setMinimumSize(
        QString::fromStdString(setting.get(KEY_WIDTH)).toInt(),
        QString::fromStdString(setting.get(KEY_HEIGHT)).toInt()
    );
    setGeometry(
        QString::fromStdString(setting.get(KEY_POS_X)).toInt(),
        QString::fromStdString(setting.get(KEY_POS_Y)).toInt(),
        QString::fromStdString(setting.get(KEY_WIDTH)).toInt(),
        QString::fromStdString(setting.get(KEY_HEIGHT)).toInt()
    );

    setUrl(QUrl(setting.get(KEY_URL).c_str()));
    QFont fon = font();
    fon.setStyleStrategy(QFont::PreferAntialias);
    setFont(fon);

    QWebEngineView* viewptr = this;
    viewptr->setAttribute(Qt::WA_TranslucentBackground);
    viewptr->page()->setBackgroundColor(Qt::transparent);
    viewptr->setStyleSheet("background:transparent");

    QString css = QString::fromStdString(setting.get(KEY_STYLE));
    qDebug() << css;
    QWebEngineScript script;
    QString s = QString::fromLatin1("(function() {"\
                                    "    css = document.createElement('style');"\
                                    "    css.type = 'text/css';"\
                                    "    css.id = '%1';"\
                                    "    document.head.appendChild(css);"\
                                    "    css.innerText = '%2';"\
                                    "})()").arg("extra-css").arg(css.simplified());

    script.setName("extra-css");
    script.setSourceCode(s);
    script.setInjectionPoint(QWebEngineScript::DocumentReady);
    script.setRunsOnSubFrames(true);
    script.setWorldId(QWebEngineScript::MainWorld);
    viewptr->page()->scripts().insert(script);

    viewptr->page()->runJavaScript(s, 0, [=](const QVariant var) {
        qDebug() << var;
    });
}

void WebEngineWrapper::display()
{
    show();
}

void WebEngineWrapper::closeEvent(QCloseEvent *event)
{
    event->accept();
    application->exit();
}
