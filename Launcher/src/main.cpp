#include "mainwindow.h"
#include "processchecker.h"
#include "settingsdialog.h"

#include <QApplication>
#include <QMessageBox>
#include <QSettings>
#include <QSharedMemory>

void checkGameforgeClient();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Check if another instance of the app is already running
    QSharedMemory sharedMemory("Gfless Client");
    if (!sharedMemory.create(1))
    {
        QMessageBox::critical(nullptr, "Error", "Gfless Client is already running.");
        return 0;
    }

    checkGameforgeClient();

    QCoreApplication::setOrganizationName("Hatz Nostale");
    QCoreApplication::setApplicationName("Gfless Client");

    QSettings settings;
    settings.beginGroup("MainWindow");
    int theme = settings.value("theme", ThemeDefault).toInt();
    settings.endGroup();
    SettingsDialog::applyTheme(theme);

    MainWindow w;
    w.show();

    return a.exec();
}

void checkGameforgeClient()
{
    const wchar_t *gameforgeClientName = L"gfclient.exe";

    if (isProcessRunning(gameforgeClientName))
    {
        int res = QMessageBox::critical(nullptr, "Error", "Seems like Gameforge Client is running.\nDo you want to kill the process?", QMessageBox::Yes | QMessageBox::No);

        if (res == QMessageBox::Yes)
            killProcess(gameforgeClientName);

        else
            exit(0);
    }
}
