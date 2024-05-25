#include <iostream>
#include <sstream>

#include <QApplication>
#include <QDir>
#include <QDockWidget>
#include <QFileSystemModel>
#include <QListView>
#include <QMainWindow>
#include <QPushButton>
#include <QStandardPaths>
#include <QToolBar>

#include "helpers.h"
#include "directory_picker/DirectoryPickerWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    examine("HOME",
            QDir::homePath());
    examine("minecraft server",
            QDir::homePath().append("/minecraft_server_forge_1_20_1"));
    examine("invalid path",
            QDir::homePath().append("/does-not-exist"));
    examine("Developer",
            QDir::homePath().append("/Developer"));
    examine("downloads",
            QStandardPaths::standardLocations(QStandardPaths::DownloadLocation));
    examine("documents",
            QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation));
    examine("app local data",
            QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation));

    auto button = new QPushButton("btn1");

    auto toolbar = new QToolBar();
    toolbar->setFloatable(false);
    toolbar->setMovable(false);
    toolbar->addWidget(button);

    QMainWindow mainWindow = QMainWindow();
    mainWindow.resize(800, 600);

    auto directoryPicker = new directory_picker::DirectoryPickerWidget();

    mainWindow.setCentralWidget(directoryPicker->getWidget());

    // TODO: and what?
    mainWindow.addToolBar(toolbar);
    // TODO: how to do translations for both PL and EN?
    mainWindow.setWindowTitle(QApplication::translate("window", "Qt File Explorer"));
    mainWindow.show();

    return QApplication::exec();
}
