//
//  VoodooInputEngine.hpp
//  VoodooInputEngine
//
//  Created by Kishor Prins on 2019-08-03.
//  Copyright © 2019 Kishor Prins. All rights reserved.
//

#ifndef VoodooInputEngine_hpp
#define VoodooInputEngine_hpp

#include <IOKit/IOService.h>
#include "Headers/VoodooI2C/VoodooI2CMultitouchInterface.hpp"
#include "Headers/VoodooI2C/VoodooI2CMultitouchEngine.hpp"

#ifndef EXPORT
#define EXPORT __attribute__((visibility("default")))
#endif

class VooodooI2CMultitouchInterface;

class EXPORT VoodooInputEngine : public VoodooI2CMultitouchEngine {
    OSDeclareDefaultStructors(VoodooInputEngine);
    
    VoodooI2CMultitouchInterface* parentProvider;
    IOService* voodooInputInstance;
public:
    UInt8 getScore() override;
    MultitouchReturn handleInterruptReport(VoodooI2CMultitouchEvent event, AbsoluteTime timestamp) override;

    bool start(IOService* provider) override;
    void stop(IOService* provider) override;

    bool handleOpen(IOService *forClient, IOOptionBits options, void *arg) override;
    void handleClose(IOService *forClient, IOOptionBits options) override;
};

#endif /* VoodooInputEngine_hpp */
