#ifndef QT_FILE_EXPLORER_WIDGETS_MONOSPACE_FONT_H
#define QT_FILE_EXPLORER_WIDGETS_MONOSPACE_FONT_H

#include <QFont>
#include <QWidget>

namespace qt_file_explorer::gui {

inline void applyMonospaceFontOn(QWidget* widget) {
  // NOTE: Even if surprising, I managed to get the most consistent nicely looking
  // results when doing as below: creating first font, setting its hint, then
  // creating a second one based on `defaultFamily()` from that first one.
  // Using just one font instance seemed to not work as expected, even with
  // a `QFont("")` constructor. On the other hand: using `QFont("Monospace")` was
  // seemingly OK, but with a risk that it worked only due to a given machine
  // having "Monospace" font family available.
  QFont font;
  font.setStyleHint(QFont::Monospace);
  font = QFont(font.defaultFamily());
  widget->setFont(font);
}

} // namespace qt_file_explorer::gui

#endif //QT_FILE_EXPLORER_WIDGETS_MONOSPACE_FONT_H
