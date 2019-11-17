#ifndef RTT_FILTERMODEL_H
#define RTT_FILTERMODEL_H

#include <QString>
class FilterModel {
  friend class FilterPresenter;

 private:
  // properties
  google::protobuf::FieldDescriptor * field_descriptor;
  google::protobuf::Message * reference_message;
  QString value;

 public:

  // methods
  bool operator==(const FilterModel & other) {
      return field_descriptor == other.field_descriptor && reference_message == other.reference_message && value == other.value;
  }

  FilterModel() = default;
  FilterModel(google::protobuf::FieldDescriptor *field_descriptor,
              google::protobuf::Message *reference_message,
              QString value)
      : field_descriptor(field_descriptor), reference_message(reference_message), value(std::move(value)) {}


  google::protobuf::FieldDescriptor *get_field_descriptor() const;
  void set_field_descriptor(google::protobuf::FieldDescriptor *field_descriptor);
  google::protobuf::Message *get_reference_message() const;
  void set_reference_message(google::protobuf::Message *reference_message);
  const QString &get_value() const;
  void set_value(const QString &value);



};


#endif //RTT_FILTERMODEL_H
