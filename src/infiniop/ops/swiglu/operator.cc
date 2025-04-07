#include "../../operator.h"
#include "../../handle.h"
#include "infiniop/ops/swiglu.h"

#ifdef ENABLE_CPU_API
#include "cpu/swiglu_cpu.h"
#endif
#ifdef ENABLE_CUDA_API
#include "cuda/swiglu_cuda.cuh"
#endif

__C infiniStatus_t infiniopCreateSwiGLUDescriptor(
    infiniopHandle_t handle,
    infiniopSwiGLUDescriptor_t *desc_ptr,
    infiniopTensorDescriptor_t c_desc,
    infiniopTensorDescriptor_t a_desc,
    infiniopTensorDescriptor_t b_desc) {

#define CREATE(CASE, NAMESPACE)                                               \
    case CASE:                                                                \
        return op::swiglu::NAMESPACE::Descriptor::create(                     \
            handle,                                                           \
            reinterpret_cast<op::swiglu::NAMESPACE::Descriptor **>(desc_ptr), \
            c_desc,                                                           \
            {a_desc,                                                          \
             b_desc})

    switch (handle->device) {

#ifdef ENABLE_CPU_API
        CREATE(INFINI_DEVICE_CPU, cpu);
#endif
#ifdef ENABLE_CUDA_API
        CREATE(INFINI_DEVICE_NVIDIA, cuda);
#endif
#ifdef ENABLE_CAMBRICON_MLU
    case DevCambriconMlu: {
        return bangCreateSwiGLUDescriptor((BangHandle_t)handle,
                                          (SwiGLUBangDescriptor_t *)desc_ptr,
                                          c_desc, a_desc, b_desc);
    }
#endif
#ifdef ENABLE_ASCEND_NPU
    case DevAscendNpu:
        return ascendCreateSwiGLUDescriptor(
            (AscendHandle_t)handle, (SwiGLUAscendDescriptor_t *)desc_ptr,
            c_desc, a_desc, b_desc);
#endif
#ifdef ENABLE_METAX_GPU
    case DevMetaxGpu: {
        return macaCreateSwiGLUDescriptor((MacaHandle_t)handle,
                                          (SwiGLUMacaDescriptor_t *)desc_ptr,
                                          c_desc, a_desc, b_desc);
    }
#endif
#ifdef ENABLE_MTHREADS_GPU
    case DevMthreadsGpu:
        return musaCreateSwiGLUDescriptor(
            handle, (SwiGLUMusaDescriptor_t *)desc_ptr, c_desc, a_desc, b_desc);
#endif

    default:
        return INFINI_STATUS_DEVICE_TYPE_NOT_SUPPORTED;
    }

#undef CREATE
}

__C infiniStatus_t infiniopSwiGLU(
    infiniopSwiGLUDescriptor_t desc,
    void *c,
    const void *a,
    const void *b,
    void *stream) {

#define CALCULATE(CASE, NAMESPACE)                                               \
    case CASE:                                                                   \
        return reinterpret_cast<const op::swiglu::NAMESPACE::Descriptor *>(desc) \
            ->calculate(c, {a, b}, stream)

    switch (desc->device_type) {

#ifdef ENABLE_CPU_API
        CALCULATE(INFINI_DEVICE_CPU, cpu);
#endif
#ifdef ENABLE_CUDA_API
        CALCULATE(INFINI_DEVICE_NVIDIA, cuda);
#endif
#ifdef ENABLE_CAMBRICON_MLU
    case DevCambriconMlu: {
        return bangSwiGLU((SwiGLUBangDescriptor_t)desc, c, a, b, stream);
    }
#endif
#ifdef ENABLE_ASCEND_NPU
    case DevAscendNpu:
        return ascendSwiGLU((SwiGLUAscendDescriptor_t)desc, c, a, b, stream);
#endif
#ifdef ENABLE_METAX_GPU
    case DevMetaxGpu:
        return macaSwiGLU((SwiGLUMacaDescriptor_t)desc, c, a, b, stream);
#endif
#ifdef ENABLE_MTHREADS_GPU
    case DevMthreadsGpu:
        return musaSwiGLU((SwiGLUMusaDescriptor_t)desc, c, a, b, stream);
#endif

    default:
        return INFINI_STATUS_DEVICE_TYPE_NOT_SUPPORTED;
    }

#undef CALCULATE
}

__C infiniStatus_t
infiniopDestroySwiGLUDescriptor(infiniopSwiGLUDescriptor_t desc) {

#define DELETE(CASE, NAMESPACE)                                                   \
    case CASE:                                                                    \
        delete reinterpret_cast<const op::swiglu::NAMESPACE::Descriptor *>(desc); \
        return INFINI_STATUS_SUCCESS;

    switch (desc->device_type) {

#ifdef ENABLE_CPU_API
        DELETE(INFINI_DEVICE_CPU, cpu);
#endif
#ifdef ENABLE_CUDA_API
        DELETE(INFINI_DEVICE_NVIDIA, cuda);
#endif
#ifdef ENABLE_CAMBRICON_MLU
    case DevCambriconMlu: {
        return bangDestroySwiGLUDescriptor((SwiGLUBangDescriptor_t)desc);
    }
#endif
#ifdef ENABLE_ASCEND_NPU
    case DevAscendNpu:
        return ascendDestroySwiGLUDescriptor((SwiGLUAscendDescriptor_t)desc);
#endif
#ifdef ENABLE_METAX_GPU
    case DevMetaxGpu:
        return macaDestroySwiGLUDescriptor((SwiGLUMacaDescriptor_t)desc);
#endif
#ifdef ENABLE_MTHREADS_GPU
    case DevMthreadsGpu:
        return musaDestroySwiGLUDescriptor((SwiGLUMusaDescriptor_t)desc);
#endif

    default:
        return INFINI_STATUS_DEVICE_TYPE_NOT_SUPPORTED;
    }

#undef DELETE
}
