#include "AbstractComponent.h"

int AbstractComponent::s_id = 0;

bool AbstractComponent::operator<(const AbstractComponent& another) const {
    return id < another.id;
}