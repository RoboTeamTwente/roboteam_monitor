//
// Created by Lukas Bos on 15/11/2019.
//

#include <QPushButton>
#include <QHBoxLayout>
#include "ConfirmationWidget.h"
ConfirmationWidget::ConfirmationWidget(const QString & cancelText, const QString & confirmText, QWidget *parent) : QWidget(parent) {
    auto layout = new QHBoxLayout();
    setLayout(layout);

    cancelButton = new QPushButton();
    cancelButton->setText(cancelText);
    layout->addWidget(cancelButton);

    confirmButton = new QPushButton();
    confirmButton->setText(confirmText);
    confirmButton->setStyleSheet("background-color: gray");
    layout->addWidget(confirmButton);

    connect(cancelButton, &QPushButton::clicked, [this]() {
      emit cancel();
    });

    connect(confirmButton, &QPushButton::clicked, [this]() {
      emit confirm();
    });
}

QPushButton *ConfirmationWidget::get_cancel_button() const {
    return cancelButton;
}

QPushButton *ConfirmationWidget::get_confirm_button() const {
    return confirmButton;
}
void ConfirmationWidget::setDisabled(bool dirty, bool valid) {
    confirmButton->setDisabled(!dirty);
    if (dirty && valid) {
        confirmButton->setStyleSheet("background-color: green");
    } else if (dirty) {
        confirmButton->setStyleSheet("background-color: orange");
    } else {
        confirmButton->setStyleSheet("background-color: gray");
    }
}


