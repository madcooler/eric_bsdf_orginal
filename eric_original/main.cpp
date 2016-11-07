//
//  main.cpp
//  eric_original
//
//  Created by Administrator on 07/11/2016.
//  Copyright © 2016 Chi Wang. All rights reserved.
//

#include <iostream>
#include "basic.h"
#include "MicrosurfaceScattering.h"


#include "test_masking.h"
#include "test_normalization_bsdf.h"
#include "test_single_scattering.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //test_masking();
    //test_normalization_bsdf();
    test_single_scattering();
    return 0;
}
