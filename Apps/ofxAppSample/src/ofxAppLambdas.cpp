//
//  ofxAppLambdas.cpp
//  BaseApp
//
//  Created by Oriol Ferrer Mesià on 12/8/16.
//
//

#include "ofxAppLambdas.h"
#include "CWRU_Object.h"

ofxAppLambdas::ofxAppLambdas(){

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/// CWRU ////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////


	// Locate Object List in JSON user lambda //////////////////////////////////////////////////////
	cwru.describeJsonUserLambda = [](ofxMtJsonParserThread::JsonStructureData & inOutData){
		ofxJSONElement & jsonRef = *(inOutData.fullJson);
		if(jsonRef["data"].isObject()){
			inOutData.objectArray = (ofxJSONElement*) &(jsonRef["data"]);
		}else{

			ofLogError("ofApp") << "JSON has unexpected format!";
			//if the json is not what we exepcted it to be, let the parser know by filling it the data like this:
			inOutData.objectArray = NULL;
		}
	};

	// Parse Single JSON Object user lambda ////////////////////////////////////////////////////////
	cwru.parseSingleObjectUserLambda = [](ofxMtJsonParserThread::SingleObjectParseData & inOutData){

		const ofxJSONElement & jsonRef = *(inOutData.jsonObj); //pointers mess up the json syntax somehow

		string title, description, imgURL, imgSha1;

		try{ //do some parsing - catching exceptions
			title = ofxMtJsonParserUtils::initFromJsonString(jsonRef, "title", false, inOutData.printMutex);
			description = ofxMtJsonParserUtils::initFromJsonString(jsonRef, "description", false, inOutData.printMutex);
			imgURL = jsonRef["image"]["uri"].asString();
			imgSha1 = jsonRef["image"]["chksum"].asString();
		}catch(Exception exc){
			inOutData.printMutex->lock();
			ofLogError("ofApp") << exc.what() << " " << exc.message() << " " << exc.displayText() << " WHILE PARSING OBJ " << inOutData.objectID;
			inOutData.printMutex->unlock();
		}

		CWRU_Object * o = new CWRU_Object();
		o->title = title;
		o->description = description;
		inOutData.objectID; //in this case we dont need to set the objectID back to the parser
							//bc this json happens to be a dictionary, not a list... so its
							//smart enough to get it from there.

		// ASSET HOLDER SETUP //
		//setup our AssetHoler structures - we need to know where to download the assets to,
		//our download and usage policies, and what assets do we own
		static string assetsDir;
		if(assetsDir.size() == 0) assetsDir = app.getString("content/JsonSources/CWRU/assetsLocation"); //TODO this is slooow!
		string assetsPath = assetsDir + "/" + inOutData.objectID;

		ofxAssets::DownloadPolicy assetDownloadPolicy = app.getAssetDownloadPolicy();
		ofxAssets::UsagePolicy assetUsagePolicy = app.getAssetUsagePolicy();
		o->AssetHolder::setup(assetsPath, assetUsagePolicy, assetDownloadPolicy);

		if(imgURL.size()){
			o->imagePath = o->addRemoteAsset(imgURL, imgSha1);
		}

		inOutData.object = dynamic_cast<ParsedObject*> (o); //this is how we "return" the object to the parser;
	};


	// Setup Textured Objects User Lambda /////////////////////////////////////////////////////////
	cwru.setupTexturedObjectUserLambda = [](ContentObject * texuredObject){

		CWRU_Object * to = (CWRU_Object*)texuredObject; //cast to our obj type

		int numAssets = to->getNumAssets(); //this will always be 1 for this example, 1 img per object

		//assets are owned by my extended object "AssetHolder"
		to->TexturedObject::setup(numAssets, TEXTURE_MEDIUM); //we only use one tex size, so lets choose medium
		to->TexturedObject::setResizeQuality(CV_INTER_AREA); //define resize quality (in case we use mipmaps)
		ofPixels pix;

		for(int i = 0; i < numAssets; i++){
			ofxAssets::Descriptor & d = to->getAssetDescAtIndex(i);

			switch (d.type) {
				case ofxAssets::VIDEO: break; //you might want to handle video thumbnails here?
				case ofxAssets::IMAGE:{
					//preload images once, to find out their dimensions that we need to know beforehand
					//for the Progressive texture loader to alloc b4 loading
					//TODO! cms should provide img dimensions to avoid startup overhead!

					if(ofLoadImage(pix, d.relativePath)){
						to->imgSize = ofVec2f(pix.getWidth(), pix.getHeight());
					}else{
						ofLogError("TexturedObject") << "cant load image at " << d.relativePath;
					}
					break;
				}
				default: break;
			}
		}
	};

}
