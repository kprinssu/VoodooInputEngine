//
//  VoodooInputEngine.c
//  VoodooInputEngine
//
//  Created by Kishor Prins on 2019-08-03.
//  Copyright © 2019 Kishor Prins. All rights reserved.
//

#include <mach/mach_types.h>

kern_return_t VoodooInputEngine_start(kmod_info_t * ki, void *d);
kern_return_t VoodooInputEngine_stop(kmod_info_t *ki, void *d);

kern_return_t VoodooInputEngine_start(kmod_info_t * ki, void *d)
{
    return KERN_SUCCESS;
}

kern_return_t VoodooInputEngine_stop(kmod_info_t *ki, void *d)
{
    return KERN_SUCCESS;
}
