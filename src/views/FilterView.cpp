//
// Created by Lukas Bos on 15/11/2019.
//

#include <src/presenters/FilterPresenter.h>
#include <src/presenters/SeriesPresenter.h>
#include <src/presenters/SeriesSettingsPresenter.h>
#include <src/utils/Helpers.h>
#include "FilterView.h"
#include "AddFilterDialog.h"

FilterView::FilterView(FilterPresenter * filterPresenter, QWidget * parent) : QWidget(parent) {

    auto filter_layout = new QHBoxLayout();
    setLayout(filter_layout);


    auto add_filter_dialog = new AddFilterDialog((QWidget *) this);
    if (filterPresenter->getParent()->get_channel_type()) {
        add_filter_dialog->update_filters_layout(QString::fromStdString(proto::CHANNELS.at(filterPresenter->getParent()->get_channel_type()).name));
    }
    auto add_filter_button = new QPushButton();
    auto definition = filterPresenter->get_field_definition();
    if (definition) {
        add_filter_button->setText(definition->get_title());
    } else {
        add_filter_button->setText("Select...");
    }

    filter_layout->addWidget(add_filter_button);

    auto filter_value_edit = new QLineEdit();
    filter_value_edit->setText(filterPresenter->get_value());
    filter_layout->addWidget(filter_value_edit);

    auto rm_filter_button = new QPushButton();
    rm_filter_button->setText("Remove");
    rm_filter_button->setStyleSheet("background-color: red;");
    filter_layout->addWidget(rm_filter_button);

    ////// VIEW --> MODEL /////
    connect(rm_filter_button, &QPushButton::clicked, [filterPresenter]() {
      filterPresenter->getParent()->removeFilter(filterPresenter);
    });

    connect(add_filter_button, &QPushButton::clicked, add_filter_dialog, &QDialog::open);
    connect(add_filter_dialog, &AddFilterDialog::valueChanged, [add_filter_button, filterPresenter](FieldDefinition * field_definition) {
      add_filter_button->setText(field_definition->get_title());
      filterPresenter->set_field_definition(field_definition);
    });

    connect(filter_value_edit, &QLineEdit::textChanged, [filterPresenter](const QString & value) {
        filterPresenter->set_value(value);
    });


    ////// MODEL --> VIEW /////
    connect(filterPresenter, &FilterPresenter::value_changed, [filter_value_edit](const QString & value) {
       filter_value_edit->setText(value);
    });
}
