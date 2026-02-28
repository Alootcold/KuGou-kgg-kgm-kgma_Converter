#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui/filewidget.h"
#include "ui/convertthread.h"
#include "ui/stylesheet.h"
#include "decrypt/kgm_decrypt.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QFileInfo>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_fileWidget(nullptr)
    , m_convertThread(nullptr)
    , m_outputFormat("flac")
{
    setupUI();
    setupConnections();

    m_outputDir = getDefaultOutputDir();
    ui->outputDirLineEdit->setText(m_outputDir);
}

MainWindow::~MainWindow()
{
    if (m_convertThread) {
        m_convertThread->cancel();
        m_convertThread->wait();
        delete m_convertThread;
    }
    delete ui;
}

void MainWindow::setupUI()
{
    ui->setupUi(this);

    setWindowTitle("酷狗音乐格式转换器");
    setMinimumSize(700, 500);

    // 文件列表组件
    m_fileWidget = new FileWidget(this);
    // 将FileWidget添加到fileGroup中替换占位符
    QVBoxLayout* fileLayout = qobject_cast<QVBoxLayout*>(ui->fileGroup->layout());
    if (fileLayout) {
        // 移除占位符，替换为FileWidget
        fileLayout->removeWidget(ui->fileWidgetPlaceholder);
        delete ui->fileWidgetPlaceholder;
        fileLayout->insertWidget(0, m_fileWidget);
    }

    // 设置格式下拉框
    ui->formatComboBox->addItem("FLAC (无损)", "flac");
    ui->formatComboBox->addItem("MP3", "mp3");
    ui->formatComboBox->setCurrentIndex(0);

    // 初始化进度条
    ui->progressBar->setValue(0);
    ui->progressBar->setVisible(false);

    // 启用拖拽
    setAcceptDrops(true);

    // 应用样式
    StyleSheet::applyDefaultStyle(this);
}

void MainWindow::setupConnections()
{
    connect(ui->selectFilesButton, &QPushButton::clicked, this, &MainWindow::onSelectFilesClicked);
    connect(ui->selectFolderButton, &QPushButton::clicked, this, &MainWindow::onSelectFolderClicked);
    connect(ui->startConvertButton, &QPushButton::clicked, this, &MainWindow::onStartConvertClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &MainWindow::onCancelConvertClicked);
    connect(ui->browseButton, &QPushButton::clicked, this, &MainWindow::onOutputDirClicked);
    connect(ui->openOutputButton, &QPushButton::clicked, this, &MainWindow::onOpenOutputDirClicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::onClearListClicked);
    connect(ui->formatComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onFormatChanged);

    if (m_fileWidget) {
        connect(m_fileWidget, &FileWidget::filesDropped, this, &MainWindow::onFilesDropped);
    }
}

void MainWindow::updateButtonsState(bool isConverting)
{
    ui->selectFilesButton->setEnabled(!isConverting);
    ui->selectFolderButton->setEnabled(!isConverting);
    ui->startConvertButton->setEnabled(!isConverting && m_fileWidget && m_fileWidget->getFileCount() > 0);
    ui->cancelButton->setEnabled(isConverting);
    ui->formatComboBox->setEnabled(!isConverting);
    ui->browseButton->setEnabled(!isConverting);

    ui->progressBar->setVisible(isConverting);
}

QString MainWindow::getDefaultOutputDir() const
{
    return QCoreApplication::applicationDirPath() + "/output";
}

void MainWindow::onSelectFilesClicked()
{
    QStringList files = QFileDialog::getOpenFileNames(
        this,
        "选择酷狗音乐文件",
        QDir::homePath(),
        "酷狗音乐文件 (*.kgm *.kgma *.kgg *.vpr);;所有文件 (*.*)"
    );

    if (!files.isEmpty() && m_fileWidget) {
        m_fileWidget->addFiles(files);
        updateButtonsState(false);
    }
}

void MainWindow::onSelectFolderClicked()
{
    QString folder = QFileDialog::getExistingDirectory(
        this,
        "选择文件夹",
        QDir::homePath()
    );

    if (!folder.isEmpty()) {
        QDir dir(folder);
        QStringList filters;
        filters << "*.kgm" << "*.kgma" << "*.kgg" << "*.vpr";
        QFileInfoList files = dir.entryInfoList(filters, QDir::Files);

        QStringList filePaths;
        for (const QFileInfo& info : files) {
            filePaths << info.absoluteFilePath();
        }

        if (!filePaths.isEmpty() && m_fileWidget) {
            m_fileWidget->addFiles(filePaths);
            updateButtonsState(false);
        }
    }
}

void MainWindow::showWarningMessage(const QString& title, const QString& msg)
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(title);
    msgBox.setText(msg);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setStyleSheet(R"(
        QMessageBox {
            background-color: #2d2d2d;
        }
        QMessageBox QLabel {
            color: #ffffff;
            font-size: 13px;
        }
        QPushButton {
            background-color: #ffa502;
            color: white;
            border: none;
            border-radius: 4px;
            padding: 8px 20px;
            font-size: 13px;
            min-width: 80px;
        }
        QPushButton:hover {
            background-color: #e69500;
        }
    )");
    msgBox.exec();
}

