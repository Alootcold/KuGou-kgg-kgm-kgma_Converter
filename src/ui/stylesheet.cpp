#include "stylesheet.h"
#include <QApplication>

StyleSheet::StyleSheet(QObject *parent)
    : QObject(parent)
{
}

StyleSheet::~StyleSheet()
{
}

void StyleSheet::applyDefaultStyle(QWidget* widget)
{
    if (!widget) return;

    QString styleSheet = getDefaultStyleSheet();
    widget->setStyleSheet(styleSheet);

    QFont font = widget->font();
    font.setFamily("Microsoft YaHei");
    font.setPointSize(10);
    widget->setFont(font);
}

QString StyleSheet::getButtonStyle()
{
    return R"(
        QPushButton {
            background-color: #1DB954;
            color: white;
            border: none;
            border-radius: 6px;
            padding: 8px 20px;
            font-size: 13px;
            font-family: Microsoft YaHei;
        }
        QPushButton:hover {
            background-color: #17a044;
        }
        QPushButton:pressed {
            background-color: #138a38;
        }
        QPushButton:disabled {
            background-color: #aaaaaa;
        }
    )";
}

QString StyleSheet::getTableStyle()
{
    return R"(
        QTableWidget {
            border: 1px solid #ddd;
            border-radius: 4px;
            background-color: white;
            font-family: Microsoft YaHei;
        }
        QTableWidget::item {
            padding: 8px;
        }
        QTableWidget::item:selected {
            background-color: #E8FFE8;
        }
        QHeaderView::section {
            background-color: #f5f5f5;
            padding: 8px;
            border: none;
            border-right: 1px solid #ddd;
            border-bottom: 1px solid #ddd;
            font-weight: bold;
            color: #333;
            font-family: Microsoft YaHei;
        }
    )";
}

QString StyleSheet::getProgressBarStyle()
{
    return R"(
        QProgressBar {
            border: 1px solid #ddd;
            border-radius: 4px;
            text-align: center;
            font-family: Microsoft YaHei;
        }
        QProgressBar::chunk {
            background-color: #1DB954;
            border-radius: 3px;
        }
    )";
}

QString StyleSheet::getDefaultStyleSheet()
{
    return R"(
        QMainWindow {
            background-color: #ffffff;
        }
        QWidget {
            font-family: Microsoft YaHei;
            font-size: 10pt;
        }
        QPushButton {
            background-color: #1DB954;
            color: white;
            border: none;
            border-radius: 6px;
            padding: 8px 20px;
            font-size: 13px;
            font-family: Microsoft YaHei;
        }
        QPushButton:hover {
            background-color: #17a044;
        }
        QPushButton:pressed {
            background-color: #138a38;
        }
        QPushButton:disabled {
            background-color: #aaaaaa;
        }
        QLineEdit {
            border: 1px solid #ddd;
            border-radius: 4px;
            padding: 5px;
            font-family: Microsoft YaHei;
        }
        QLineEdit:focus {
            border: 1px solid #1DB954;
        }
        QComboBox {
            border: 1px solid #ddd;
            border-radius: 4px;
            padding: 5px;
            font-family: Microsoft YaHei;
        }
        QComboBox::drop-down {
            border: none;
        }
        QComboBox:focus {
            border: 1px solid #1DB954;
        }
        QProgressBar {
            border: 1px solid #ddd;
            border-radius: 4px;
            text-align: center;
            font-family: Microsoft YaHei;
        }
        QProgressBar::chunk {
            background-color: #1DB954;
            border-radius: 3px;
        }
        QTableWidget {
            border: 1px solid #ddd;
            border-radius: 4px;
            background-color: white;
            font-family: Microsoft YaHei;
        }
        QTableWidget::item {
            padding: 8px;
        }
        QTableWidget::item:selected {
            background-color: #E8FFE8;
        }
        QHeaderView::section {
            background-color: #f5f5f5;
            padding: 8px;
            border: none;
            border-right: 1px solid #ddd;
            border-bottom: 1px solid #ddd;
            font-weight: bold;
            color: #333;
            font-family: Microsoft YaHei;
        }
        QStatusBar {
            background-color: #f5f5f5;
            color: #333;
            font-family: Microsoft YaHei;
        }
        QLabel {
            color: #333;
            font-family: Microsoft YaHei;
        }
    )";
}

void applyStylesheet(QWidget* widget)
{
    StyleSheet::applyDefaultStyle(widget);
}
