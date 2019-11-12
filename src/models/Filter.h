#ifndef RTT_FILTER_H
#define RTT_FILTER_H

#include <google/protobuf/descriptor.h>
#include <QString>
#include <QMetaType>

class Filter {
 private:
  google::protobuf::FieldDescriptor *field_descriptor = nullptr;
  QString value = "";

 public:
  Filter() = default;
  Filter(const Filter &other);
  ~Filter();
  Filter(google::protobuf::FieldDescriptor *field_descriptor, QString value);

  google::protobuf::FieldDescriptor *get_field_descriptor() const;
  void set_field_descriptor(google::protobuf::FieldDescriptor *field_descriptor);
  const QString &get_value() const;
  void set_value(const QString &value);
};
Q_DECLARE_METATYPE(Filter);
QDebug operator<<(QDebug dbg, const Filter &filter);

#endif //RTT_FILTER_H
