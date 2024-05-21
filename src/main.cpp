#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QDir>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto homePath = QDir::homePath();
    std::cout << "home: '" << homePath.toStdString() << "'" << std::endl;

    QDir homeDir(homePath);
    homeDir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    std::cout << "home dir:" << std::endl;
    for (const auto &fileInfo: homeDir.entryInfoList()) {
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
