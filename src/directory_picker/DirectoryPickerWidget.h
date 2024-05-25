#ifndef LEARNING__QT_FILE_EXPLORER_DIRECTORYPICKERWIDGET_H
#define LEARNING__QT_FILE_EXPLORER_DIRECTORYPICKERWIDGET_H

#import <QTreeView>

namespace directory_picker {

    class DirectoryPickerWidget : public QTreeView {

    public:
        DirectoryPickerWidget();

        void setCurrentPath(QString &path);

    private:
        QString DEFAULT_PATH = QDir::homePath();
        QFileSystemModel *model;
    };

}

#endif //LEARNING__QT_FILE_EXPLORER_DIRECTORYPICKERWIDGET_H
