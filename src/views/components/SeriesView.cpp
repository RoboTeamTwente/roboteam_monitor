//
// Created by Lukas Bos on 13/11/2019.
//

#include <QVBoxLayout>
#include <QPushButton>
#include <src/models/SeriesModel.h>
#include <src/models/ChartModel.h>

#include "SeriesView.h"

SeriesView::SeriesView(SeriesModel* model, QWidget *parent) : QWidget(parent) {
    this->model = model;
    auto seriesLayout = new QVBoxLayout();
    setLayout(seriesLayout);


    auto title_and_color_layout = new QHBoxLayout();

    // name text edit
    auto series_title_line_edit = new QLineEdit();
    series_title_line_edit->setText(model->getName());
    title_and_color_layout->addWidget(series_title_line_edit);
    connect(series_title_line_edit, &QLineEdit::textChanged, model, &SeriesModel::setName);



    auto change_color_button = new QPushButton();
    change_color_button->setText("");
    change_color_button->setAutoFillBackground(true);
    QString change_color_button_stylesheet = "background-color: " + model->getColor().name() +";";
    change_color_button->setStyleSheet(change_color_button_stylesheet);
    title_and_color_layout->addWidget(change_color_button);

    auto color_dialog = new QColorDialog();
    connect(color_dialog, &QColorDialog::colorSelected, model, &SeriesModel::setColor);

    // handle color change
    connect(model, &SeriesModel::qtSeriesChanged, [change_color_button, model]() {
      QString change_color_button_stylesheet = "background-color: " + model->getColor().name() +";";
      change_color_button->setStyleSheet(change_color_button_stylesheet);
    });

    connect(change_color_button, &QPushButton::clicked, [color_dialog]() {
      color_dialog->exec();
    });


    auto visible_checkbox = new QCheckBox("visible");
    visible_checkbox->setChecked(true);
    title_and_color_layout->addWidget(visible_checkbox);
    // connect(visible_checkbox, &QCheckBox::toggled, model, &SeriesModel::setVisible);
    seriesLayout->addLayout(title_and_color_layout);


    auto removeSeriesBtn = new QPushButton();
    removeSeriesBtn->setText("Remove");
    seriesLayout->addWidget(removeSeriesBtn);

    connect(removeSeriesBtn, &QPushButton::clicked, [model]() {
        model->get_parent()->removeSeries(model);
    });
}
