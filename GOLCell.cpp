#include "GOLCell.h"
#include "Rect2D.h"

/*
* Old, disused class, ignore
*/


GOLCell::GOLCell() {
    this->alive = false;
    this->square = Rect2D(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0));
}

GOLCell::GOLCell(bool lifeStatus) {
    this->alive = lifeStatus;
    this->square = Rect2D(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0));
}

GOLCell GOLCell::checkForLife(GOLCell*)
{

    return GOLCell(false);
}
