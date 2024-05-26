#ifndef QT_FILE_EXPLORER_SRC_HELPERS_H
#define QT_FILE_EXPLORER_SRC_HELPERS_H

#include <sstream>

#include <QString>
#include <QStringList>

namespace qt_file_explorer::helpers {

void examine(const std::string& label, const QStringList& paths);

void examine(const std::string& label, const QString& path);

} // namespace qt_file_explorer::helpers

#endif //QT_FILE_EXPLORER_SRC_HELPERS_H
