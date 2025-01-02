#include "uiCanvas.h"

#include "engineCore.h"
#include "list.h"
#include "logger.h"

void _uiCanvas_attachUIComponent(UICanvas *canvas, void *uiComponent) {
    LIST_ADD(canvas->uiComponents, void *, uiComponent);

    void (*event_registered)(void *, UICanvas *) = *(void (**)(void *, UICanvas *))(uiComponent);
    if (event_registered != NULL) {
        event_registered(uiComponent, canvas);
    }
}