//
//  mcbIOSUtils.h
//  SoundSurfer
//
//  Created by Radif Sharafullin on 12/24/13.
//
//

#ifndef __mcb__mcbIOSUtils__
#define __mcb__mcbIOSUtils__

#import <Foundation/Foundation.h>
#include <iostream>

#define mcbClassLog(format, ...) NSLog(@((std::string("%@: ")+[format UTF8String]).c_str()), NSStringFromClass(self.class), ##__VA_ARGS__)

typedef void (^MCBGeneralPurposeBlock)();


namespace mcb{namespace PlatformSupport{namespace utils{namespace iOS{
    UIViewController * rootViewController();
    
    std::string platform();
    std::string buildVersion();
    std::string locale();
    std::string language();
    std::string iOSVersion();
    
    struct MemoryInfoInGB{std::string totalMemory, usedMemory, freeMemory;};
    MemoryInfoInGB memoryInGB();
    
    UIImage* takeScreenshot();
    UIImage *scaleImageToSize(UIImage * image, CGSize newSize);
    
}}}}
#endif//__mcb__mcbIOSUtils__