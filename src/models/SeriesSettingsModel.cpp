#include "SeriesSettingsModel.h"
#include "FilterModel.h"

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

SeriesSettingsModel::SeriesSettingsModel(const SeriesSettingsModel &other) {
    std::cout << "[SeriesSettingsModel] Making a copy..." << std::endl;
    channel_type = other.channel_type;
    use_packet_rate = other.use_packet_rate;
    parent = other.parent;
    use_packet_rate = other.use_packet_rate;
    field_to_show = other.field_to_show;

    for (auto filter : other.filters) {
        auto new_filter = new FilterModel(* filter->get_model());
        filters.push_back(new FilterPresenter(new_filter));
    }
}
SeriesSettingsModel::SeriesSettingsModel(SeriesPresenter *parent) : parent(parent)
{ }
