#include "TerminalViewModel.h"

TerminalViewModel::TerminalViewModel(QObject *parent) : QObject(parent) {
    connect(&model_, &TerminalModel::outputChanged, this, &TerminalViewModel::outputChanged);
}

QString TerminalViewModel::command() const {
    return command_;
}

void TerminalViewModel::setCommand(const QString &command) {
    if (command_ != command) {
        command_ = command;
        emit commandChanged();
    }
}

QStringList TerminalViewModel::output() const {
    return model_.output();
}

void TerminalViewModel::submitCommand() {
    model_.executeCommand(command_);
}
