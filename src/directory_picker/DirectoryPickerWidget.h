#ifndef LEARNING__QT_FILE_EXPLORER_DIRECTORYPICKERWIDGET_H
#define LEARNING__QT_FILE_EXPLORER_DIRECTORYPICKERWIDGET_H

#import <QWidget>

namespace directory_picker {

    class DirectoryPickerWidget : public QWidget {

    public:
        DirectoryPickerWidget();

        // TODO: make use of DirectoryPickerWidget being QWidget instead
        QWidget *getWidget();

    private:
        QWidget *widget;

    };

}

#endif //LEARNING__QT_FILE_EXPLORER_DIRECTORYPICKERWIDGET_H
