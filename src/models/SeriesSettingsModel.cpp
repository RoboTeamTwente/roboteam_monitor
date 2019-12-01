#include "SeriesSettingsModel.h"
#include "FilterModel.h"
#include "presenters/SeriesSettingsPresenter.h"

bool SeriesSettingsModel::operator==(const SeriesSettingsModel &rhs) const {

    bool filters_are_equal = filters.size() == rhs.filters.size() && std::equal(filters.begin(), filters.end(), rhs.filters.begin(),
        [](const FilterPresenter * lhs, const FilterPresenter * rhs) {
          return *lhs == *rhs;
    });

    return filters_are_equal &&
        channel_type==rhs.channel_type &&
        use_packet_rate==rhs.use_packet_rate &&
        parent==rhs.parent;
}

bool SeriesSettingsModel::operator!=(const SeriesSettingsModel &rhs) const {
    return !(rhs==*this);
}

SeriesSettingsModel::SeriesSettingsModel(const SeriesSettingsModel &other, SeriesSettingsPresenter * presenter) {
    std::cout << "[SeriesSettingsModel] Making a copy..." << std::endl;
    channel_type = other.channel_type;
    use_packet_rate = other.use_packet_rate;
    parent = other.parent;
    use_packet_rate = other.use_packet_rate;
    field_to_show = other.field_to_show;

    for (auto filter : other.filters) {
        auto new_filter = new FilterModel(* filter->get_model(), presenter);
        filters.push_back(new FilterPresenter(new_filter));
    }
}
SeriesSettingsModel::SeriesSettingsModel(SeriesPresenter *parent) : parent(parent)
{ }

json SeriesSettingsModel::to_json() {

    // convert the vector of filtermodels* to filtermodel jsons
    std::vector<json> filter_jsons;
    filter_jsons.reserve(filters.size());
    for (auto filter : filters) {
        filter_jsons.push_back(filter->to_json());
    }

    // this field definition might not exist.
    json field_to_show_json = field_to_show ? field_to_show->to_json() : json();

    return {
        {"filters", filter_jsons},
        {"channel_type", (int) channel_type},
        {"use_packet_rate", use_packet_rate},
        {"field_to_show", field_to_show_json},
    };
}

// Constructor to be used when generating from JSON
SeriesSettingsModel::SeriesSettingsModel(SeriesPresenter *parent, json data) {
    this->channel_type = (proto::ChannelType) data.value("channel_type", (int)channel_type);
    this->use_packet_rate = data.value("use_packet_rate", use_packet_rate);

    json field_to_show_json = data["field_to_show"];
    if (!field_to_show_json.is_null()) {
        field_to_show = new FieldDefinition(field_to_show_json);
    }

    for (auto const & filter_json : data["filters"]) {
        auto settings_presenter = new SeriesSettingsPresenter(this);

        auto filter_model = new FilterModel(settings_presenter, filter_json);
        filters.push_back(new FilterPresenter(filter_model));
    }

}
