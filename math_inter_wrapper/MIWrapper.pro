# Имя проекта
TEMPLATE = app
TARGET = MIWRapper
CONFIG += c++20    # Установим стандарт C++20, измените на нужный при необходимости

# Включение модулей Qt
QT += quick qml core gui

# Включение необходимых директорий
SOURCES += \
    src/main.cpp \
    src/models/TerminalModel.cpp \
    src/viewmodels/TerminalViewModel.cpp

HEADERS += \
    src/models/TerminalModel.h \
    src/viewmodels/TerminalViewModel.h

# Ресурсы и QML файлы
RESOURCES += \
    views/TerminalView.qml \
    views/TerminalStyle.qml

# Включение QML-папки в проект
QML_IMPORT_PATH = $$PWD/views
QML_DESIGNER_IMPORT_PATH = $$PWD/views

# Указание дополнительных флагов
CONFIG += console    # Включает вывод в консоль (удобно для отладки)
CONFIG += qml_debug  # Включает QML-отладчик для более легкой отладки UI

# Папка для вывода скомпилированных файлов
DESTDIR = bin

# Включение файловых путей для Intellisense (если используется в Qt Creator)
INCLUDEPATH += src \
               src/viewmodels \
               src/models

# Оптимизация настроек компилятора и линкера
QMAKE_CXXFLAGS_RELEASE += -O2 -Wall -Wextra
QMAKE_LFLAGS_RELEASE += -s

