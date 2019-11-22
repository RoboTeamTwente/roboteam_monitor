#ifndef RTT_FIELDDEFINITION_H
#define RTT_FIELDDEFINITION_H

#include <roboteam_utils/json.hpp>
#include <google/protobuf/descriptor.h>
#include <QString>

using json = nlohmann::json;

class FieldDefinition {
 public:
  FieldDefinition(QString title, std::vector<int> field_numbers);
  FieldDefinition();
  FieldDefinition(const json & data);

  const std::vector<int> &get_field_numbers() const;
  const QString &get_title() const;
  json to_json();
  bool is_valid();

 private:
  QString title = "";
  std::vector<int> field_numbers;
};

#endif //RTT_FIELDDEFINITION_H
