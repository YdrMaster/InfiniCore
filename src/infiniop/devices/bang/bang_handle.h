#ifndef BANG_HANDLE_H
#define BANG_HANDLE_H

#include "../../handle.h"

struct InfiniopBangHandle;
typedef struct InfiniopBangHandle *infiniopBangHandle_t;

infiniStatus_t createBangHandle(infiniopBangHandle_t *handle_ptr);
infiniStatus_t destroyBangHandle(infiniopBangHandle_t handle);

#endif
