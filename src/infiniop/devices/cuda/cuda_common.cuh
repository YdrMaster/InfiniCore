#ifndef __INFINIOP_CUDA_COMMON_CUH__
#define __INFINIOP_CUDA_COMMON_CUH__

#include "../../reduce/cuda/reduce.cuh"
#include "cuda_handle.cuh"
#include "infinicore.h"

#ifdef ENABLE_SUGON_CUDA_API
#define INFINIOP_CUDA_KERNEL __launch_bounds__(512) __global__ void
#else
#define INFINIOP_CUDA_KERNEL __global__ void
#endif

// Posible maximum number of threads per block for CUDA architectures
// Used for picking correct kernel launch configuration
#define CUDA_BLOCK_SIZE_1024 1024
#define CUDA_BLOCK_SIZE_512 512

namespace device::cuda {

cudnnDataType_t getCudnnDtype(infiniDtype_t dt);

// return the memory offset of original tensor, given the flattened index of broadcasted tensor
__forceinline__ __device__ __host__ size_t
indexToReducedOffset(
    size_t flat_index,
    size_t ndim,
    const ptrdiff_t *broadcasted_strides,
    const ptrdiff_t *target_strides) {
    size_t res = 0;
    for (size_t i = 0; i < ndim; ++i) {
        res += flat_index / broadcasted_strides[i] * target_strides[i];
        flat_index %= broadcasted_strides[i];
    }
    return res;
}

// get the memory offset of the given element in a tensor given its flat index
__forceinline__ __device__ __host__ size_t
indexToOffset(
    size_t flat_index,
    size_t ndim,
    const size_t *shape,
    const ptrdiff_t *strides) {
    size_t res = 0;
    for (size_t i = ndim; i-- > 0;) {
        res += (flat_index % shape[i]) * strides[i];
        flat_index /= shape[i];
    }
    return res;
}

} // namespace device::cuda

#endif // __INFINIOP_CUDA_COMMON_CUH__
