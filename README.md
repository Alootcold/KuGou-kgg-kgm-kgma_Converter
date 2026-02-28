# KuGouConverter - 酷狗音乐格式转换器

<p align="center">
  <img src="resources/icons/app.png" alt="KuGouConverter Logo" width="128" height="128"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Version-1.0.0-blue.svg" alt="Version"/>
  <img src="https://img.shields.io/badge/Qt-6.10+-green.svg" alt="Qt Version"/>
  <img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="License"/>
</p>

## 📖 项目简介

KuGouConverter（酷狗音乐格式转换器）是一款功能强大的桌面应用程序，专门用于解密和转换酷狗音乐平台的加密音频文件。

本软件基于 Qt 6.x 框架开发，采用原生 Windows 桌面体验，界面简洁美观，支持暗黑主题，让您轻松将加密的酷狗音乐转换为通用的 MP3、FLAC 等格式。

## ✨ 主要特性

### 🔓 格式支持
- **KGM** - 酷狗音乐早期加密格式
- **KGMA** - 酷狗音乐高清加密格式
- **VPR** - 酷狗音乐VIP加密格式
- **输出格式** - FLAC 无损 / MP3 有损

### 🎨 用户界面
- 全新暗黑主题 UI 设计
- 酷狗标志性蓝色主题配色
- 拖拽文件直接添加
- 实时转换进度显示

### 🛠️ 技术特点
- 基于 Qt 6.x 框架
- 多线程后台转换
- 完整的错误处理机制

## 📋 系统要求

| 项目 | 要求 |
|------|------|
| 操作系统 | Windows 10 及以上 |
| 内存 | 4 GB 及以上 |
| 磁盘空间 | 100 MB |

## 🚀 快速开始

### 下载安装

1. 从 [Releases](https://github.com/Alootcold/KuGou-kgg-kgm-kgma_Converter/releases) 下载最新版本
2. 运行安装程序 `KuGouConverter_Setup_v1.0.0.exe`
3. 按照安装向导完成安装

### 从源码构建

```bash
# 克隆项目
git clone https://github.com/your-repo/KuGouConverter.git

# 进入项目目录
cd KuGouConverter/KuGouConverter

# 使用 Qt Creator 打开 .pro 文件
# 选择 Release 模式构建
```

### 部署 Qt 运行时库

如果需要手动部署，运行以下命令：

```cmd
cd release
"C:\Qt\6.10.2\msvc2022_64\bin\windeployqt.exe" --release KuGouConverter.exe
```

## 💡 使用教程

### 步骤 1：添加文件
- 点击「+ 添加文件」按钮选择需要转换的文件
- 或直接将文件拖拽到窗口中

### 步骤 2：设置输出
- 选择输出格式（FLAC 或 MP3）
- 选择输出目录

### 步骤 3：开始转换
- 点击「开始转换」按钮
- 等待转换完成

### 步骤 4：播放音乐
- 在输出目录中找到转换后的文件
- 使用任意播放器即可播放

## 📂 项目结构

```
KuGouConverter/
├── src/
│   ├── main.cpp                 # 程序入口
│   ├── mainwindow.cpp           # 主窗口
│   ├── decrypt/                 # 解密模块
│   │   ├── kgm_decrypt.cpp     # KGM/KGMA/VPR 解密
│   │   └── kgm_mask_table.cpp  # Mask 表
│   ├── ui/                      # UI 模块
│   │   ├── filewidget.cpp      # 文件列表组件
│   │   └── convertthread.cpp   # 转换线程
│   └── ...
├── resources/                    # 资源文件
│   ├── icons/                   # 应用图标
│   └── qss/                     # 样式文件
├── KuGouConverter.pro          # 项目文件
└── KuGouConverter.iss          # Inno Setup 安装脚本
```

## 🤝 贡献指南

欢迎提交 Issue 和 Pull Request！

## 📄 许可证

本项目基于 MIT 许可证开源。

---

<p align="center">Made with ❤️ for music lovers</p>
