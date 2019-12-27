//
//  AELoader.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/2.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include <thread>

#include "json.h"
#include "AELoader.h"

using namespace std;

AELoader::~AELoader() {
}

AELoader::AELoader() {
    
}

GLvoid AELoader::operator()(int a) {
    cout<< "HelloWorld : " << a << endl;
}
GLvoid AELoader::reset() {
    
}
GLvoid AELoader::add(string& url) {
    _resources.push_back(_baseURL + url);
}
GLvoid AELoader::load(string& callback) {
}
GLvoid AELoader::handleBaseURL(string& url) {
    _baseURL = AEURLPath(url);
}
