//PF COURE Project by Hamza Aamer 21I-0415
//============================================================================
// Name        : Hamza Aamer
// Author      : FAST CS Department
// Roll no     : 21I-0415
// Copyright   : (c) Reserved
// Description : Basic 2D game of Rush Hour...
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include<time.h>
#include<ctime>
#include<cmath>
using namespace std;

int scorecount=0; 	//ALL GLOBAL VARIABLES
int destinationx;
int destinationy;
int xI = 0, yI = 975;

int taxix[100];
int taxiy[100];

int obstaclex[20];
int obstacley[20];

int taxidirection[100];

int building[2][100];
int personx[3];
int persony[3];
int personpicked[3]={0,0,0};
int persondropped=0;

int starttime=time(0);

int colorpick;		
bool spikeflag;
string username;

void buildinglocations(){			//FUNCTION TO DETERMINE LOCATIONS OF BUILDINGS
    int x=0;
    int y[10];
    int vert;
    if ((rand()%2+1)==1) vert=50;
    else vert=0;
    for (int a=0;a<10;a++)
    {
    if (rand()%2==1)
    y[a]=-50;
    else y[a]=-100;}
for (int a=0;a<10;a++){
x=vert;
for (int c=0;c<10;c++)
y[c]+=100;
for (int b=0;b<10;b++){
building[0][b+(a*10)]=x;
building[1][b+(a*10)]=y[b];
x+=100;
}
}

for (int a=0;a<10;a++){	
for (int b=0;b<10;b++){
if ((building[0][b+(a*10)]==xI && building[1][b+(a*10)]+25==yI)){
building[1][b+(a*10)]-=100;
}
}
}

}


bool buildingcheck(int xaxis,int yaxis){ //FUNCTION TO CHECK IF THE COORDINATES ARE INSIDE BUILDING
bool flag=0;
for (int x=0;x<100;x++){
if ((xaxis==building[0][x] && yaxis==building[1][x]) || (xaxis==building[0][x]+25 && yaxis==building[1][x]) || (xaxis==building[0][x] && yaxis==building[1][x]+25) || (xaxis==building[0][x]+25 && yaxis==building[1][x]+25))
flag=1;
}
return flag;
}

void taxilocations(){			//FUNCTION TO DETERMINE TAXI LOCATIONS
for (int z=0;z<100;z++){
taxix[z]=(rand()%36+2)*25;
taxiy[z]=(rand()%36+1)*25;
taxidirection[z]=rand()%2+1;
}
for (int z=0;z<100;z++){
do {
taxix[z]=(rand()%36+1)*25;
taxiy[z]=(rand()%36+1)*25;
} while(buildingcheck(taxix[z],taxiy[z]));

}
}

bool personcheck(int x,int y){	//FUNCTION TO CHECK IF THE COORDINATES ARE SAME AS PERSON LOCATION

bool flag=0;
for (int z=0;z<3;z++){
if (personpicked[z]==1) continue;
if (x==personx[z] && y==persony[z]){
flag=1;
}
}
if (flag==1) return 1;
else return 0;

}


void obstaclelocations(){	//FUNCTION TO GET RANDOM OBSTACLE LOCATIONS
for (int z=0;z<20;z++){
obstaclex[z]=(rand()%38+1)*25;
obstacley[z]=(rand()%38+1)*25;
}

for (int z=0;z<20;z++){
do {
obstaclex[z]=(rand()%38+1)*25;
obstacley[z]=(rand()%38+1)*25;
} while(buildingcheck(obstaclex[z],obstacley[z]) || personcheck(obstaclex[z],obstacley[z]) );
}
}



