#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "viewmodels/TerminalViewModel.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    TerminalViewModel terminalViewModel;

    engine.rootContext()->setContextProperty("terminalViewModel", &terminalViewModel);
    engine.load(QUrl(QStringLiteral("qrc:/TerminalView.qml")));

    return QGuiApplication::exec();
}
