//
//  VoodooInputEngine.cpp
//  VoodooInputEngine
//
//  Created by Kishor Prins on 2019-08-03.
//  Copyright © 2019 Kishor Prins. All rights reserved.
//

#include "VoodooInputEngine.hpp"
#include "Headers/VoodooInput/VoodooInputMessages.h"

#define super VoodooI2CMultitouchEngine
OSDefineMetaClassAndStructors(VoodooInputEngine, VoodooI2CMultitouchEngine);

UInt8 VoodooInputEngine::getScore() {
    return 0x1;
}

MultitouchReturn VoodooInputEngine::handleInterruptReport(VoodooI2CMultitouchEvent event, AbsoluteTime timestamp) {
    
    return MultitouchReturnBreak;
}

bool VoodooInputEngine::start(IOService *provider) {
    if (!super::start(provider)) {
        return false;
    }
    
    parentProvider = NULL;
    parentProvider = OSDynamicCast(VoodooI2CMultitouchInterface, provider);
    
    if (!parentProvider) {
        return false;
    }
    
    voodooInputInstance = NULL;
    
    
    setProperty(VOODOO_INPUT_LOGICAL_MAX_X_KEY, parentProvider->logical_max_x, 32);
    setProperty(VOODOO_INPUT_LOGICAL_MAX_Y_KEY, parentProvider->logical_max_y, 32);
    
    setProperty(VOODOO_INPUT_PHYSICAL_MAX_X_KEY, parentProvider->physical_max_x, 32)VOODOO_INPUT_PHYSICAL_MAX_Y_KEY
    setProperty(VOODOO_INPUT_PHYSICAL_MAX_Y_KEY, parentProvider->physical_max_y, 32);;
    
    setProperty(kIOFBTransformKey, 0ull, 32);
    setProperty("VoodooInputSupported", kOSBooleanTrue);
    
    return true;
}

bool VoodooInputEngine::handleOpen(IOService *forClient, IOOptionBits options, void *arg) {
    if (forClient && forClient->getProperty(VOOODOO_INPUT_IDENTIFIER)) {
        voodooInputInstance = forClient;
        voodooInputInstance->retain();
        
        return true;
    }
    
    return super::handleOpen(forClient, options, arg);
}

void VoodooInputEngine::handleClose(IOService *forClient, IOOptionBits options) {
    OSSafeReleaseNULL(voodooInputInstance);
    super::handleClose(forClient, options);
}
