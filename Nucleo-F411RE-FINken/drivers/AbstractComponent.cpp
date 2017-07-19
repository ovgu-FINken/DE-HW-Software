#include "AbstractComponent.h"

/**
 * The id for each component will be created in a sequence order staring with 1
 */
int AbstractComponent::s_id = 0;

bool AbstractComponent::operator<(const AbstractComponent& another) const {
    return id < another.id;
}