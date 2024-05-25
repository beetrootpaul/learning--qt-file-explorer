#include <QFileSystemModel>
#include <QStandardPaths>

#include "DirectoryPickerWidget.h"

namespace directory_picker {

    DirectoryPickerWidget::DirectoryPickerWidget() {
        model = new QFileSystemModel();
        QTreeView::setModel(model);
        setCurrentPath(DEFAULT_PATH);
    }

    void DirectoryPickerWidget::setCurrentPath(QString &path) {
        model->setRootPath(path);
        QTreeView::setRootIndex(model->index(path));
    }

}