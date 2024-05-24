#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QStandardPaths>
#include <QDir>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto homePath = QDir::homePath();

    std::cout << "home: '" << homePath.toStdString() << "'" << std::endl;


    QDir homeDir(homePath);
    std::cout << "path = " << homePath.toStdString() << std::endl;
    std::cout << "does exist ??? " << homeDir.exists() << std::endl;


    auto ap = QDir::homePath().append("/minecraft_server_forge_1_20_1");
    std::cout << "path = " << ap.toStdString() << std::endl;
    QDir ad(ap);
    std::cout << "does exist ??? " << ad.exists() << std::endl;

    auto bp = QDir::homePath().append("/minecraft_server_forge_1_20_");
    std::cout << "path = " << bp.toStdString() << std::endl;
    QDir bd(bp);
    std::cout << "does exist ??? " << bd.exists() << std::endl;

    for (const auto &stdLoc: QStandardPaths::standardLocations(QStandardPaths::DownloadLocation)) {
        std::cout << "STD DOWNLOADS LOCATION = " << stdLoc.toStdString() << std::endl;
    }

    auto downloadsPath = QDir::homePath().append("/Downloads");
    std::cout << "path = " << downloadsPath.toStdString() << std::endl;
    QDir downloadsDir(downloadsPath);
    std::cout << "does exist ??? " << downloadsDir.exists() << std::endl;

    // TODO: HOW TO "/" in an idiomatic way?
    auto developerPath = QDir::homePath().append("/Developer");
    std::cout << "path = " << developerPath.toStdString() << std::endl;
    QDir developerDir(developerPath);
    std::cout << "does exist ??? " << developerDir.exists() << std::endl;


    homeDir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    std::cout << std::endl << "home dir:" << std::endl;
    for (const auto &fileInfo: homeDir.entryInfoList()) {
        if (fileInfo.isDir()) {
            std::cout << "- ./" << fileInfo.fileName().toStdString() << "/" << std::endl;
        } else {
            std::cout << "- ./" << fileInfo.fileName().toStdString() << std::endl;
        }
    }

    ad.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    std::cout << std::endl << "a dir:" << std::endl;
    for (const auto &fileInfo: ad.entryInfoList()) {
        if (fileInfo.isDir()) {
            std::cout << "- ./" << fileInfo.fileName().toStdString() << "/" << std::endl;
        } else {
            std::cout << "- ./" << fileInfo.fileName().toStdString() << std::endl;
        }
    }

    bd.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    std::cout << std::endl << "b dir:" << std::endl;
    for (const auto &fileInfo: bd.entryInfoList()) {
        if (fileInfo.isDir()) {
            std::cout << "- ./" << fileInfo.fileName().toStdString() << "/" << std::endl;
        } else {
            std::cout << "- ./" << fileInfo.fileName().toStdString() << std::endl;
        }
    }

    downloadsDir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    std::cout << std::endl << "DOWNLOADS dir:" << std::endl;
    for (const auto &fileInfo: downloadsDir.entryInfoList()) {
        if (fileInfo.isDir()) {
            std::cout << "- ./" << fileInfo.fileName().toStdString() << "/" << std::endl;
        } else {
            std::cout << "- ./" << fileInfo.fileName().toStdString() << std::endl;
        }
    }

    developerDir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    std::cout << std::endl << "DEVELOPER dir:" << std::endl;
    for (const auto &fileInfo: developerDir.entryInfoList()) {
        if (fileInfo.isDir()) {
            std::cout << "- ./" << fileInfo.fileName().toStdString() << "/" << std::endl;
        } else {
            std::cout << "- ./" << fileInfo.fileName().toStdString() << std::endl;
        }
    }


    QPushButton button("(see the standard output)", nullptr);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