void drawtaxi(){		//FUNCTION TO DRAW TAXIS
for (int z=0;z<persondropped+1;z++){
    DrawSquare(taxix[z]+4,taxiy[z]+1,6,colors[BLACK]);
    DrawSquare(taxix[z]+15,taxiy[z]+1,6,colors[BLACK]);
    
    DrawSquare(taxix[z]+1,taxiy[z]+5,19,colors[KHAKI]);
    DrawSquare(taxix[z]+5,taxiy[z]+5,19,colors[KHAKI]);
        
    DrawSquare(taxix[z]+4,taxiy[z]+10,10,colors[WHITE]);
    DrawSquare(taxix[z]+11,taxiy[z]+10,10,colors[WHITE]);
    
    DrawSquare(taxix[z]+4,taxiy[z]+7,4,colors[BLUE]);
    DrawSquare(taxix[z]+17,taxiy[z]+7,4,colors[BLUE]);
    glutPostRedisplay();
}
}



void SetCanvasSize(int width, int height) {	//SETTING CANVAS SIZE
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
}



void DrawBuildings(){			//FUNCTION TO DRAW BUILDINGS
for (int a=0;a<100;a++){
DrawSquare(building[0][a] , building[1][a] , 51 , colors[BLACK]);
}

glutPostRedisplay();
}

void DrawPeople(){			//FUNCTION TO DRAW PEOPLE
for (int a=0;a<3;a++){
if (personpicked[a]==1) continue;
DrawLine(personx[a]+12,persony[a]+10,personx[a]+12,persony[a]+21,3,colors[BLACK]);
DrawLine(personx[a]+10,persony[a],personx[a]+12,persony[a]+10,3,colors[BLACK]);
DrawLine(personx[a]+15,persony[a],personx[a]+12,persony[a]+10,3,colors[BLACK]);
DrawLine(personx[a]+10,persony[a]+14,personx[a]+12,persony[a]+20,3,colors[BLACK]);
DrawLine(personx[a]+15,persony[a]+14,personx[a]+12,persony[a]+20,3,colors[BLACK]);

DrawSquare(personx[a]+10,persony[a]+20, 5 , colors[TOMATO]);
}}

void drawObstacles(){			//FUNCTION TO DRAW OBSTACLES
for (int z=0;z<20;z++){
if (spikeflag==1){
DrawTriangle(obstaclex[z],obstacley[z],obstaclex[z]+5,obstacley[z],obstaclex[z]+2,obstacley[z]+10,colors[TOMATO]);
DrawTriangle(obstaclex[z]+5,obstacley[z],obstaclex[z]+10,obstacley[z],obstaclex[z]+7,obstacley[z]+10,colors[TOMATO]);
DrawTriangle(obstaclex[z]+10,obstacley[z],obstaclex[z]+15,obstacley[z],obstaclex[z]+12,obstacley[z]+10,colors[TOMATO]);
DrawTriangle(obstaclex[z]+15,obstacley[z],obstaclex[z]+20,obstacley[z],obstaclex[z]+17,obstacley[z]+10,colors[TOMATO]);
DrawTriangle(obstaclex[z]+20,obstacley[z],obstaclex[z]+25,obstacley[z],obstaclex[z]+22,obstacley[z]+10,colors[TOMATO]);
}
if (spikeflag==0){
DrawTriangle(obstaclex[z],obstacley[z],obstaclex[z]+5,obstacley[z],obstaclex[z]+2,obstacley[z]+20,colors[TOMATO]);
DrawTriangle(obstaclex[z]+5,obstacley[z],obstaclex[z]+10,obstacley[z],obstaclex[z]+7,obstacley[z]+20,colors[TOMATO]);
DrawTriangle(obstaclex[z]+10,obstacley[z],obstaclex[z]+15,obstacley[z],obstaclex[z]+12,obstacley[z]+20,colors[TOMATO]);
DrawTriangle(obstaclex[z]+15,obstacley[z],obstaclex[z]+20,obstacley[z],obstaclex[z]+17,obstacley[z]+20,colors[TOMATO]);
DrawTriangle(obstaclex[z]+20,obstacley[z],obstaclex[z]+25,obstacley[z],obstaclex[z]+22,obstacley[z]+20,colors[TOMATO]);
}


}
}

