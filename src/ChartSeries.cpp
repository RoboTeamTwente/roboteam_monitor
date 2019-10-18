#include "include/ChartSeries.h"
#include <roboteam_proto/RobotCommand.pb.h>
#include <include/ChartView.h>

using namespace google::protobuf;

ChartSeries::ChartSeries(ChartView * chart_view) : QWidget(chart_view) {

  auto series_layout = new QVBoxLayout();
  this->setLayout(series_layout);

  series_title_line_edit = new QLineEdit();
  series_title_line_edit->setText("new series");
  series_layout->addWidget(series_title_line_edit);

  delete_series_button = new QPushButton();
  delete_series_button->setText("remove series");
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

const string &ChartSeries::getName() const {
  return name;
}

void ChartSeries::setName(const string &name) {
  ChartSeries::name = name;
}
