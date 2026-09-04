#ifndef OTPDIALOG_H
#define OTPDIALOG_H

#include <QDialog>

namespace Ui {
class OtpDialog;
}

class OtpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OtpDialog(QWidget *parent = nullptr);
    ~OtpDialog();

    QString getOtpCode() const;

private slots:
    void on_confirmButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::OtpDialog *ui;
};

#endif // OTPDIALOG_H
