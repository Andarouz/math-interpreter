#ifndef TERMINALMODEL_H
#define TERMINALMODEL_H

#include <QObject>
#include <QStringList>
#include <QProcess>

class TerminalModel final : public QObject {
    Q_OBJECT
    Q_PROPERTY(QStringList output READ output NOTIFY outputChanged)

public:
    explicit TerminalModel(QObject *parent = nullptr);

    Q_INVOKABLE void executeCommand(const QString &command);

    [[nodiscard]]
    QStringList output() const;

    signals:
        void outputChanged();

    private slots:
        void onCommandOutput();

private:
    QProcess process_;
    QStringList outputBuffer_;
};

#endif // TERMINALMODEL_H
