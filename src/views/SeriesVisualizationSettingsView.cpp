#include <QHBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include "SeriesVisualizationSettingsView.h"
#include "AddFilterDialog.h"

SeriesVisualizationSettingsView::SeriesVisualizationSettingsView(QWidget *parent) : QWidget(parent) {
    auto visualization_layout = new QHBoxLayout();
    setLayout(visualization_layout);

    auto groupBox = new QGroupBox(tr("Data to plot"));
    auto radio_rate = new QRadioButton("Data rate (packets/s)");
    auto radio_field = new QRadioButton("Custom field");
    radio_rate->setChecked(true);

    auto vbox = new QVBoxLayout;
    vbox->addWidget(radio_rate);
    vbox->addWidget(radio_field);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    visualization_layout->addWidget(groupBox);

    auto filter_widget = new QWidget();
    auto filter_layout = new QHBoxLayout();
    filter_widget->setLayout(filter_layout);

    auto select_field_dialog = new AddFilterDialog((QWidget *) this);
    auto select_field_button = new QPushButton();
    select_field_button->setText("Select...");
    select_field_button->setStyleSheet("background-color: gray");

    connect(select_field_button, &QPushButton::clicked, select_field_dialog, &QDialog::open);
    connect(select_field_dialog, &AddFilterDialog::valueChanged, [select_field_button](const google::protobuf::FieldDescriptor * field_descriptor) {
      select_field_button->setText(QString::fromStdString(field_descriptor->name()));
    });
    connect(radio_field, &QRadioButton::toggled, [select_field_button](bool checked) {
        select_field_button->setDisabled(!checked);
        if (checked) {
            select_field_button->setStyleSheet("background-color: none");
        } else {
            select_field_button->setStyleSheet("background-color: gray");
        }
    });

    visualization_layout->addWidget(select_field_button);
}
