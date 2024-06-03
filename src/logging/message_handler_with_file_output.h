#ifndef QT_FILE_EXPLORER_LOGGING_MESSAGE_HANDLER_WITH_FILE_OUTPUT_H
#define QT_FILE_EXPLORER_LOGGING_MESSAGE_HANDLER_WITH_FILE_OUTPUT_H

#include <iostream>

#include <QApplication>
#include <QFile>

namespace qt_file_explorer::logging::message_handler_with_file_output {

QString _logFilePath;

QtMessageHandler _originalHandler = nullptr;

bool _installedSuccessfully = false;

void _handler(QtMsgType type, const QMessageLogContext& context,
              const QString& msg) {
  if (_installedSuccessfully) {
    QFile logFile(_logFilePath);
    if (logFile.open(QIODeviceBase::OpenModeFlag::Append)) {
      QTextStream out(&logFile);
      out << qFormatLogMessage(type, context, msg) << "\n";
      logFile.close();
    }
  }

  if (_originalHandler) {
    _originalHandler(type, context, msg);
  }
}

void install() {
  const QString logDirName = "logs";

  QDir currentDir(".");
  if (!currentDir.exists(logDirName)) {
    qWarning() << "[logging] Log dir does not exist. Creating it:"
               << currentDir.absoluteFilePath(logDirName);
    currentDir.mkdir(logDirName);
  }

  QFileInfo logDirInfo(logDirName);
  if (!logDirInfo.isDir()) {
    qWarning() << "[logging] Log dir is not a dir:"
               << logDirInfo.absoluteFilePath();
    return;
  }
  if (!logDirInfo.isWritable()) {
    qWarning() << "[logging] Log dir is not writable:"
               << logDirInfo.absoluteFilePath();
    return;
  }

  QDateTime now = QDateTime::currentDateTimeUtc();
  auto logFileName = QString("log_%1.txt").arg(
      now.toString(QLatin1String("yyyyMMdd_hhmmss")));
  _logFilePath = logDirInfo.absoluteFilePath() + "/" + logFileName;
  QFile logFile(logDirInfo.absoluteFilePath() + "/" + logFileName);
  if (logFile.exists()) {
    qWarning() << "[logging] Log file already exist:" << logFile.fileName();
    return;
  }

  bool couldOpen = logFile.open(QIODeviceBase::OpenModeFlag::Append);
  if (!couldOpen) {
    qWarning() << "[logging] Log file couldn't be open:"
               << logFile.fileName();
    return;
  }

  qInfo() << "[logging] Will log to file:" << logFile.fileName();

  _originalHandler = qInstallMessageHandler(_handler);

  _installedSuccessfully = true;
}

} // namespace qt_file_explorer::logging::message_handler_with_file_output

#endif //QT_FILE_EXPLORER_LOGGING_MESSAGE_HANDLER_WITH_FILE_OUTPUT_H
