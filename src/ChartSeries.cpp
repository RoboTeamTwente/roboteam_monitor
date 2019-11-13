#include "ChartSeries.h"
#include <roboteam_proto/RobotCommand.pb.h>
#include <Chart.h>
#include <functional>
#include <roboteam_utils/constants.h>
#include <ChartSeriesDialog.h>

using namespace google::protobuf;

ChartSeries::ChartSeries(const QString & default_name, Chart * chart_view) : QGroupBox("", chart_view) {
  this->setCheckable(false);
  qt_series = new QSplineSeries();


  srand (time(NULL));

  // dummy data
  qt_series->append(0, rand() % 20 + 1);
  qt_series->append(2, rand() % 20 + 1);
  qt_series->append(4, rand() % 20 + 1);
  qt_series->append(16, rand() % 20 + 1);

  setMaximumHeight(260);

  connect(qt_series, &QXYSeries::colorChanged, this, &ChartSeries::set_change_color_button_background);

  auto series_layout = new QVBoxLayout();
  this->setLayout(series_layout);

  auto title_and_color_layout = new QHBoxLayout();
  auto series_title_line_edit = new QLineEdit();
  series_title_line_edit->setText(default_name);
  set_name(default_name);
  title_and_color_layout->addWidget(series_title_line_edit);

  connect(series_title_line_edit, &QLineEdit::textChanged, [this, chart_view](const QString & new_title) {
    set_name(new_title);
  });


  change_color_button = new QPushButton();
  change_color_button->setText("");
  title_and_color_layout->addWidget(change_color_button);

  auto color_dialog = new QColorDialog();
  connect(color_dialog, &QColorDialog::colorSelected, this, &ChartSeries::set_color);
  connect(color_dialog, &QColorDialog::currentColorChanged, this, &ChartSeries::set_color);

  connect(change_color_button, &QPushButton::clicked, [color_dialog]() {
    color_dialog->exec();
  });

  auto visible_checkbox = new QCheckBox("visible");
  visible_checkbox->setChecked(true);
  title_and_color_layout->addWidget(visible_checkbox);
  connect(visible_checkbox, &QCheckBox::toggled, this, &ChartSeries::set_visible);

  series_layout->addLayout(title_and_color_layout);

  auto delete_series_button = new QPushButton();
  delete_series_button->setText("Remove series");

  delete_series_button->setAutoFillBackground(true);
  delete_series_button->setStyleSheet("background-color: red");

  series_layout->addWidget(delete_series_button);

  connect(delete_series_button, &QPushButton::clicked, [this, chart_view]() {
    chart_view->delete_series(this);
  });


  auto series_settings_button = new QPushButton();
  series_settings_button->setText("Configuration");
  series_layout->addWidget(series_settings_button);

  ChartSeriesDialog * series_dialog = new ChartSeriesDialog(this);
  connect(series_settings_button, &QPushButton::clicked, [this, series_dialog]() {
    series_dialog->exec();
  });
}

void ChartSeries::set_name(const QString &name) {
  qt_series->setName(name);
}

QXYSeries * ChartSeries::get_qt_series() {
  return qt_series;
}

void ChartSeries::set_visible(bool visible) {
  qt_series->setVisible(visible);
}

void ChartSeries::set_color(const QColor & color) {
  qt_series->setColor(color);
  set_change_color_button_background(color);
}

void ChartSeries::set_change_color_button_background(const QColor & color) const {
  QString change_color_button_stylesheet = "background-color: " + color.name() +";";
  change_color_button->setStyleSheet(change_color_button_stylesheet);
}

void ChartSeries::init_subscriber_for_channel_type(const proto::ChannelType & channel_type) {

    proto_subscriber = new proto::Subscriber<proto::RobotCommand>
        (proto::ROBOT_COMMANDS_PRIMARY_CHANNEL, &ChartSeries::handle_robot_command_input, this);

}

void ChartSeries::handle_robot_command_input(proto::RobotCommand &robot_command) {
  auto reflection = proto::RobotCommand::GetReflection();
  this->handle_incoming_message(robot_command, *reflection);
}

void ChartSeries::handle_world_input(proto::World &world) {
  auto reflection = proto::World::GetReflection();
  this->handle_incoming_message(world, *reflection);
}

void ChartSeries::handle_feedback_input(proto::RobotFeedback &feedback) {
  auto reflection = proto::RobotFeedback::GetReflection();
  this->handle_incoming_message(feedback, *reflection);
}

void ChartSeries::handle_setting_input(proto::Setting &setting) {
  auto reflection = proto::Setting::GetReflection();
  this->handle_incoming_message(setting, *reflection);
}

void ChartSeries::update_channel(const proto::ChannelType & channel_type) {
  if (this->channel_type != channel_type) {
    this->channel_type = channel_type;
    init_subscriber_for_channel_type(channel_type);
  }
}

template<class T>
void ChartSeries::handle_incoming_message(T message, const Reflection &reflection) {
  auto current_time = roboteam_utils::Timer::getCurrentTime();
  auto field_descriptors = std::vector<const google::protobuf::FieldDescriptor *>();
  reflection.ListFields(message, &field_descriptors);

  for (auto field_descriptor : field_descriptors) {
    switch(field_descriptor->cpp_type()) {
      case FieldDescriptor::CPPTYPE_FLOAT: break;
      case FieldDescriptor::CPPTYPE_INT32: break;
      default: break;
    }
  }
}

const std::vector<Filter *> &ChartSeries::get_filters() {
    return filters;
}

Filter * ChartSeries::add_new_filter() {
    auto empty_filter = new Filter();
    filters.push_back(empty_filter);
    return empty_filter;
}

void ChartSeries::removeFilter(Filter *filter_to_remove) {
    filters.erase(std::remove(filters.begin(), filters.end(), filter_to_remove), filters.end());
}

