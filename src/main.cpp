#include <iostream>
#include <sstream>

#include <QApplication>
#include <QDir>
#include <QPushButton>
#include <QStandardPaths>

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

    QPushButton button("(see the standard output)", nullptr);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
