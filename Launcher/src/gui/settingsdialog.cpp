#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QApplication>
#include <QFile>

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent),
                                                  ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    initLanguageComboBox();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

QString SettingsDialog::getGameClientPath() const
{
    return ui->gameClientPathLineEdit->text();
}

QString SettingsDialog::getProfilesPath() const
{
    return ui->profilesPathLineEdit->text();
}

int SettingsDialog::getOpenInterval() const
{
    return ui->openIntervalSpinBox->value();
}

int SettingsDialog::getGameLanguage() const
{
    return ui->gameLanguageComboBox->currentData().toInt();
}

int SettingsDialog::getGameLanguageIndex() const
{
    return ui->gameLanguageComboBox->currentIndex();
}

int SettingsDialog::getTheme() const
{
    return ui->themeComboBox->currentIndex();
}

void SettingsDialog::setGameClientPath(const QString &path)
{
    ui->gameClientPathLineEdit->setText(path);
}

void SettingsDialog::setProfilesPath(const QString &path)
{
    ui->profilesPathLineEdit->setText(path);
}

void SettingsDialog::setOpenInterval(int n)
{
    ui->openIntervalSpinBox->setValue(n);
}

void SettingsDialog::setGameLanguage(int language)
{
    ui->gameLanguageComboBox->setCurrentIndex(language);
}

void SettingsDialog::setTheme(int index)
{
    ui->themeComboBox->setCurrentIndex(index);
    applyTheme(index);
}

void SettingsDialog::applyTheme(int index)
{
    QPalette pal;

    if (index == 1)
    {
        pal.setColor(QPalette::Window, QColor(0xf6, 0xf8, 0xfa));
        pal.setColor(QPalette::WindowText, QColor(0x1f, 0x23, 0x28));
        pal.setColor(QPalette::Base, QColor(0xff, 0xff, 0xff));
        pal.setColor(QPalette::AlternateBase, QColor(0xea, 0xee, 0xf2));
        pal.setColor(QPalette::Text, QColor(0x1f, 0x23, 0x28));
        pal.setColor(QPalette::Button, QColor(0xff, 0xff, 0xff));
        pal.setColor(QPalette::ButtonText, QColor(0x1f, 0x23, 0x28));
        pal.setColor(QPalette::Highlight, QColor(0x7a, 0x5a, 0xf8));
        pal.setColor(QPalette::HighlightedText, QColor(0xff, 0xff, 0xff));
        pal.setColor(QPalette::ToolTipBase, QColor(0xff, 0xff, 0xff));
        pal.setColor(QPalette::ToolTipText, QColor(0x1f, 0x23, 0x28));
        pal.setColor(QPalette::PlaceholderText, QColor(0x65, 0x6d, 0x76));
    }
    else
    {
        pal.setColor(QPalette::Window, QColor(0x0e, 0x11, 0x17));
        pal.setColor(QPalette::WindowText, QColor(0xe6, 0xed, 0xf3));
        pal.setColor(QPalette::Base, QColor(0x16, 0x1b, 0x22));
        pal.setColor(QPalette::AlternateBase, QColor(0x1c, 0x21, 0x28));
        pal.setColor(QPalette::Text, QColor(0xe6, 0xed, 0xf3));
        pal.setColor(QPalette::Button, QColor(0x21, 0x26, 0x2d));
        pal.setColor(QPalette::ButtonText, QColor(0xe6, 0xed, 0xf3));
        pal.setColor(QPalette::Highlight, QColor(0x7a, 0x5a, 0xf8));
        pal.setColor(QPalette::HighlightedText, QColor(0xff, 0xff, 0xff));
        pal.setColor(QPalette::ToolTipBase, QColor(0x16, 0x1b, 0x22));
        pal.setColor(QPalette::ToolTipText, QColor(0xe6, 0xed, 0xf3));
        pal.setColor(QPalette::PlaceholderText, QColor(0x6e, 0x76, 0x81));
    }

    qApp->setPalette(pal);

    QString qss = index == 1 ? ":/resources/light.qss" : ":/resources/dark.qss";

    QFile styleFile(qss);

    if (styleFile.open(QFile::ReadOnly | QFile::Text))
    {
        qApp->setStyleSheet(styleFile.readAll());
    }
}

void SettingsDialog::setThemeComboBox(int index)
{
    ui->themeComboBox->setCurrentIndex(index);
}

void SettingsDialog::setDisabledNosmall(bool b)
{
    ui->disableNosmallChekcbox->setChecked(b);
}

bool SettingsDialog::getDisabledNosmall() const
{
    return ui->disableNosmallChekcbox->isChecked();
}

void SettingsDialog::setCheckUpdates(bool b)
{
    ui->checkUpdatesCheckbox->setChecked(b);
}

bool SettingsDialog::getCheckUpdates() const
{
    return ui->checkUpdatesCheckbox->isChecked();
}

void SettingsDialog::on_selectGamePathButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Select NostaleClientX.exe", QDir::rootPath(), "NostaleClientX.exe (NostaleClientX.exe)");

    if (path.isEmpty())
        return;

    setGameClientPath(path);
}

void SettingsDialog::initLanguageComboBox()
{
    ui->gameLanguageComboBox->addItem("English", 0);
    ui->gameLanguageComboBox->addItem("Deutsch", 1);
    ui->gameLanguageComboBox->addItem("Français", 2);
    ui->gameLanguageComboBox->addItem("Italiano", 3);
    ui->gameLanguageComboBox->addItem("Polski", 4);
    ui->gameLanguageComboBox->addItem("Español", 5);
    ui->gameLanguageComboBox->addItem("Türkçe", 8);
    ui->gameLanguageComboBox->addItem("Čeština", 7);
}

void SettingsDialog::on_selectProfilePathButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Select profile", QDir::rootPath(), "(*.ini)");

    if (path.isEmpty())
        return;

    setProfilesPath(path);

    emit profilesPathSelected(path);
}

void SettingsDialog::on_themeComboBox_currentIndexChanged(int index)
{
    setTheme(index);
}
