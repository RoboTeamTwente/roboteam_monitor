//
// Created by Lukas Bos on 11/11/2019.
//

#ifndef RTT_FILTER_H
#define RTT_FILTER_H

#include <google/protobuf/descriptor.h>
#include <QString>

struct Filter {
  google::protobuf::FieldDescriptor * field_descriptor;
  QString value;
    Filter()
    : field_descriptor(nullptr), value("") {}
  Filter(google::protobuf::FieldDescriptor * _field_descriptor, QString _value)
  : field_descriptor(_field_descriptor), value(_value) {

  }
};

#endif //RTT_FILTER_H
