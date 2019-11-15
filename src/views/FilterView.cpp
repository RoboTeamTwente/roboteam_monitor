//
// Created by Lukas Bos on 15/11/2019.
//

#include <src/models/FilterModel.h>
#include <src/models/SeriesModel.h>
#include "FilterView.h"
#include "AddFilterDialog.h"
FilterView::FilterView(FilterModel * filterModel, SeriesInputSettingsModel * inputSettingsModel, QWidget * parent)
        : QWidget(parent), filterModel(filterModel), inputSettingsModel(inputSettingsModel) {

    auto filter_layout = new QHBoxLayout();
    setLayout(filter_layout);


    auto add_filter_dialog = new AddFilterDialog((QWidget *) this);
    auto add_filter_button = new QPushButton();
    add_filter_button->setText("Select...");

    connect(add_filter_button, &QPushButton::clicked, add_filter_dialog, &QDialog::open);
    connect(add_filter_dialog, &AddFilterDialog::valueChanged, [add_filter_button, filterModel](const google::protobuf::FieldDescriptor * field_descriptor) {
      add_filter_button->setText(QString::fromStdString(field_descriptor->name()));
        filterModel->set_field_descriptor(const_cast<google::protobuf::FieldDescriptor *>(field_descriptor));
    });

    filter_layout->addWidget(add_filter_button);

    auto filter_value_edit = new QLineEdit();
    filter_layout->addWidget(filter_value_edit);

    auto rm_filter_button = new QPushButton();
    rm_filter_button->setText("Remove");
    rm_filter_button->setStyleSheet("background-color: red;");
    filter_layout->addWidget(rm_filter_button);

    ////// VIEW --> MODEL /////
    connect(rm_filter_button, &QPushButton::clicked, [inputSettingsModel, filterModel]() {
      inputSettingsModel->removeFilter(filterModel);
    });

}
