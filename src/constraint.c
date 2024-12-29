#include "constraint.h"

#include "brush.h"
#include "transform.h"
#include "vector2.h"

Vector2 constraint_apply(Transform* parentTrans, Transform* childTrans, Thickness* margin, ConstraintType horizontal, ConstraintType vertical) {
    Vector2 result = VECTOR2_ZERO;

    switch (horizontal) {
        case CONSTRAINT_RELATIVE: {
            result.x = parentTrans->position.x + childTrans->position.x;
            break;
        }

        case CONSTRAINT_CENTERED: {
            result.x = parentTrans->position.x + (parentTrans->size.x / 2) - (childTrans->size.x / 2) + margin->left - margin->right;
            break;
        }

        case CONSTRAINT_START: {
            result.x = parentTrans->position.x + margin->left;
            break;
        }

        case CONSTRAINT_END: {
            result.x = parentTrans->position.x + parentTrans->size.x - childTrans->size.x - margin->right;
            break;
        }
    }

    switch (vertical) {
        case CONSTRAINT_RELATIVE: {
            result.y = parentTrans->position.y + childTrans->position.y;
            break;
        }

        case CONSTRAINT_CENTERED: {
            result.y = parentTrans->position.y + (parentTrans->size.y / 2) - (childTrans->size.y / 2) + margin->top - margin->bottom;
            break;
        }

        case CONSTRAINT_START: {
            result.y = parentTrans->position.y + margin->top;
            break;
        }

        case CONSTRAINT_END: {
            result.y = parentTrans->position.y + parentTrans->size.y - childTrans->size.y - margin->bottom;
            break;
        }
    }

    return result;
}