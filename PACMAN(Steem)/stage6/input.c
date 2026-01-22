#include <osbind.h>
#include "input.h"

/* Returns the key pressed, or 0 if no key is waiting */
int read_key()
{
    if (Cconis())      /* key available? */
        return Cnecin();  /* read now */
    
    return 0;          /* no key */
}
