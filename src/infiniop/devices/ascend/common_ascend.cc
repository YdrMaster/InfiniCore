#include "common_ascend.h"

infiniStatus_t mallocWorkspace(void **workspaceAddr, size_t workspaceSize) {
    *workspaceAddr = nullptr;
    if (workspaceSize > 0) {
        CHECK_ACL(aclrtMalloc(workspaceAddr, workspaceSize,
                              ACL_MEM_MALLOC_HUGE_FIRST));
    }
    return INFINI_STATUS_SUCCESS;
}

infiniStatus_t freeWorkspace(void *workspaceAddr) {
    if (workspaceAddr != nullptr) {
        CHECK_ACL(aclrtFree(workspaceAddr));
    }
    return INFINI_STATUS_SUCCESS;
}

aclDataType toAclDataType(infiniDtype_t dt) {
    if (dt == INFINI_DTYPE_I8) {
        return aclDataType::ACL_INT8;
    } else if (dt == INFINI_DTYPE_I16) {
        return aclDataType::ACL_INT16;
    } else if (dt == INFINI_DTYPE_I32) {
        return aclDataType::ACL_INT32;
    } else if (dt == INFINI_DTYPE_I64) {
        return aclDataType::ACL_INT64;
    } else if (dt == INFINI_DTYPE_U8) {
        return aclDataType::ACL_UINT8;
    } else if (dt == INFINI_DTYPE_U16) {
        return aclDataType::ACL_UINT16;
    } else if (dt == INFINI_DTYPE_U32) {
        return aclDataType::ACL_UINT32;
    } else if (dt == INFINI_DTYPE_U64) {
        return aclDataType::ACL_UINT64;
    } else if (dt == INFINI_DTYPE_F16) {
        return aclDataType::ACL_FLOAT16;
    } else if (dt == INFINI_DTYPE_BF16) {
        return aclDataType::ACL_BF16;
    } else if (dt == INFINI_DTYPE_F32) {
        return aclDataType::ACL_FLOAT;
    } else if (dt == INFINI_DTYPE_F64) {
        return aclDataType::ACL_DOUBLE;
    } else {
        return aclDataType::ACL_DT_UNDEFINED;
    }
}

const char *dataTypeToString(aclDataType dtype) {
    switch (dtype) {
    case ACL_DT_UNDEFINED:
        return "ACL_DT_UNDEFINED";
    case ACL_FLOAT:
        return "ACL_FLOAT";
    case ACL_FLOAT16:
        return "ACL_FLOAT16";
    case ACL_INT8:
        return "ACL_INT8";
    case ACL_INT32:
        return "ACL_INT32";
    case ACL_UINT8:
        return "ACL_UINT8";
    case ACL_INT16:
        return "ACL_INT16";
    case ACL_UINT16:
        return "ACL_UINT16";
    case ACL_UINT32:
        return "ACL_UINT32";
    case ACL_INT64:
        return "ACL_INT64";
    case ACL_UINT64:
        return "ACL_UINT64";
    case ACL_DOUBLE:
        return "ACL_DOUBLE";
    case ACL_BOOL:
        return "ACL_BOOL";
    case ACL_STRING:
        return "ACL_STRING";
    case ACL_COMPLEX64:
        return "ACL_COMPLEX64";
    case ACL_COMPLEX128:
        return "ACL_COMPLEX128";
    case ACL_BF16:
        return "ACL_BF16";
    case ACL_INT4:
        return "ACL_INT4";
    case ACL_UINT1:
        return "ACL_UINT1";
    case ACL_COMPLEX32:
        return "ACL_COMPLEX32";
    default:
        return "UNKNOWN";
    }
}

const char *formatToString(aclFormat format) {
    switch (format) {
    case ACL_FORMAT_UNDEFINED:
        return "ACL_FORMAT_UNDEFINED";
    case ACL_FORMAT_NCHW:
        return "ACL_FORMAT_NCHW";
    case ACL_FORMAT_NHWC:
        return "ACL_FORMAT_NHWC";
    case ACL_FORMAT_ND:
        return "ACL_FORMAT_ND";
    case ACL_FORMAT_NC1HWC0:
        return "ACL_FORMAT_NC1HWC0";
    case ACL_FORMAT_FRACTAL_Z:
        return "ACL_FORMAT_FRACTAL_Z";
    case ACL_FORMAT_NC1HWC0_C04:
        return "ACL_FORMAT_NC1HWC0_C04";
    case ACL_FORMAT_HWCN:
        return "ACL_FORMAT_HWCN";
    case ACL_FORMAT_NDHWC:
        return "ACL_FORMAT_NDHWC";
    case ACL_FORMAT_FRACTAL_NZ:
        return "ACL_FORMAT_FRACTAL_NZ";
    case ACL_FORMAT_NCDHW:
        return "ACL_FORMAT_NCDHW";
    case ACL_FORMAT_NDC1HWC0:
        return "ACL_FORMAT_NDC1HWC0";
    case ACL_FRACTAL_Z_3D:
        return "ACL_FRACTAL_Z_3D";
    case ACL_FORMAT_NC:
        return "ACL_FORMAT_NC";
    case ACL_FORMAT_NCL:
        return "ACL_FORMAT_NCL";
    default:
        return "UNKNOWN";
    }
}
