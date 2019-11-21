#include "SeriesModel.h"
#include "SeriesSettingsModel.h"
#include <QtCharts/QtCharts>

using namespace google::protobuf;

SeriesModel::SeriesModel(ChartPresenter * parent, const QString & name): parent(parent) {
    time_since_series_is_created = timer.getCurrentTime().count();
    qt_series = new QLineSeries();
    qt_series->setName(name);
    data = new QVector<QPointF>();
    auto settings = new SeriesSettingsModel(new SeriesPresenter(this));
    settings_presenter = new SeriesSettingsPresenter(settings);
    init_subscriber_for_channel_type(proto::ChannelType::GEOMETRY_CHANNEL);
}


void SeriesModel::init_subscriber_for_channel_type(const proto::ChannelType & channel_type) {
    if (!proto_subscriber) {

        proto_subscriber = reinterpret_cast<proto::Subscriber<google::protobuf::Message> *>
            (new proto::Subscriber<proto::RobotCommand>(
                proto::ROBOT_COMMANDS_PRIMARY_CHANNEL,
                &SeriesModel::handle_incoming_message,
                this));
    }



    std::cerr << "[SeriesModel:init_subscriber_for_channel_type] temporarily only allowing one type of publisher" << std::endl;
}


/*
 *
 * This function currently applies every setting available to the incoming messages.
 * - applying filters
 * - measuring rate
 * - forwarding output
 *
 */
template<class T>
void SeriesModel::handle_incoming_message(T message) {

    auto reflection = const_cast<google::protobuf::Reflection *>(message.GetReflection());
    auto current_time = roboteam_utils::Timer::getCurrentTime();
    auto refl = const_cast<Reflection *>(reflection);

    // apply filters
    auto field_descriptors = std::vector<const google::protobuf::FieldDescriptor *>();
    reflection->ListFields(message, &field_descriptors);

    for (auto filter : settings_presenter->get_filters()) {
        // if the filter is empty do nothing
        if (!filter->get_field_definition() || !filter->get_field_definition()->get_field_descriptor() || filter->get_value().isEmpty()) break;

        if (filter->get_field_definition()->get_field_descriptor()->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT32) {
            int value = reflection->GetUInt32(message, filter->get_field_definition()->get_field_descriptor());
            if (QString::number(value, 10) != filter->get_value()) return;
        } else {
            return;
        }
    }

    // handle rate
    auto now = timer.getCurrentTime();
    determine_packet_rate();



    if (settings_presenter->use_packet_rate()) {
        QPoint point((now.count() - parent->get_time_chart_created())/1000.0, rate);
        data->append(point);
        parent->adjustBoundaries(point.x(), point.y(), 10);
    }

    double value = 0.0;

    // handle custom fields
    if (!settings_presenter->use_packet_rate()) {
        if (settings_presenter->get_field_to_show()) {

            google::protobuf::Message * msg = &message;
            auto field_definition = settings_presenter->get_field_to_show();
            auto desc = message.GetDescriptor();
            auto field = const_cast<FieldDescriptor *>(field_definition->get_field_descriptor());
            for (int index : field_definition->get_field_numbers()) {
                field = const_cast<FieldDescriptor *>(desc->field(index));
                refl = const_cast<google::protobuf::Reflection *>(msg->GetReflection());

                if (field) {
                    desc = field->message_type();
                    if (field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE) {
                        msg = const_cast<Message *>(&refl->GetMessage(*msg, field));
                    }
                }
            }

        // field->extension_scope()->FindNestedTypeByName(field->na
        switch(field->cpp_type()) {
            case FieldDescriptor::CPPTYPE_INT32: {
                value = refl->GetInt32(*msg, field);
                break;
            }
            case FieldDescriptor::CPPTYPE_UINT32: {
                value = refl->GetUInt32(*msg, field);
                break;
            }
            case FieldDescriptor::CPPTYPE_INT64: {
                value = refl->GetInt64(*msg, field);
                break;
            }
            case FieldDescriptor::CPPTYPE_UINT64: {
                value = refl->GetUInt64(*msg, field);
                break;
            }
            case FieldDescriptor::CPPTYPE_FLOAT: {
                value = refl->GetFloat(*msg, field);
                break;
            }
            case FieldDescriptor::CPPTYPE_DOUBLE: {
                value = refl->GetDouble(*msg, field);
                break;
            }
            default: return;

        }

        qreal time = (now.count() - parent->get_time_chart_created());
        QPoint point(time, value);
        parent->adjustBoundaries(point.x(), point.y(), 10);
        data->append(point);
        }
    }
}
void SeriesModel::determine_packet_rate() {
    if (timer.getCurrentTime().count() <= lastRateUpdateTime + 1000) {
        internal_rate++;
    } else {
        lastRateUpdateTime = timer.getCurrentTime().count();
        rate = internal_rate;
        internal_rate = 0;
    }
}

ChartPresenter *SeriesModel::get_parent() const {
    return parent;
}
SeriesModel::~SeriesModel() {
    /*
     * Ignore the clang-tidy warning here.
     * clang-tidy thinks proto_subscriber == nullptr, but it is not.
     */

    // NOLINTNEXTLINE
    if (proto_subscriber) {
        delete proto_subscriber;
    }
}


