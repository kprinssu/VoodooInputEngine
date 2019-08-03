//
//  VoodooInputMessages.h
//  VooodooInput
//
//  Created by Kishor Prins on 2019-07-20.
//  Copyright © 2019 Kishor Prins. All rights reserved.
//

#ifndef VOODOO_INPUT_MESSAGES_H
#define VOODOO_INPUT_MESSAGES_H

#define VOOODOO_INPUT_IDENTIFIER "VoodooInput Instance"

#define VOODOO_INPUT_TRANSFORM_KEY "IOFBTransform"
#define VOODOO_INPUT_LOGICAL_MAX_X_KEY "Logical Max X"
#define VOODOO_INPUT_LOGICAL_MAX_Y_KEY "Logical Max Y"
#define VOODOO_INPUT_PHYSICAL_MAX_X_KEY "Physical Max X"
#define VOODOO_INPUT_PHYSICAL_MAX_Y_KEY "Physical Max Y"

#define VOODOO_INPUT_MAX_TRANSDUCERS 10
#define kIOMessageVoodooInputMessage 12345

#define kVoodooInputTransducerFingerType 1
#define kVoodooInputTransducerStylusType 2

#include "VoodooInputTransducer.h"
#include "VoodooInputEvent.h"

#endif /* VoodooInputMessages_h */
