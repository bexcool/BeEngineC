if [ -z "$1" ]; then
    echo "Usage: $0 <ComponentName>"
    exit 1
fi

COMPONENT_NAME=$1
COMPONENT_NAME_NCAPITAL=$(echo "$(tr '[:upper:]' '[:lower:]' <<< "${COMPONENT_NAME:0:1}")${COMPONENT_NAME:1}")
HEADER_FILE="${COMPONENT_NAME_NCAPITAL}.h"
SOURCE_FILE="${COMPONENT_NAME_NCAPITAL}.c"

cat << EOT >> ../include/$HEADER_FILE
#pragma once
#include "gameObjectComponent.h"

DEFINE_GAMEOBJECTCOMP_START(${COMPONENT_NAME});
// Custom variables
DEFINE_GAMEOBJECTCOMP_END(${COMPONENT_NAME});
EOT

cat << EOT >> ../src/$SOURCE_FILE
#include "${HEADER_FILE}"

#include "engineApi.h"
#include "engineCore.h"

BEENGINE_API void _${COMPONENT_NAME}_registered(${COMPONENT_NAME} *comp, GameObject *parent) {

}

BEENGINE_API void _${COMPONENT_NAME}_tick(${COMPONENT_NAME} *comp, GameObject *parent) {

}

BEENGINE_API void _${COMPONENT_NAME}_draw(${COMPONENT_NAME} *comp, GameObject *parent) {

}

BEENGINE_API void _${COMPONENT_NAME}_destroyed(${COMPONENT_NAME} *comp, GameObject *parent) {

}
EOT

echo "Generated \"${HEADER_FILE}\" and \"${SOURCE_FILE}\"."