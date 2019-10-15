float[] start;
float[] end;

float innerR=70;
float outterR=400;
int flowerSeg=30;
int flowerStep=300;


int bgLines=1000;
int bgLineSeg=20;

color bgColor=color(150,0,0);
color stColor=color(50,50);
void setup(){
  size(2048,2048);
  noLoop();
}
void draw(){
  drawBG();
  drawFlower();
  
}
void drawBG(){
  background(bgColor);
  noFill();
  stroke(stColor);
  float stWeight=width/bgLines;
  strokeWeight(stWeight*8);
  
  for(int i=0;i<bgLines;i++){
    float xBase=width*i/bgLines;
    beginShape();
    curveVertex(xBase,0);
    
    for(int j=0;j<bgLineSeg;j++){
       float y=height*j/bgLineSeg;
       float x=xBase+stWeight*randomGaussian();
       curveVertex(x,y);
    }
    
    curveVertex(xBase,height);
    curveVertex(xBase,height);
    endShape();
  }
}
void drawFlower(){
  stroke(240,240,210);
  strokeWeight(1);
  setArrays(0.4f,2);
  for(int i=0;i<flowerStep;i++){
    beginShape();
    float xfin=0;
    float yfin=0;
    for(int j=0;j<flowerSeg;j++){
      float n=i/(float)flowerStep;
      float m=(flowerStep-i)/(float)flowerStep;
      float r=start[j]*m+end[j]*n;
      float x=ort2cartx(j*2*PI/flowerSeg,r);
      float y=ort2carty(j*2*PI/flowerSeg,r);
      xfin=x+60*sin(i/100)+width/2;
      yfin=y+60*cos(i/100)+height/2;
      curveVertex(xfin,yfin);
    }
    curveVertex(xfin,yfin);
    endShape(CLOSE);
  }
}
void setArrays(float rndConstant, float stable){
  start=new float[flowerSeg];
  end=new float[flowerSeg];
  for(int i=0;i<flowerSeg;i++){
    start[i]=innerR*(rndConstant*randomGaussian()+stable);
    end[i]=outterR*(rndConstant*randomGaussian()+stable);
  }
}
float ort2cartx(float deg, float radius){
   return radius*sin(deg);
}
float ort2carty(float deg, float radius){
   return radius*cos(deg);
}
