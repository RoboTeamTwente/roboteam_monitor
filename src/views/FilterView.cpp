//
// Created by Lukas Bos on 15/11/2019.
//

#include <src/presenters/FilterPresenter.h>
#include <src/presenters/SeriesPresenter.h>
#include "FilterView.h"
#include "AddFilterDialog.h"

FilterView::FilterView(FilterPresenter * filterPresenter, QWidget * parent) : QWidget(parent) {

    auto filter_layout = new QHBoxLayout();
    setLayout(filter_layout);


    auto add_filter_dialog = new AddFilterDialog((QWidget *) this);
    auto add_filter_button = new QPushButton();
    add_filter_button->setText("Select...");

    connect(add_filter_button, &QPushButton::clicked, add_filter_dialog, &QDialog::open);
    connect(add_filter_dialog, &AddFilterDialog::valueChanged, [add_filter_button, filterPresenter](const google::protobuf::FieldDescriptor * field_descriptor) {
      add_filter_button->setText(QString::fromStdString(field_descriptor->name()));
       // filterPresenter->set_field_descriptor(const_cast<google::protobuf::FieldDescriptor *>(field_descriptor));
    });

    filter_layout->addWidget(add_filter_button);

    auto filter_value_edit = new QLineEdit();
    filter_layout->addWidget(filter_value_edit);

    auto rm_filter_button = new QPushButton();
    rm_filter_button->setText("Remove");
    rm_filter_button->setStyleSheet("background-color: red;");
    filter_layout->addWidget(rm_filter_button);

    ////// VIEW --> MODEL /////
    connect(rm_filter_button, &QPushButton::clicked, [filterPresenter]() {
    //  series_input_settings_delegate->removeFilter(filterPresenter);
    });

}
