#include <iostream>
#include <sstream>

#include <QDir>

#import "helpers.h"

void examine(const std::string &label, const QStringList &paths) {
    unsigned i = 1;
    for (const auto &path: paths) {
        std::stringstream ss;
        ss << "(" << i << "/" << paths.count() << ") " << label;
        examine(ss.str(), path);
        i += 1;
    }
}

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
