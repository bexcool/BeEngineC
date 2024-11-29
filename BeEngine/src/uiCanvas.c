#include "uiCanvas.h"

#include "array.h"
#include "engineCore.h"

void uiCanvas_attachUIComponent(UICanvas *canvas, void *uiComponent) {
    ARRAY_ADD(getCore()->allUICanvases, void *, uiComponent);

    void (*event_registered)(void *, UICanvas *) = *(void (**)(void *, UICanvas *))(uiComponent);
    if (event_registered != NULL) {
        event_registered(uiComponent, canvas);
    }
}