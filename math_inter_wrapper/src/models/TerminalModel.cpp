#include "TerminalModel.h"
#include <QStringConverter>

TerminalModel::TerminalModel(QObject *parent) : QObject(parent) {
    connect(&process_, &QProcess::readyReadStandardOutput, this, &TerminalModel::onCommandOutput);
    connect(&process_, &QProcess::readyReadStandardError, this, &TerminalModel::onCommandOutput);
}

void TerminalModel::executeCommand(const QString &command) {
    process_.start(command);
    process_.waitForStarted();
}

void TerminalModel::onCommandOutput() {
    while (process_.canReadLine()) {
        outputBuffer_ << QString::fromUtf8(process_.readLine()).trimmed();
    }
    emit outputChanged();
}

QStringList TerminalModel::output() const {
    return outputBuffer_;
}
