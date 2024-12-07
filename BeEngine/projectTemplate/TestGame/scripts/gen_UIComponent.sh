if [ -z "$1" ]; then
    echo "Usage: $0 <ComponentName>"
    exit 1
fi

COMPONENT_NAME=$1
COMPONENT_NAME_NCAPITAL=$(echo "$(tr '[:upper:]' '[:lower:]' <<< "${COMPONENT_NAME:0:1}")${COMPONENT_NAME:1}")
HEADER_FILE="${COMPONENT_NAME_NCAPITAL}.h"
SOURCE_FILE="${COMPONENT_NAME_NCAPITAL}.c"

cat << EOT >> ../src/$HEADER_FILE
#pragma once

#include "uiCanvas.h"
#include "uiComponent.h"

DEFINE_UICOMPONENT_START(${COMPONENT_NAME});
// Custom variables
DEFINE_UICOMPONENT_END(${COMPONENT_NAME});
EOT

cat << EOT >> ../src/$SOURCE_FILE
#include "${HEADER_FILE}"

#include "uiCanvas.h"

void _${COMPONENT_NAME}_registered(${COMPONENT_NAME} *comp, UICanvas *canvas) {
}

void _${COMPONENT_NAME}_tick(${COMPONENT_NAME} *comp, UICanvas *canvas) {
}

void _${COMPONENT_NAME}_draw(${COMPONENT_NAME} *comp, UICanvas *canvas) {
}

void _${COMPONENT_NAME}_destroyed(${COMPONENT_NAME} *comp, UICanvas *canvas) {
}

void _${COMPONENT_NAME}_clicked(${COMPONENT_NAME} *comp, UICanvas *canvas) {
}

void _${COMPONENT_NAME}_pressed(${COMPONENT_NAME} *comp, UICanvas *canvas) {
}

void _${COMPONENT_NAME}_released(${COMPONENT_NAME} *comp, UICanvas *canvas) {
}

void _${COMPONENT_NAME}_hovered(${COMPONENT_NAME} *comp, UICanvas *canvas) {
}

void _${COMPONENT_NAME}_unhovered(${COMPONENT_NAME} *comp, UICanvas *canvas) {
}
EOT

echo "Generated \"${HEADER_FILE}\" and \"${SOURCE_FILE}\"."