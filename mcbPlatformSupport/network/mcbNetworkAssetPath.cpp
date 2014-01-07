//
//  mcbNetworkAssetPath.cpp
//  SoundSurfer
//
//  Created by Radif Sharafullin on 1/5/14.
//
//

#include "mcbNetworkAssetPath.h"
#include "mcbDownloadQueue.h"
#include "mcbUnzipQueue.h"
#include "mcbPlatformSupportFunctions.h"

namespace mcb{namespace PlatformSupport{namespace network{
    
    void downloadAndUnzipBundle(const HTTPRequest & request, const std::string & bundlesDirectory, const std::function<void(const std::string & bundlePath, bool success)> & completion, const std::function<void(float progress)> & progress){
    
        static const float kDownloadToUnpackProgressRatio(.7f);
        
        auto setProgressL([=](float p){
            if (progress)
                progress(p);
        });
        
        
        
        std::string bundleHash(Functions::generateRandomAlphanumericString());
        std::string bundlePath(Functions::stringByAppendingPathComponent(bundlesDirectory, bundleHash));
        std::string bundleZipPath(bundlePath+".zip");
        std::string bundleUnZipPath(bundlePath+"/");
        
        auto callCompletionL([=](bool success){
            if (completion)
                completion(bundleUnZipPath, success);
        });
        
        auto cleanupL([=](bool both){
            remove(bundleZipPath.c_str());
            if (both)
                remove(bundleUnZipPath.c_str());
        });
        
        cleanupL(true);
        DownloadQueue::sharedInstance()->enqueueDownload(request, bundleZipPath, [=](NetworkTask::Status status, const HTTPResponse & response){
            
            if (status==NetworkTask::StatusCompleted) {
                UnzipQueue::sharedInstance()->enqueueUnzip(bundleZipPath, bundleUnZipPath, [=](UnzipTask::Status status){
                    
                    if (status==UnzipTask::StatusCompleted) {
                        cleanupL(false);
                        setProgressL(1.f);
                        callCompletionL(true);
                    }else{
                        callCompletionL(false);
                        cleanupL(true);
                    }
                    
                },[=](float prog){//progress
                    setProgressL(kDownloadToUnpackProgressRatio + (1.f-kDownloadToUnpackProgressRatio) * prog);
                });
            }else{
                callCompletionL(false);
                cleanupL(false);
            }
            
        },[=](float prog){//progress
            setProgressL(kDownloadToUnpackProgressRatio * prog);
        });
        
    }
    
    
    
    void NetworkAssetManager::init(){
    
    }
    std::string NetworkAssetManager::resolveNetworkAssetPath(const std::string & path){
        std::string localPath;
        std::string networkURL;
        
        //check the data, see if can find it, if not, return local path, otherwise, return path from data, if exists
        
        //enqeue:
        //compare versions, start download, unzip
        
        //remove previous version, update data
        
    }
    void NetworkAssetManager::loadVersionsWithPath(const std::string & path){
        std::string dataPath(resolveNetworkAssetPath(path));
        
    }
}}}