#include <QFileSystemModel>
#include <QStandardPaths>
#include <QTreeView>

#include "DirectoryPickerWidget.h"

namespace directory_picker {

    DirectoryPickerWidget::DirectoryPickerWidget() {
        auto downloadLocations =
                QStandardPaths::standardLocations(QStandardPaths::DownloadLocation);
        if (downloadLocations.count() < 1) {
            // TODO: make it nicer
            throw;
        }
        auto path = downloadLocations.first();

        auto model = new QFileSystemModel();
        model->setRootPath(path);

//        auto view = new QListView();
        auto view = new QTreeView();
        view->setModel(model);
        view->setRootIndex(model->index(path));

        this->widget = view;
    }

    QWidget *DirectoryPickerWidget::getWidget() {
        return this->widget;
    }


}