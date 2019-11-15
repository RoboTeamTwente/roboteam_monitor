#include <src/models/SeriesModel.h>
#include <roboteam_utils/constants.h>
#include <src/utils/Helpers.h>
#include <src/views/AddFilterDialog.h>
#include <src/views/components/ConfirmationWidget.h>
#include "ChartSeriesDialog.h"
#include "SeriesInputSettingsView.h"

ChartSeriesDialog::ChartSeriesDialog(SeriesModel *series, QWidget * parent) : QDialog(parent) {
    setMinimumWidth(600);
    auto dialog_layout = new QVBoxLayout(this);
    setLayout(dialog_layout);

    auto tab_widget = new QTabWidget();
    dialog_layout->addWidget(tab_widget);

    // input settings
    auto inputSettingsView = new SeriesInputSettingsView(series->get_settings_model());
    tab_widget->addTab(inputSettingsView, "Input");

    // visualization settings
//    QWidget * visualization_tab = create_visualization_settings_tab(series);
//    tab_widget->addTab(visualization_tab, "Visualization");
}

//
//QWidget *ChartSeriesDialog::create_visualization_settings_tab(SeriesModel *series) {
//    auto visualization_widget = new QWidget();
//    auto visualization_layout = new QHBoxLayout();
//    visualization_widget->setLayout(visualization_layout);
//
//    auto groupBox = new QGroupBox(tr("Data to plot"));
//    auto radio_rate = new QRadioButton("Data rate (packets/s)");
//    auto radio_field = new QRadioButton("Custom field");
//    radio_rate->setChecked(true);
//
//    auto vbox = new QVBoxLayout;
//    vbox->addWidget(radio_rate);
//    vbox->addWidget(radio_field);
//    vbox->addStretch(1);
//    groupBox->setLayout(vbox);
//
//    visualization_layout->addWidget(groupBox);
//
//    auto filter_widget = new QWidget();
//    auto filter_layout = new QHBoxLayout();
//    filter_widget->setLayout(filter_layout);
//    select_field_dialog = new AddFilterDialog((QWidget *) this);
//    auto select_field_button = new QPushButton();
//    select_field_button->setText("Select...");
//    select_field_button->setStyleSheet("background-color: gray");
//
//    connect(select_field_button, &QPushButton::clicked, select_field_dialog, &QDialog::open);
//    connect(select_field_dialog, &AddFilterDialog::valueChanged, [select_field_button](const google::protobuf::FieldDescriptor * field_descriptor) {
//      select_field_button->setText(QString::fromStdString(field_descriptor->name()));
//    });
//    connect(radio_field, &QRadioButton::toggled, [select_field_button](bool checked) {
//        select_field_button->setDisabled(!checked);
//        if (checked) {
//            select_field_button->setStyleSheet("background-color: none");
//        } else {
//            select_field_button->setStyleSheet("background-color: gray");
//        }
//    });
//
//    if (selected_topic_name!="") {
//        select_field_dialog->update_filters_layout(selected_topic_name);
//    }
//    visualization_layout->addWidget(select_field_button);
//
//
//
//    return visualization_widget;
//}


