openFrameworks addons should be added as submodules in this folder. These addons should be forked into the Local Projects account in the event that the original author removes their repository, and so that we can maintain project-specific code. 

To Add an Addon:

```
#from the repo root!
git submodule add https://github.com/local-projects/ofxTimeMeasurements.git ExternalAddons/ofxTimeMeasurements
cd ExternalAddons/ofxTimeMeasurements
git status
```