# InfiniCore

[![Doc](https://img.shields.io/badge/Document-ready-blue)](https://github.com/InfiniTensor/InfiniCore-Documentation)
[![CI](https://github.com/InfiniTensor/InfiniCore/actions/workflows/build.yml/badge.svg?branch=main)](https://github.com/InfiniTensor/InfiniCore/actions)
[![license](https://img.shields.io/github/license/InfiniTensor/InfiniCore)](https://mit-license.org/)
![GitHub repo size](https://img.shields.io/github/repo-size/InfiniTensor/InfiniCore)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/InfiniTensor/InfiniCore)

[![GitHub Issues](https://img.shields.io/github/issues/InfiniTensor/InfiniCore)](https://github.com/InfiniTensor/InfiniCore/issues)
[![GitHub Pull Requests](https://img.shields.io/github/issues-pr/InfiniTensor/InfiniCore)](https://github.com/InfiniTensor/InfiniCore/pulls)
![GitHub contributors](https://img.shields.io/github/contributors/InfiniTensor/InfiniCore)
![GitHub commit activity](https://img.shields.io/github/commit-activity/m/InfiniTensor/InfiniCore)

InfiniCore 是一个跨平台统一编程工具集，为不同芯片平台的功能（包括计算、运行时、通信等）提供统一 C 语言接口。目前支持的硬件和后端包括：

- CPU；
- CUDA
  - 英伟达 GPU；
  - 摩尔线程 GPU；
  - 天数智芯 GPU；
  - 沐曦 GPU；
  - 曙光 DCU；
- 华为昇腾 NPU；
- 寒武纪 MLU；
- 昆仑芯 XPU；

API 定义以及使用方式详见 [`InfiniCore文档`](https://github.com/InfiniTensor/InfiniCore-Documentation)。

## 配置和使用

### 一键安装

在 `script/` 目录中提供了 `install.py` 安装脚本。使用方式如下：

```shell
cd InfiniCore

python scripts/install.py [XMAKE_CONFIG_FLAGS]
```

参数 `XMAKE_CONFIG_FLAGS` 是 xmake 构建配置，可配置下列可选项：

| 选项                     | 功能                              | 默认值
|--------------------------|-----------------------------------|:-:
| `--omp=[y\|n]`           | 是否使用 OpenMP                   | y
| `--cpu=[y\|n]`           | 是否编译 CPU 接口实现             | y
| `--nv-gpu=[y\|n]`        | 是否编译英伟达 GPU 接口实现       | n
| `--ascend-npu=[y\|n]`    | 是否编译昇腾 NPU 接口实现         | n
| `--cambricon-mlu=[y\|n]` | 是否编译寒武纪 MLU 接口实现       | n
| `--metax-gpu=[y\|n]`     | 是否编译沐曦 GPU 接口实现         | n
| `--moore-gpu=[y\|n]`     | 是否编译摩尔线程 GPU 接口实现     | n
| `--iluvatar-gpu=[y\|n]`  | 是否编译沐曦 GPU 接口实现         | n
| `--sugon-dcu=[y\|n]`     | 是否编译曙光 DCU 接口实现         | n
| `--kunlun-xpu=[y\|n]`    | 是否编译昆仑 XPU 接口实现         | n
| `--ccl=[y\|n]`           | 是否编译 InfiniCCL 通信库接口实现 | n

### 手动安装

1. 项目配置

   windows系统上，建议使用`xmake v2.8.9`编译项目。
   - 查看当前配置

     ```shell
     xmake f -v
     ```

   - 配置 CPU（默认配置）

     ```shell
     xmake f -cv
     ```

   - 配置加速卡

     ```shell
     # 英伟达
     # 可以指定 CUDA 路径， 一般环境变量为 `CUDA_HOME` 或者 `CUDA_ROOT`
     # window系统：--cuda="%CUDA_HOME%"
     # linux系统：--cuda=$CUDA_HOME
     xmake f --nv-gpu=true --cuda=$CUDA_HOME -cv

     # 寒武纪
     xmake f --cambricon-mlu=true -cv

     # 华为昇腾
     xmake f --ascend-npu=true -cv
     ```

2. 编译安装

   默认安装路径为 `$HOME/.infini`。

   ```shell
   xmake build && xmake install
   ```

3. 设置环境变量

   按输出提示设置 `INFINI_ROOT` 和 `LD_LIBRARY_PATH` 环境变量。

### 运行测试

#### 运行Python算子测试

```shell
python test/infiniop/[operator].py [--cpu | --nvidia | --cambricon | --ascend]
```

#### 一键运行所有Python算子测试

```shell
python scripts/python_test.py [--cpu | --nvidia | --cambricon | --ascend]
```

#### 算子测试框架

详见 `test/infiniop-test` 目录

#### 通信库（InfiniCCL）测试

编译（需要先安装InfiniCCL）：

```shell
xmake build infiniccl-test
```

在英伟达平台运行测试（会自动使用所有可见的卡）：

```shell
infiniccl-test --nvidia
```

## 如何开源贡献

见 [`InfiniCore开发者手册`](DEV.md)。
