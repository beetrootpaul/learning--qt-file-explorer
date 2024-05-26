#ifndef QT_FILE_EXPLORER_SRC_MODEL_H
#define QT_FILE_EXPLORER_SRC_MODEL_H

#include <QString>

#include "model/dir_listing_view_type.h"

namespace qt_file_explorer::model {

class Model {

public:
  QString currentPath();
  
  DirListingViewType currentDirListingViewType();
  void setDirListingViewType(DirListingViewType viewType);

private:
  DirListingViewType dir_listing_view_type_ = DirListingViewType::List;

};

} // namespace qt_file_explorer::model

#endif //QT_FILE_EXPLORER_SRC_MODEL_H
