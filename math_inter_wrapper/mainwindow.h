#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QKeyEvent>
#include <QStringList>

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QTextEdit *textEdit;
    QStringList commandHistory;
    int historyIndex;
    QString currentCommand;

    void executeCommand(const QString &command) const;
};

#endif // MAINWINDOW_H
