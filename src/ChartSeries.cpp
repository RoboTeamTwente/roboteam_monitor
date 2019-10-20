#include "include/ChartSeries.h"
#include <roboteam_proto/RobotCommand.pb.h>
#include <include/ChartView.h>
#include <stdlib.h>     /* srand, rand */

using namespace google::protobuf;

ChartSeries::ChartSeries(const QString & default_name, ChartView * chart_view) : QGroupBox("", chart_view) {
  this->setCheckable(false);

  qt_series = new QSplineSeries();


  srand (time(NULL));

  // dummy data
  qt_series->append(0, rand() % 20 + 1);
  qt_series->append(2, rand() % 20 + 1);
  qt_series->append(4, rand() % 20 + 1);
  qt_series->append(16, rand() % 20 + 1);

  setMaximumHeight(160);

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








  roboteam_proto::RobotCommand robot_command;

  /*
   * Getting a list of all members of a class is called 'Reflection'.
   * For more info, see: https://en.wikipedia.org/wiki/Reflection_(computer_programming)
   */
  auto reflection = roboteam_proto::RobotCommand::GetReflection();
  auto fieldDescriptors = new std::vector<const FieldDescriptor *>();
  reflection->ListFields(robot_command, fieldDescriptors);

  // I need the message to subscribe to.
  // and I need to get values for a specific type and name.
  // or a set of types and names.
  // A topic is always linked to a type
  // So we need to have a map of topics and their respective type.

  // list through all known fields
  for (auto field_descriptor : *fieldDescriptors) {
    auto cpp_type = field_descriptor->cpp_type();

    switch(cpp_type) {
      case FieldDescriptor::CppType::CPPTYPE_FLOAT: {
        reflection->GetFloat(robot_command, field_descriptor);
        break;
      }
      case FieldDescriptor::CppType::CPPTYPE_INT32: {
        reflection->GetInt64(robot_command, field_descriptor);
        break;
      }
      case FieldDescriptor::CPPTYPE_BOOL: {
        reflection->GetBool(robot_command, field_descriptor);
        break;
      }
      default: {
        // Do nothing if not float, int or bool
        break;
      }
    }
  }
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
