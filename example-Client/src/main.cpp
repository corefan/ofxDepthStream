// OF
#include "ofMain.h"
// addons
#include "ofxDepthStream/ofxDepthStream.h"

class ofApp : public ofBaseApp{

  public: // methods
    void setup() override;
    void update() override;
    void draw() override;

  private: // attributes
    std::string remoteCamAddress = "persee.local"; //"192.168.1.226"; // "127.0.0.1";
    int depthPort = 4445;
    int colorPort = 4446;

    depth::ReceiverRef depthReceiverRef, colorReceiverRef;
    ofTexture depthTex, colorTex;
};

void ofApp::setup() {
  ofSetWindowShape(1280,480);
  // create tcp network receivers for both the depth and the color stream
  depthReceiverRef = depth::Receiver::createAndStart(remoteCamAddress, depthPort);
  colorReceiverRef = depth::Receiver::createAndStart(remoteCamAddress, colorPort); // color stream isn't working yet on the transmitter side...
}

void ofApp::update() {
  // checks if our receivers have new data, if so these convenience methods
  // update (and allocate if necessary!) our textures.
  ofxDepthStream::loadDepthTexture(*depthReceiverRef, depthTex);
  ofxDepthStream::loadColorTexture(*colorReceiverRef, colorTex);
}

void ofApp::draw() {
  ofBackground(0);

  if(depthTex.isAllocated()) {
    depthTex.draw(0, 0);
  }

  if(colorTex.isAllocated()) {
    colorTex.draw(640, 0);
  }
}

//========================================================================

int main(int argc, char** argv){
  ofSetupOpenGL(800, 600, OF_WINDOW);
  ofRunApp(new ofApp());
}
