
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define DEFINE_DYNARRAY(name, type) \
  type *name; \
  size_t name ## _len; \
  size_t name ## _size;

#define RESIZE_DYNARRAY(name, desired_len) { \
  size_t orig_size = name ## _size;          \
  while((signed) name ## _size < ((signed) desired_len)) { \
    name ## _size *= 2; \
  } \
  /* don't bother shrinking for now.  when/if we do, we'll want to bake in \
   * some kind of hysteresis so that we don't shrink until we've been under \
   * for a while. */ \
  if(name ## _size != orig_size) \
    name = realloc(name, name ## _size * sizeof(*name)); \
  name ## _len = desired_len; \
}

#define INIT_DYNARRAY(name, initial_len, initial_size) \
  name ## _len = initial_len; \
  name ## _size = initial_size; \
  name = realloc(NULL, name ## _size * sizeof(*name))

#define FREE_DYNARRAY(name) \
  free(name);

#define DYNARRAY_GET_TOP(name) \
  (&name[name ## _len - 1])

