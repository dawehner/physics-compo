#include <map>

/**
 * Stores some things statically to be reused somewhere else.
 * This is basically some kind of global key value store.
 *
 * @todo
 * This method could be written as template.
 */
double static_cache(int key, int value) {
  static map<int, int> cache;

  if (value == 0) {
    return cache[key];
  }
  else {
    cache[key] = value;
    return value;
  }
}

