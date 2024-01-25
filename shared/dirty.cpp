//
// Created by Liplum on 6/12/23.
//

#include "dirty.h"

void DirtyMarkMixin::markDirty() {
  dirty = true;
}

bool DirtyMarkMixin::clearDirty() {
  bool isDirty = dirty;
  dirty = false;
  return isDirty;
}

bool DirtyMarkMixin::isDirty() {
  return dirty;
}