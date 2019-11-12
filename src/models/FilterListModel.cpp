//
// Created by Lukas Bos on 12/11/2019.
//

#include <src/utilities/Helpers.h>
#include "FilterListModel.h"

FilterListModel::FilterListModel(QObject * parent) : QAbstractListModel(parent) { }

/*
 * QT data override for Model/View design pattern
 */
QVariant FilterListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();
    auto filter = filters.at(index.row());

    // return the name for displaying
    if (role == Qt::DisplayRole) {
        return Helpers::get_actual_typename(filter.get_field_descriptor());
    }

    // return the full filter
    if (role == Qt::EditRole) {
        return QVariant::fromValue(filter);
    }

    return QVariant();
}

/*
 * QT data override for Model/View design pattern
 */
int FilterListModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : filters.size();
}

/*
 * Append a filter to the list
 */
void FilterListModel::addFilter(Filter filter) {
    filters.push_back(filter);
}


