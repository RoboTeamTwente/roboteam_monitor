/*
 * This view displays the series settings dialog.
 *
 * It shows the GUI for input settings and visualization settings.
 */

#include <src/presenters/SeriesPresenter.h>
#include <roboteam_utils/constants.h>
#include <src/utils/Helpers.h>
#include <src/views/AddFilterDialog.h>
#include <src/views/components/ConfirmationWidget.h>
#include "SeriesSettingsDialog.h"

SeriesSettingsDialog::SeriesSettingsDialog(SeriesSettingsPresenter * presenter, QWidget * parent) : QDialog(parent), presenter(presenter){
    setMinimumWidth(600);
    auto network_settings_layout = new QVBoxLayout(this);
    network_settings_layout->setAlignment(Qt::AlignTop);
    setLayout(network_settings_layout);


    // communication layout
    auto comm_layout = new QHBoxLayout();
    auto channel_combo_box = new QComboBox();
    comm_layout->addWidget(channel_combo_box);
    for (auto const &channel : proto::CHANNELS) {
        channel_combo_box->addItem(QString::fromStdString(channel.second.name));
    }
    network_settings_layout->addLayout(comm_layout);

    auto current_filters_label = new QLabel();
    current_filters_label->setText("Active filters");
    network_settings_layout->addWidget(current_filters_label);

    auto current_filters_layout = new QVBoxLayout();
    for (auto filter_presenter : presenter->get_filters()) {
        auto filterView = new FilterView(filter_presenter, this);
        filterMap.insert(std::make_pair(filter_presenter, filterView));
        current_filters_layout->addWidget(filterView);
    }
    network_settings_layout->addLayout(current_filters_layout);

    auto add_new_filter_button = new QPushButton();
    add_new_filter_button->setText("Add new filter");

    network_settings_layout->addWidget(add_new_filter_button);




    auto visualization_layout = new QHBoxLayout();
    network_settings_layout->addLayout(visualization_layout);

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
    select_field_button->setHidden(presenter->use_packet_rate());
    network_settings_layout->addWidget(select_field_button);

    auto confirmWidget = new ConfirmationWidget("Cancel", "Apply", this);
    network_settings_layout->addWidget(confirmWidget);

    connect(select_field_button, &QPushButton::clicked, select_field_dialog, &QDialog::open);
    connect(select_field_dialog, &AddFilterDialog::valueChanged, [select_field_button](const google::protobuf::FieldDescriptor * field_descriptor) {
      select_field_button->setText(QString::fromStdString(field_descriptor->name()));
    });

    connect(presenter, &SeriesSettingsPresenter::rateSettingChanged, [select_field_button](bool use_packet_rate) {
      select_field_button->setDisabled(use_packet_rate);
      select_field_button->setHidden(use_packet_rate);
    });


    ////// VIEW --> MODEL CONNECTIONS /////
    connect(add_new_filter_button, &QPushButton::clicked, presenter, &SeriesSettingsPresenter::add_new_filter);
    connect(channel_combo_box, &QComboBox::currentTextChanged, [presenter](const QString & text) {
      presenter->update_channel(text);
    });

    connect(radio_rate, &QRadioButton::toggled, [presenter, select_field_button](bool checked) {
      presenter->set_use_packet_rate(checked);

    });

    connect(select_field_dialog, &AddFilterDialog::valueChanged, [presenter](const google::protobuf::FieldDescriptor * fd) {
      presenter->set_field_to_show(const_cast<google::protobuf::FieldDescriptor *>(fd));
    });

    ////// MODEL --> VIEW CONNECTIONS /////
    connect(presenter, &SeriesSettingsPresenter::filterAdded, [this, presenter, current_filters_layout](FilterPresenter * new_filter) {
      auto filterView = new FilterView(new_filter, this);
      auto pair = std::make_pair(new_filter, filterView);
      filterMap.insert(pair);
      current_filters_layout->addWidget(filterView);
    });

    connect(presenter, &SeriesSettingsPresenter::channelChanged, [select_field_dialog](const proto::ChannelType & type) {
      select_field_dialog->update_filters_layout(QString::fromStdString(proto::CHANNELS.at(type).name));
    });


    connect(presenter, &SeriesSettingsPresenter::filterRemoved, [this, presenter, current_filters_layout](FilterPresenter * removed_filter) {
        if (filterMap.count(removed_filter) == 0) {
            std::cerr << "[SeriesSettingsDialog] It looks like the filter was removed already." << std::endl;
        } else {
            auto filterView = filterMap.at(removed_filter);
            filterView->hide();
            current_filters_layout->removeWidget(filterView);
            filterMap.erase(removed_filter);
        }
    });

    connect(presenter, &SeriesSettingsPresenter::modelChanged, [this, presenter, current_filters_layout, channel_combo_box, radio_field, radio_rate]() {
      channel_combo_box->setCurrentText(QString::fromStdString(proto::CHANNELS.at(presenter->get_channel_type()).name));
      // Refresh filters
      for (auto const& [model, view] : filterMap) {
          view->hide();
          current_filters_layout->removeWidget(view);
      }
      filterMap.clear();
      for (auto filter_presenter : presenter->get_filters()) {
          auto filterView = new FilterView(filter_presenter, this);
          filterMap.insert(std::make_pair(filter_presenter, filterView));
          current_filters_layout->addWidget(filterView);
      }
      radio_rate->setChecked(presenter->use_packet_rate());
      radio_field->setChecked(!presenter->use_packet_rate());
      presenter->createSnapShot();
    });

    connect(this, &SeriesSettingsDialog::user_event_dirty, confirmWidget, &ConfirmationWidget::setDisabled);
    connect(this, &QDialog::rejected, presenter, &SeriesSettingsPresenter::rollBack);
    connect(this, &QDialog::accepted, presenter, &SeriesSettingsPresenter::createSnapShot);
    connect(confirmWidget, &ConfirmationWidget::cancel, this, &QDialog::reject);
    connect(confirmWidget, &ConfirmationWidget::confirm, this, &QDialog::accept);
    connect(confirmWidget, &ConfirmationWidget::confirm, presenter, &SeriesSettingsPresenter::confirm);
}

/*
 * On 'an event' we check if the model is dirty or not.
 */
bool SeriesSettingsDialog::event(QEvent *event) {
    emit user_event_dirty(presenter->is_dirty());
    return QWidget::event(event);
}

/*
 * Override execution of opening the dialog by making a snapshot of the data in it first.
 */
int SeriesSettingsDialog::exec() {
    presenter->createSnapShot();
    return QDialog::exec();
}






