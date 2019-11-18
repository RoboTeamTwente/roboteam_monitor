#include "SeriesSettingsModel.h"
#include "FilterModel.h"

bool SeriesSettingsModel::operator==(const SeriesSettingsModel &rhs) const {

    bool filters_are_equal = filters.size() == rhs.filters.size() && std::equal(filters.begin(), filters.end(), rhs.filters.begin(),
        [](const FilterPresenter * lhs, const FilterPresenter * rhs) {
          std::cout << "compare left and right: " << std::endl;

          return *lhs == *rhs;
    });

    std::cout << "filters_are_equal: " + std::to_string(filters_are_equal) << std::endl;
    return filters_are_equal &&
        channel_type==rhs.channel_type &&
        show_packet_rate==rhs.show_packet_rate &&
        show_custom_field==rhs.show_custom_field &&
        parent==rhs.parent;
}

bool SeriesSettingsModel::operator!=(const SeriesSettingsModel &rhs) const {
    return !(rhs==*this);
}

SeriesSettingsModel::SeriesSettingsModel(const SeriesSettingsModel &other) {
    std::cout << "[SeriesSettingsModel] Making a copy..." << std::endl;
    channel_type = other.channel_type;
    show_packet_rate = other.show_packet_rate;
    show_custom_field = other.show_custom_field;
    parent = other.parent;

    for (auto filter : other.filters) {
        auto new_filter = new FilterModel(* filter->get_model());
        filters.push_back(new FilterPresenter(new_filter));
    }
}
