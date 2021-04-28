#include "InstModel/InstModel.h"

namespace spatial {

InstModel::InstModel(TokenWrapper *TW) { this->TW = TW; }
InstModel::~InstModel(){};
TokenWrapper* InstModel::getTokenWrapper() { return this->TW; }

} // namespace spatial