void MainWindow::onStartConvertClicked()
{
    if (!m_fileWidget || m_fileWidget->getFileCount() == 0) {
        showWarningMessage("警告", "请先添加要转换的文件！");
        return;
    }

    QString outputDir = ui->outputDirLineEdit->text();
    if (outputDir.isEmpty()) {
        showWarningMessage("警告", "请选择输出目录！");
        return;
    }

    QDir dir(outputDir);
    if (!dir.exists()) {
        if (!dir.mkpath(outputDir)) {
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("错误");
            msgBox.setText("无法创建输出目录！");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setStyleSheet(R"(
                QMessageBox {
                    background-color: #2d2d2d;
                }
                QMessageBox QLabel {
                    color: #ffffff;
                    font-size: 13px;
                }
                QPushButton {
                    background-color: #ff4757;
                    color: white;
                    border: none;
                    border-radius: 4px;
                    padding: 8px 20px;
                    font-size: 13px;
                    min-width: 80px;
                }
                QPushButton:hover {
                    background-color: #ee3742;
                }
            )");
            msgBox.exec();
            return;
        }
    }

    QStringList files = m_fileWidget->getAllFiles();
    QString format = ui->formatComboBox->currentData().toString();

    m_convertThread = new ConvertThread(this);
    m_convertThread->setFiles(files);
    m_convertThread->setOutputDir(outputDir);
    m_convertThread->setFormat(format);

    connect(m_convertThread, &ConvertThread::progress, this, &MainWindow::onConvertProgress);
    connect(m_convertThread, &ConvertThread::finished, this, &MainWindow::onConvertFinished);
    connect(m_convertThread, &ConvertThread::error, this, &MainWindow::onConvertError);
    connect(m_convertThread, &ConvertThread::finished, m_convertThread, &QObject::deleteLater);

    updateButtonsState(true);
    m_convertThread->start();
}

void MainWindow::onCancelConvertClicked()
{
    if (m_convertThread && m_convertThread->isRunning()) {
        m_convertThread->cancel();
    }
}

void MainWindow::onOutputDirClicked()
{
    QString dir = QFileDialog::getExistingDirectory(
        this,
        "选择输出目录",
        ui->outputDirLineEdit->text()
    );

    if (!dir.isEmpty()) {
        ui->outputDirLineEdit->setText(dir);
    }
}

void MainWindow::onOpenOutputDirClicked()
{
    QString dir = ui->outputDirLineEdit->text();
    if (QDir(dir).exists()) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(dir));
    }
}

void MainWindow::onClearListClicked()
{
    if (m_fileWidget) {
        m_fileWidget->clearAll();
        updateButtonsState(false);
    }
    ui->statusLabel->setText("列表已清空");
}

void MainWindow::onFormatChanged(int index)
{
    Q_UNUSED(index);
    m_outputFormat = ui->formatComboBox->currentData().toString();
}

void MainWindow::onConvertProgress(int current, int total, const QString& filename)
{
    int progress = (total > 0) ? (current * 100 / total) : 0;
    ui->progressBar->setValue(progress);
    ui->progressBar->setFormat(QString("%1%").arg(progress));
    ui->statusLabel->setText(QString("正在转换: %1 (%2/%3)").arg(filename).arg(current).arg(total));
}

void MainWindow::onConvertFinished(const QString& outputDir)
{
    ui->progressBar->setValue(100);
    ui->statusLabel->setText("转换完成！");
    updateButtonsState(false);

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("完成");
    msgBox.setText("文件转换完成！");
    msgBox.setInformativeText("输出目录: " + outputDir);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setStyleSheet(R"(
        QMessageBox {
            background-color: #2d2d2d;
        }
        QMessageBox QLabel {
            color: #ffffff;
            font-size: 13px;
        }
        QPushButton {
            background-color: #00A0E9;
            color: white;
            border: none;
            border-radius: 4px;
            padding: 8px 20px;
            font-size: 13px;
            min-width: 80px;
        }
        QPushButton:hover {
            background-color: #0088cc;
        }
    )");
    msgBox.exec();
}

void MainWindow::onConvertError(const QString& msg)
{
    ui->statusLabel->setText("转换出错: " + msg);
    updateButtonsState(false);

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("错误");
    msgBox.setText(msg);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setStyleSheet(R"(
        QMessageBox {
            background-color: #2d2d2d;
        }
        QMessageBox QLabel {
            color: #ffffff;
            font-size: 13px;
        }
        QPushButton {
            background-color: #ff4757;
            color: white;
            border: none;
            border-radius: 4px;
            padding: 8px 20px;
            font-size: 13px;
            min-width: 80px;
        }
        QPushButton:hover {
            background-color: #ee3742;
        }
    )");
    msgBox.exec();
}

void MainWindow::onFilesDropped(const QStringList& files)
{
    if (m_fileWidget) {
        m_fileWidget->addFiles(files);
        updateButtonsState(false);
    }
}
