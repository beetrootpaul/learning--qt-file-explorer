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
#include <QTreeView>

// TODO: extract to a separate file
void examine(const std::string &label, const QString &path) {

    auto normalizedPath = QDir::toNativeSeparators(path);

    std::cout << std::endl;

    std::cout << "### " << label << std::endl;

    std::cout << std::endl;

    std::cout << "path: " << normalizedPath.toStdString() << std::endl;

    std::cout << std::endl;

    QDir dir(normalizedPath);
    std::cout << "does dir exist? " << (dir.exists() ? "yes" : "!!! NO !!!") << std::endl;

    std::cout << std::endl;

    // NOTE: This one does print only if e.g. IDE got permissions to access those folders,
    //       granted by the user.
    std::cout << "entries: " << std::endl;
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDot);
    for (const auto &fileInfo: dir.entryInfoList()) {
        std::cout << "- " << fileInfo.fileName().toStdString();
        if (fileInfo.isDir()) {
            std::cout << QDir::separator().toLatin1();
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

// TODO: extract to a separate file
void examine(const std::string &label, QStringList paths) {
    unsigned i = 1;
    for (const auto &path: paths) {
        std::stringstream ss;
        ss << "(" << i << "/" << paths.count() << ") " << label;
        examine(ss.str(), path);
        i += 1;
    }
}


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


    auto downloadLocations = QStandardPaths::standardLocations(QStandardPaths::DownloadLocation);
    if (downloadLocations.count() < 1) {
        // TODO: make it nicer
        throw;
    }

    auto path = downloadLocations.first();

    auto model = new QFileSystemModel();
    model->setRootPath(path);
    auto tree = new QTreeView();
    tree->setModel(model);
    tree->setRootIndex(model->index(path));
    auto list = new QListView();
    list->setModel(model);
    list->setRootIndex(model->index(path));

    auto button = new QPushButton("btn1");

    auto toolbar = new QToolBar();
    toolbar->setFloatable(false);
    toolbar->setMovable(false);
    toolbar->addWidget(button);

    QMainWindow mainWindow = QMainWindow();
    mainWindow.resize(800, 600);
    mainWindow.setCentralWidget(tree);
//    mainWindow.setCentralWidget(list);
    
    // TODO: and what?
    mainWindow.addToolBar(toolbar);
    // TODO: how to do translations for both PL and EN?
    mainWindow.setWindowTitle(QApplication::translate("window", "Qt File Explorer"));
    mainWindow.show();

    return QApplication::exec();
}
