//
// Created by Lukas Bos on 15/11/2019.
//

#ifndef RTT_CONFIRMATIONWIDGET_H
#define RTT_CONFIRMATIONWIDGET_H

#include <QWidget>
#include <QPushButton>

class ConfirmationWidget : public QWidget {
  Q_OBJECT
 private:
  QPushButton * cancelButton;
  QPushButton * confirmButton;
 public:
  ConfirmationWidget( const QString & cancelText = "Cancel", const QString & confirmText = "Ok", QWidget *parent = nullptr);
  QPushButton * get_cancel_button() const;
  QPushButton * get_confirm_button() const;

 public slots:
  void setDisabled(bool disabled);

  signals:
    void confirm();
    void cancel();
};

#endif //RTT_CONFIRMATIONWIDGET_H
