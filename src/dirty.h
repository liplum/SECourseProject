//
// Created by Liplum on 6/12/23.
//

#ifndef PRODMANAGESYS_DIRTY_H
#define PRODMANAGESYS_DIRTY_H

#include <concepts>

template<typename T>
concept TMarkDirty = requires(T t) {
  { t.clearDirty() } -> std::convertible_to<bool>;
  { t.isDirty() } -> std::convertible_to<bool>;
};

class DirtyMarkMixin {
protected:
  /**
  * whether the object was changed.
  */
  bool dirty{false};

  void markDirty();

public:
  /**
 * Clear the dirty mark.
 * @return whether is dirty.
 */
  bool clearDirty();

  bool isDirty();
};

#endif //PRODMANAGESYS_DIRTY_H
