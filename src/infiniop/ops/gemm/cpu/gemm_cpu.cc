#include "gemm_cpu.h"
#include "../../../devices/cpu/common_cpu.h"

namespace op::gemm::cpu {

Descriptor::~Descriptor() = default;

infiniStatus_t Descriptor::create(
    infiniopHandle_t handle_,
    Descriptor **desc_ptr,
    infiniopTensorDescriptor_t c_desc,
    infiniopTensorDescriptor_t a_desc,
    infiniopTensorDescriptor_t b_desc) {
    auto handle = reinterpret_cast<device::cpu::Handle *>(handle_);
    auto dtype = c_desc->dtype();

    if (dtype != INFINI_DTYPE_F16 && dtype != INFINI_DTYPE_F32) {
        return INFINI_STATUS_BAD_TENSOR_DTYPE;
    }

    infiniStatus_t status;
    auto info = MatmulInfo(c_desc, a_desc, b_desc, &status, MatrixLayout::COL_MAJOR);
    if (status != INFINI_STATUS_SUCCESS) {
        return status;
    }

    *desc_ptr = new Descriptor(
        dtype, info, 0,
        nullptr,
        handle->device, handle->device_id);
    return INFINI_STATUS_SUCCESS;
}

template <typename Tdata>
void calculate(
    const MatmulInfo &info,
    void *c,
    float beta,
    const void *a,
    const void *b,
    float alpha) {
    if (info.is_transed) {
        std::swap(a, b);
    }
#pragma omp parallel for collapse(3)
    for (int i = 0; i < static_cast<int>(info.batch); ++i) {
        for (int m_ = 0; m_ < static_cast<int>(info.m); ++m_) {
            for (int n_ = 0; n_ < static_cast<int>(info.n); ++n_) {
                auto c_ = reinterpret_cast<Tdata *>(c) + i * info.c_matrix.stride + m_ * info.c_matrix.row_stride + n_ * info.c_matrix.col_stride;
                float sum = 0;
                for (int k_ = 0; k_ < static_cast<int>(info.k); ++k_) {
                    auto a_ = reinterpret_cast<const Tdata *>(a) + i * info.a_matrix.stride + m_ * info.a_matrix.row_stride + k_ * info.a_matrix.col_stride;
                    auto b_ = reinterpret_cast<const Tdata *>(b) + i * info.b_matrix.stride + n_ * info.b_matrix.col_stride + k_ * info.b_matrix.row_stride;
                    if constexpr (std::is_same<Tdata, fp16_t>::value) {
                        sum += utils::cast<float>(*a_) * utils::cast<float>(*b_);
                    } else {
                        sum += *a_ * (*b_);
                    }
                }
                if constexpr (std::is_same<Tdata, fp16_t>::value) {
                    if (beta == 0) {
                        *c_ = utils::cast<fp16_t>(alpha * sum);
                    } else {
                        *c_ = utils::cast<fp16_t>(beta * utils::cast<float>(*c_) + alpha * sum);
                    }
                } else {
                    *c_ = beta * (*c_) + alpha * sum;
                }
            }
        }
    }
}

infiniStatus_t Descriptor::calculate(
    void *workspace,
    size_t workspace_size,
    void *c,
    float beta,
    const void *a,
    const void *b,
    float alpha,
    void *stream) const {

    switch (_dtype) {
    case INFINI_DTYPE_F16:
        cpu::calculate<fp16_t>(_info, c, beta, a, b, alpha);
        return INFINI_STATUS_SUCCESS;

    case INFINI_DTYPE_F32:
        cpu::calculate<float>(_info, c, beta, a, b, alpha);
        return INFINI_STATUS_SUCCESS;

    default:
        return INFINI_STATUS_BAD_TENSOR_DTYPE;
    }
}

} // namespace op::gemm::cpu
