#ifndef TERMINALVIEWMODEL_H
#define TERMINALVIEWMODEL_H

#include <QObject>
#include "../models/TerminalModel.h"

class TerminalViewModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString command READ command WRITE setCommand NOTIFY commandChanged)
    Q_PROPERTY(QStringList output READ output NOTIFY outputChanged)

public:
    explicit TerminalViewModel(QObject *parent = nullptr);

    QString command() const;
    void setCommand(const QString &command);

    QStringList output() const;

    Q_INVOKABLE void submitCommand();

    signals:
        void commandChanged();
    void outputChanged();

private:
    TerminalModel model_;
    QString command_;
};

#endif // TERMINALVIEWMODEL_H
