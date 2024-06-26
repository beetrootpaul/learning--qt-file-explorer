#include "preview_dock_widget.h"

#include <QSharedPointer>

#include "file_name_preview_widget.h"
#include "image_preview_widget.h"
#include "json_preview_widget.h"
#include "markdown_preview_widget.h"
#include "text_preview_widget.h"

namespace qt_file_explorer::gui {

PreviewDockWidget::PreviewDockWidget() {
  setObjectName("PreviewDockWidget");
  qDebug() << "+" << this;
}

PreviewDockWidget::~PreviewDockWidget() {
  qDebug() << "~" << this;
}

void
PreviewDockWidget::init(app_state::AppState* appState) {
  appState_ = appState;

  setWindowTitle(tr("Preview"));

  // Remove context menu in order to remove the ability to close this dock or other app toolbars.
  setContextMenuPolicy(Qt::ContextMenuPolicy::PreventContextMenu);

  auto* imagePreview = new ImagePreviewWidget();
  imagePreview->init();
  orderedPreviewWidgets_.push_back(
      QSharedPointer<PreviewWidget>(imagePreview));

  auto* jsonPreviewWidget = new JsonPreviewWidget();
  jsonPreviewWidget->init();
  orderedPreviewWidgets_.push_back(
      QSharedPointer<PreviewWidget>(jsonPreviewWidget));

  auto* markdownPreviewWidget = new MarkdownPreviewWidget();
  markdownPreviewWidget->init();
  orderedPreviewWidgets_.push_back(
      QSharedPointer<PreviewWidget>(markdownPreviewWidget));

  auto* textPreviewWidget = new TextPreviewWidget();
  textPreviewWidget->init();
  orderedPreviewWidgets_.push_back(
      QSharedPointer<PreviewWidget>(textPreviewWidget));

  auto* fileNamePreview = new FileNamePreviewWidget();
  fileNamePreview->init();
  orderedPreviewWidgets_.push_back(
      QSharedPointer<PreviewWidget>(fileNamePreview));

  setWidget(imagePreview);

  connect(appState_, &app_state::AppState::signalSelectedPathChanged, this,
          &PreviewDockWidget::slotUpdatePreview);
}

void PreviewDockWidget::closeEvent(QCloseEvent* event) {
  if (appState_->isPreviewVisible()) {
    appState_->togglePreviewVisible();
  }
}

void PreviewDockWidget::slotUpdatePreview() {
  auto path = appState_->selectedPath();

  auto chosenPreviewWidget = QSharedPointer<PreviewWidget>(nullptr);
  for (const auto& pw: orderedPreviewWidgets_) {
    if (!chosenPreviewWidget && pw->canPreview(path)) {
      chosenPreviewWidget = pw;
    } else {
      pw->clear();
    }
  }

  setWidget(chosenPreviewWidget->asQWidget());

  chosenPreviewWidget->preview(path);
}

} // namespace qt_file_explorer::gui