void drawCar() {			//FUNCTION TO DRAW USER CAR
    
    DrawSquare(xI+4,yI+1,6,colors[BLACK]);
    DrawSquare(xI+15,yI+1,6,colors[BLACK]);
    
    if (colorpick==1){
    DrawSquare(xI+1,yI+5,19,colors[DARK_GOLDEN_ROD]);
    DrawSquare(xI+5,yI+5,19,colors[DARK_GOLDEN_ROD]);
        }
    else if (colorpick==2){
    DrawSquare(xI+1,yI+5,19,colors[RED]);
    DrawSquare(xI+5,yI+5,19,colors[RED]);
    	}
    DrawSquare(xI+4,yI+10,10,colors[WHITE]);
    DrawSquare(xI+11,yI+10,10,colors[WHITE]);
    
    DrawSquare(xI+4,yI+7,4,colors[BLUE]);
    DrawSquare(xI+17,yI+7,4,colors[BLUE]);
    glutPostRedisplay();
}

bool obstaclecheck(int x, int y){//FUNCTION TO CHECK IF THE COORDINATES MATCH WITH THAT OF OBSTACLES AND IF THEYRE OF USER CAR THEN POINTS DEDUCTED
bool flag=0;
for (int z=0;z<20;z++){
if (x==obstaclex[z] && y==obstacley[z]){
flag=1;
}
}
if (flag==1 && xI==x && yI==y){
if (colorpick==1)scorecount-=4;
if (colorpick==2)scorecount-=2;}
return flag;
}


void personlocations(){	//FUNCTIONS TO DETERMINE LOCATION OF PEOPLEa
bool flag;
bool flag2;
do{
do{
personx[0]=rand()%40*25;
persony[0]=rand()%40*25;
flag=buildingcheck(personx[0],persony[0]);
flag2=obstaclecheck(personx[0],persony[0]);
}while(flag || flag2);
do{
personx[1]=rand()%40*25;
persony[1]=rand()%40*25;
flag=buildingcheck(personx[1],persony[1]);
flag2=obstaclecheck(personx[0],persony[0]);
}while(flag || flag2);
do{
personx[2]=rand()%40*25;
persony[2]=rand()%40*25;
flag=buildingcheck(personx[2],persony[2]);
flag2=obstaclecheck(personx[0],persony[0]);
}while(flag || flag2);
}while ( ((personx[0]==personx[1] && persony[0]==persony[1]) || (personx[1]==personx[2] && persony[1]==persony[2]) || (personx[0]==personx[2] || persony[0]==persony[2])));

}


bool flag[100];	//GLOBAL VARIABLE

void moveCarHorizontal(int a) {	//FUNCTION TO MOVE OTHER CARS HORIZONTAL
    bool flagbuilding;
    if (taxix[a] > 10 && flag[a]) {
        taxix[a] -= 25;
        flagbuilding=buildingcheck(taxix[a],taxiy[a]);
    	if ((flagbuilding) || (obstaclecheck(taxix[a],taxiy[a])==1)){
        taxix[a] += 50;
        flag[a] = false;
        }
        if(taxix[a] < 25)
            flag[a] = false;

    }
    else if (taxix[a] < 1000 && !flag[a]) {	

        taxix[a] += 25;
        flagbuilding=buildingcheck(taxix[a],taxiy[a]);
    	if ((flagbuilding) || (obstaclecheck(taxix[a],taxiy[a])==1)){
        taxix[a] -= 50;
        flag[a] = true;
        }
        if (taxix[a] >= 975)
            flag[a] = true;
    }
}

