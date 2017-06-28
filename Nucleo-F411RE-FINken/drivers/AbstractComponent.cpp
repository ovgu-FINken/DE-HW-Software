#include "AbstractComponent.h"

int AbstractComponent::s_id = 0;
/*   *The id for each componeent will be created in a sequence odrder staring with 0
     * Overloaded comparison operator '<'
     *
     * @param another component for comparison
     * @return true if id is smaller then the id of another component
*/

bool AbstractComponent::operator<(const AbstractComponent& another) const {
    return id < another.id;
}