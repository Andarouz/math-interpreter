#include "mainwindow.h"
#include <QVBoxLayout>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), historyIndex(-1) {

    // Настройка текстового поля
    textEdit = new QTextEdit(this);
    textEdit->setReadOnly(false);
    textEdit->setStyleSheet("background-color: black; color: white; font-family: monospace; font-size: 12px;");
    textEdit->setLineWrapMode(QTextEdit::NoWrap);

    setCentralWidget(textEdit);
    textEdit->setFocus();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        currentCommand = textEdit->toPlainText().split('\n').last(); // Получаем последнюю строку
        commandHistory.append(currentCommand); // Сохраняем в историю
        historyIndex = commandHistory.size(); // Обновляем индекс истории

        executeCommand(currentCommand); // Выполняем команду

        textEdit->append(""); // Создаем новую строку для следующей команды
        textEdit->moveCursor(QTextCursor::End); // Перемещаем курсор в конец
    } else if (event->key() == Qt::Key_Up) {
        if (historyIndex > 0) {
            historyIndex--;
            QStringList lines = textEdit->toPlainText().split('\n');
            lines.removeLast(); // Удаляем последнюю строку
            textEdit->setPlainText(lines.join('\n') + "\n" + commandHistory[historyIndex]);
            textEdit->moveCursor(QTextCursor::End); // Перемещаем курсор в конец
        }
    } else if (event->key() == Qt::Key_Down) {
        if (historyIndex < commandHistory.size() - 1) {
            historyIndex++;
            QStringList lines = textEdit->toPlainText().split('\n');
            lines.removeLast(); // Удаляем последнюю строку
            textEdit->setPlainText(lines.join('\n') + "\n" + commandHistory[historyIndex]);
            textEdit->moveCursor(QTextCursor::End); // Перемещаем курсор в конец
        }
    } else {
        QMainWindow::keyPressEvent(event); // Обработка остальных клавиш
    }
}


void MainWindow::executeCommand(const QString &command) const {
    // Здесь нужно реализовать логику обработки команд
    // Например, можно просто выводить команду обратно
    textEdit->append("Executed: " + command);
}

