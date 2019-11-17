#ifndef RTT_FILTERMODEL_H
#define RTT_FILTERMODEL_H

#include <QString>
#include <src/presenters/SeriesPresenter.h>

class SeriesPresenter;
class SeriesInputSettingsPresenter;
class FilterModel {

  // Presenter
  friend class FilterPresenter;

  // properties
  google::protobuf::FieldDescriptor * field_descriptor;
  google::protobuf::Message * reference_message;
  QString value;

  // Relations
  SeriesInputSettingsPresenter * parent;

 public:
  FilterModel(SeriesInputSettingsPresenter * parent);
  FilterModel(SeriesInputSettingsPresenter * parent,
      google::protobuf::FieldDescriptor *field_descriptor,
              google::protobuf::Message *reference_message,
              QString value);


  // methods
  bool operator==(const FilterModel & other);
  google::protobuf::FieldDescriptor *get_field_descriptor() const;
  void set_field_descriptor(google::protobuf::FieldDescriptor *field_descriptor);
  google::protobuf::Message *get_reference_message() const;
  void set_reference_message(google::protobuf::Message *reference_message);
  const QString &get_value() const;
  void set_value(const QString &value);
};
#endif //RTT_FILTERMODEL_H