void moveCarVertical(int a) {		//FUNCTION TO MOVE OTHER CARS VERTICAL
    bool flagbuilding;
    if (taxiy[a] > 10 && flag[a]) {
        taxiy[a] -= 25;
        flagbuilding=buildingcheck(taxix[a],taxiy[a]);
    	if ((flagbuilding) || (obstaclecheck(taxix[a],taxiy[a])==1)){
        taxiy[a] += 50;
        flag[a] = false;
        }
        if(taxiy[a] < 25)
            
            flag[a] = false;

    }
    else if (taxiy[a] < 1000 && !flag[a]) {
        taxiy[a] += 25;
        flagbuilding=buildingcheck(taxix[a],taxiy[a]);
    	if ((flagbuilding) || (obstaclecheck(taxix[a],taxiy[a])==1)){
        taxiy[a] -= 50;
        flag[a] = true;
        }
        if (taxiy[a] >= 975)
            flag[a] = true;
    }
}



void GameDisplay(){		//FUNCTION TO DISPLAY SCREEN
  
    glClearColor(0/*Red Component*/, 225,    //148.0/255/*Green Component*/,
            225/*Blue Component*/, 0.5 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
    glClear (GL_COLOR_BUFFER_BIT); //Update the colors
  
    
    DrawSquare(0,0,1000,colors[SILVER]);
    int grid=0;
    for (int x=0;x<=20;x++){
    
    DrawLine(0,0+grid,1000,0+grid,3,colors[BLACK]);
    DrawLine(0+grid,0,0+grid,1000,3,colors[GREEN]);
    grid+=50;
    }
    
    
    DrawBuildings();
    drawtaxi();
    drawObstacles();
    drawCar();
    
    DrawPeople();
    for (int z=0;z<3;z++){
    if (personpicked[z]==1)
    DrawSquare(destinationx,destinationy,25,colors[GREEN]);
    }
    
    int currentsec;
    int currentmin;
    currentsec=180-(time(0)-starttime);
    if (scorecount>=100){
    scorecount+=currentsec;
    cout<<"************YOU WON*************\n";
    cout<<"User : "<<username<<endl;
    cout<<"Your Points: "<<scorecount<<endl;
    cout<<"************YOU WON*************\n\n";
    exit(1);}
    
    
    
    if (currentsec<=0){
    cout<<"************TIMES UP************\n";
    cout<<"User : "<<username<<endl;
    cout<<"Your Points: "<<scorecount<<endl;
    cout<<"************TIMES UP************\n\n";
    exit(1);}
    currentmin=currentsec/60;
    currentsec=currentsec%60;
    string currentseconds=Num2Str(currentsec);
    string currentminutes=Num2Str(currentmin);
    string timer;
    if (currentsec<10)
    timer="Time Left : "+currentminutes+":0"+currentseconds;
    else
    timer="Time Left : "+currentminutes+":"+currentseconds;
    
    
    DrawSquare(1015,620,280,colors[BLACK]);
    DrawSquare(1045,620,280,colors[BLACK]);
    DrawSquare(1020,625,270,colors[OLIVE]);
    DrawSquare(1050,625,270,colors[OLIVE]);
    
    
    string namedisplay="Player : "+username;
    string score=Num2Str(scorecount);
    score="Score : "+score;
    DrawString( 1100, 900, namedisplay, colors[TOMATO]);
    DrawString( 1100, 800, score, colors[TOMATO]);
    DrawString( 1100, 700, timer, colors[TOMATO]);
   
    
    
    glutSwapBuffers(); 

}



bool wallcheck(){	//FUNCTION TO CHECK IF USER IS INSIDE BORDER
if ((xI<0 || xI>=1000 || yI<0 || yI>=1000)){
return 1;}
else return 0;

}



bool taxicheck(int x,int y){		//FUNCTION TO MATCH COORDINATES WITH THOSE OF OTHER CARS
bool flag=0;
for (int z=0;z<persondropped+1;z++){
if (x==taxix[z] && y==taxiy[z]){
flag=1;
}
}
if (flag==1) return 1;
else return 0;
}

void Dropcheck(){	//FUNCTION TO CHECK IF USER IS AS DROP POINT AFTER PICKING UP PERSON
bool flag;
for (int z=0;z<3;z++){
        if (personpicked[z]==1)
        if (xI==destinationx && yI==destinationy){
        scorecount+=10;
        personpicked[z]=0;
        persondropped++;
        do{
        do{
	personx[z]=rand()%40*25;
	persony[z]=rand()%40*25;
	flag=buildingcheck(personx[z],persony[z]);
	}while(flag);
	}while ( ((personx[0]==personx[1] && persony[0]==persony[1]) || (personx[1]==personx[2] && persony[1]==persony[2]) || (personx[0]==personx[2] || 	persony[0]==persony[2])));
        }
        }
}



void NonPrintableKeys(int key, int x, int y) {	//FUNCTION TO CHECK WHEN ARROW KEYS ARE PRESSED
bool flagwall;
bool flagbuilding;
bool flagperson;
bool flagtaxi;

    if (key
            == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
        // what to do when left key is pressed...
        xI -= 25;
        flagwall=wallcheck();
        flagbuilding=buildingcheck(xI,yI);
        flagperson=personcheck(xI,yI);
        flagtaxi=taxicheck(xI,yI);
        obstaclecheck(xI,yI);
        if (flagtaxi) scorecount-=3;
        if (flagperson) scorecount-=5;
        for (int z=0;z<3;z++){
        if (personpicked[z]==1)
        Dropcheck();
        }
        if ((flagwall) || (flagbuilding)){
        xI += 25;
        }
       
        
     } else if (key
            == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
        xI += 25;
        flagwall=wallcheck();
        flagbuilding=buildingcheck(xI,yI);
        flagperson=personcheck(xI,yI);
        flagtaxi=taxicheck(xI,yI);
        obstaclecheck(xI,yI);
        if (flagtaxi){
        if (colorpick==1)scorecount-=2;
        if (colorpick==2)scorecount-=3;}
        if (flagperson) scorecount-=5;
        for (int z=0;z<3;z++){
        if (personpicked[z]==1)
        Dropcheck();
        }
        if ((flagwall) || (flagbuilding)){
        xI -= 25;
        }
        
    } else if (key
            == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
        yI += 25;
        flagwall=wallcheck();
        flagbuilding=buildingcheck(xI,yI);
        flagperson=personcheck(xI,yI);
        flagtaxi=taxicheck(xI,yI);
        obstaclecheck(xI,yI);
        if (flagtaxi){
        if (colorpick==1)scorecount-=2;
        if (colorpick==2)scorecount-=3;}
        if (flagperson) scorecount-=5;
        for (int z=0;z<3;z++){
        if (personpicked[z]==1)
        Dropcheck();
        }
        if ((flagwall) || (flagbuilding)){
        yI -= 25;
        }
    }

    else if (key
            == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
        yI -= 25;
        flagwall=wallcheck();
        flagbuilding=buildingcheck(xI,yI);
        flagperson=personcheck(xI,yI);
        flagtaxi=taxicheck(xI,yI);
        obstaclecheck(xI,yI);
        if (flagtaxi){
        if (colorpick==1)scorecount-=2;
        if (colorpick==2)scorecount-=3;}
        if (flagperson) scorecount-=5;
        for (int z=0;z<3;z++){
        if (personpicked[z]==1)
        Dropcheck();
        }
        if ((flagwall) || (flagbuilding)){
        yI += 25;
        }
    }

    /* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
     * this function*/

    glutPostRedisplay();

}

 void DestinationLocation(){	//FUNCTION TO RANDOMIZE DESTINATION LOCATIONS
do{
destinationx=rand()%20 * 25;
destinationy=rand()%20 * 25;
}while((buildingcheck(destinationx,destinationy)==1) ||  (personcheck(destinationx,destinationy)==1) || (obstaclecheck(destinationx,destinationy)==1) );
}

 
 
void PrintableKeys(unsigned char key, int x, int y) { //FUNCTION TO CHECK IF PERSON CAN BE PICKED OR NOT AFTER PRESSING SPACE
    if (key == 27/* Escape key ASCII*/) {
        exit(1); // exit the program when escape key is pressed.
    }

    if (key == ' ') //Key for picking the passenger
            {
        bool flag=0;
        for (int z=0;z<3;z++){
        if (personpicked[0]==0 && personpicked[1]==0 && personpicked[2]==0 ){
        if ((xI-25==personx[z] && yI-25==persony[z]) || (xI-25==personx[z] && yI==persony[z]) || (xI-25==personx[z] && yI+25==persony[z]) || (xI==personx[z] && yI-25==persony[z]) || (xI==personx[z] && yI==persony[z]) || (xI==personx[z] && yI+25==persony[z]) || (xI+25==personx[z] && yI-25==persony[z]) || (xI+25==personx[z] && yI==persony[z]) || (xI+25==personx[z] && yI+25==persony[z])){
        personpicked[z]=1;
        DestinationLocation();
        }
        }
        }
    }
    glutPostRedisplay();
}

 
 
void Timer(int m) {		//FUNCTION THATS RUN EVERY 1000 FPS
bool flagtaxi;
    // implement your functionality here
    if (spikeflag==0) spikeflag=1;
    
    else if (spikeflag==1) spikeflag=0;
    
    for (int a=0;a<persondropped+1;a++){
    if (taxidirection[a]==1)
    moveCarHorizontal(a);
    else if (taxidirection[a]==2)
    moveCarVertical(a);
    }
	flagtaxi=taxicheck(xI,yI);
        if (flagtaxi) {
        if (colorpick==1)scorecount-=2;
        if (colorpick==2)scorecount-=3;}
    int speedincrease;
    speedincrease=persondropped/2;
    speedincrease*=300;
    if (speedincrease>1900)
    speedincrease=1900;
    
    glutTimerFunc(2000-speedincrease, Timer, 0);
}


void MouseMoved(int x, int y) {
    //cout << x << " " << y << endl;
    glutPostRedisplay();
}



void MouseClicked(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON) // dealing only with left button
            {
        cout << GLUT_DOWN << " " << GLUT_UP << endl;

    } else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
            {
            cout<<"Right Button Pressed"<<endl;

    }
    glutPostRedisplay();
}
 
