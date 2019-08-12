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
    
    if (!voodooInputInstance) {
        return MultitouchReturnContinue;
    }
    
    VoodooInputEvent message;
    
    message.timestamp = timestamp;
    message.contact_count = event.contact_count;
    
    for(int i = 0; i < event.contact_count; i++) {
        VoodooI2CDigitiserTransducer* transducer = (VoodooI2CDigitiserTransducer*) event.transducers->getObject(i);
        
        VoodooInputTransducer* inputTransducer = &message.transducers[i];
        
        if (!transducer) {
            continue;
        }
        
        inputTransducer->id = transducer->id;
        inputTransducer->secondaryId = transducer->secondary_id;
        
        inputTransducer->type = VoodooInputTransducerType::FINGER;
        
        inputTransducer->isValid = transducer->is_valid;
        inputTransducer->isTransducerActive = transducer->tip_switch.value();
        inputTransducer->isPhysicalButtonDown = transducer->physical_button.value();
        
        inputTransducer->currentCoordinates.x = transducer->coordinates.x.value();
        inputTransducer->previousCoordinates.x = transducer->coordinates.x.last.value;
        
        inputTransducer->currentCoordinates.y = transducer->coordinates.y.value();
        inputTransducer->previousCoordinates.y = transducer->coordinates.y.last.value;

        // TODO: does VoodooI2C know width(s)? how does it measure pressure?
        inputTransducer->currentCoordinates.width = transducer->tip_pressure.value() / 2;
        inputTransducer->previousCoordinates.width = transducer->tip_pressure.last.value / 2;

        inputTransducer->currentCoordinates.pressure = transducer->tip_pressure.value();
        inputTransducer->previousCoordinates.pressure = transducer->tip_pressure.last.value;
    }
    
    super::messageClient(kIOMessageVoodooInputMessage, voodooInputInstance, &message, sizeof(VoodooInputEvent));
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
    
    setProperty(VOODOO_INPUT_PHYSICAL_MAX_X_KEY, parentProvider->physical_max_x * 10, 32);
    setProperty(VOODOO_INPUT_PHYSICAL_MAX_Y_KEY, parentProvider->physical_max_y * 10, 32);
    
    setProperty(kIOFBTransformKey, 0ull, 32);
    setProperty("VoodooInputSupported", kOSBooleanTrue);
    
    return true;
}

bool VoodooInputEngine::handleOpen(IOService *forClient, IOOptionBits options, void *arg) {
    if (forClient && forClient->getProperty(VOODOO_INPUT_IDENTIFIER)) {
        voodooInputInstance = forClient;
        voodooInputInstance->retain();
        
        return true;
    }
    
    return super::handleOpen(forClient, options, arg);
}

void VoodooInputEngine::stop(IOService *provider) {
    super::stop(provider);
}

void VoodooInputEngine::handleClose(IOService *forClient, IOOptionBits options) {
    OSSafeReleaseNULL(voodooInputInstance);
    super::handleClose(forClient, options);
}