int main(int argc, char*argv[]) {	//MAIN FUNCTION
	cout<<"WELCOME TO RUSH HOUR BY HAMZA AAMER\n";
	cout<<"Enter Your First Name: ";
	cin>>username;
	cout<<"Please Select the Taxi of your choice: \n";
	cout<<" 1- Yellow:\n\tHitting Flames : -4 points\n\tHitting Another Car : -3 points \n\tHitting A Person : -5 points\n"; 
	cout<<" 2- Red:\n\tHitting Flames : -4 points\n\tHitting Another Car : -2 points \n\tHitting A Person : -5 points\n";
	cout<<"Make a Decision ( 1 | 2 )\n";
	cin>>colorpick;
	srand(time(0));
    int width = 1400, height = 1100; // i have set my window size to be 800 x 600
    buildinglocations();
    personlocations();
    taxilocations();
    obstaclelocations();
    starttime=time(0);
    InitRandomizer(); // seed the random number generator...
    glutInit(&argc, argv); // initialize the graphics library...
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
    glutInitWindowPosition(50, 50); // set the initial position of our window
    glutInitWindowSize(width, height); // set the size of our window
    glutCreateWindow("Rush Hour by Hamza Aamer"); // set the title of our game window
    SetCanvasSize(width, height); // set the number of pixels...


    glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
    glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
    glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
    // This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
    glutTimerFunc(2000, Timer, 0);

    glutMouseFunc(MouseClicked);
    glutPassiveMotionFunc(MouseMoved); // Mouse


    
    glutMainLoop();
    return 1;
}
#endif /* RushHour_CPP_ */

