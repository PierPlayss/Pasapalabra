//Retextured

//SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
//OpenCV
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
//C++
#include <iostream>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <ctime>
//Headers
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "logic.h"
#include "SDL2SoundEffects.h"

using namespace std;
using namespace cv;

RenderWindow window("Pasapalabra", 1280, 720);

int SetMouseX, SetMouseY;
void checkposition(bool rosco1Over, int answers[], int& posicion, int& respondidas, int selected[]);
void game(int answers[], int selected[], int& posicion, int buttons[], bool& roscoOver, int& respondidas,int &acertadas,int& rosco,int selected2[],int &posicion2,bool &changesomething, bool roscoOver2,bool &timerOn, int &incorrectas);
void SetMousePos(int x, int y) {
	SetMouseX = x;
	//cout << "x: " << SetMouseX << endl;
	SetMouseY = y;
	//cout << "y: " << SetMouseY << endl;
}
void onMouse(int event, int x, int y, int flags, void* params) {
	Mat* image = reinterpret_cast<Mat*>(params);
	switch (event) {
	case EVENT_LBUTTONDOWN: {
		int pixelvalue = static_cast<int>(image->at<uchar>(Point(x, y)));
		//cout << "The pixel value is x:" << x << " y:" << y << " . " << pixelvalue << endl;
		SetMousePos(x, y);
	}break;

	}

}

int main(int argc, char* argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		cout << "IMG_init has failed. Error: " << SDL_GetError() << endl;
	
	if (TTF_Init() == -1) {
		cout << "TTF_init has failed. Error: " << SDL_GetError() << endl;
	}
	
	//Settings
	Mat Settings(160, 190, CV_8UC3, Scalar(238, 238, 238));
	Mat reset(160, 190, CV_8UC3, Scalar(238, 238, 238));

	Mat accepted = imread("res/gfx/acceptedButton.png");
	Mat wrong = imread("res/gfx/wrongButton.png");
	Mat pass = imread("res/gfx/passButton.png");
	Mat leftArrowButton = imread("res/gfx/arrow.png");
	Mat rightArrowButton = imread("res/gfx/arrow.png");
	Mat resetButton = imread("res/gfx/resetButton.png");
	Mat timerButton = imread("res/gfx/timerButton.png");
	Mat R1 = imread("res/gfx/rosco1.png");
	Mat R2 = imread("res/gfx/rosco2.png");
	Mat musicButton = imread("res/gfx/music.png");

	resize(musicButton, musicButton, Size(), 0.7, 0.7);
	resize(timerButton, timerButton, Size(), 0.7, 0.7);
	resize(resetButton, resetButton, Size(), 0.7, 0.7);
	resize(leftArrowButton, leftArrowButton, Size(), 0.7, 0.7);
	resize(rightArrowButton, rightArrowButton, Size(), 0.7, 0.7);
	flip(leftArrowButton, leftArrowButton, 1);
	int buttons[10] = { 0,0,0,0,0,0,0,0,0,0 };

	//Sounds

	
	int mouseX=0, mouseY=0;
	int acumulatedpoints = 0;
	int multiplicador = 1;
	int Team1Points = 0;
	int Team2Points = 0;
	string STeam1Points;
	string STeam2Points;
	stringstream tp, tp2;
	int pointsaux;
	int widthPoints=0, heightPoints=0;
	int respuestas = 0;
	bool movewindow = false;
	stringstream ap; string stringpoints;

	int x[25] =            { 313,376,435,486,526,552,565,560,546,507,462,401,345,282,220,165,120, 86, 67, 64, 75,101,141,192,252 };
	int y[25] =              {75,82, 105,142,192,248,310,372,432,485,530,558,575,575,558,530,482,432,372,312,248,192,142,105,82};
	string abecedario[25] = {"A","B","C","D","E","F","G","H","I","J","L","M","N","Ñ","O","P","Q","R","S","T","U","V","X","Y","Z " };
	int lugaresX[25]=      { 315,377,436,487,527,553,565,561,542,508,462,408,346,284,222,168,122, 88, 69, 65, 77,103,143,194,253 };
	int lugaresY[25]=       { 73,81, 104,141,189,246,308,371,430,484,527,556,573,573,556,527,484,430,371,308,246,189,141,105,81 };
	int answers[25] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int selected[25] = { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int answers2[25] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int selected2[25] = { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int respondidas=0;
	int respondidas2 = 0;
	int acertadas = 0;
	int acertadas2 = 0;
	int incorrectas = 0;
	int incorrectas2 = 0;
	bool rosco1Over = false;
	bool rosco2Over = false;
	bool changesomething = false;
	int rosco = 1;
	
	
	int angulo[2] = { 0,0 };
	string timerS, timerS2;
	bool timerOn = false, timer2On = false;
	bool show[2] = { 0,0 };
	int posicion = 0;
	int posicion2 = 0;
	//Texturas
	SDL_Texture* letrasTexture = window.loadTexture("res/gfx/letras.png");
	SDL_Texture* backgroundTexture = window.loadTexture("res/gfx/background.png");
	SDL_Texture* abecedarioTexture = window.loadTexture("res/gfx/abecedario.png");
	SDL_Texture* greenTexture = window.loadTexture("res/gfx/accepted.png");
	SDL_Texture* yellowTexture = window.loadTexture("res/gfx/pass.png");
	SDL_Texture* redTexture = window.loadTexture("res/gfx/wrong.png");
	SDL_Texture* selectedTexture = window.loadTexture("res/gfx/selected2.png");
	SDL_Texture* scoreTexture = window.loadTexture("res/gfx/score.png");
	SDL_Texture* timeTexture = window.loadTexture("res/gfx/time.png");
	SDL_Texture* maskOnTexture = window.loadTexture("res/gfx/maskOn.png");

	//Entidades

	Entity letras(0, 0, 1280, 720, letrasTexture);
	Entity background(0, 0, 1280, 720, backgroundTexture);
	Entity abecedarioEnt(0, 0, 1280, 720, abecedarioTexture);
	Entity green(0, 0, 52, 52, greenTexture);
	Entity yellow(0, 0, 52, 52, yellowTexture);
	Entity red(0, 0, 52, 52, redTexture);
	Entity selectedEntity(0, 0, 52, 52, selectedTexture);
	Entity timeEntity(0, 0, 113, 113, timeTexture);
	Entity maskOn(0, 0, 1280, 720, maskOnTexture);
	bool mask = false;

	bool gameRunning = true;

	SDL_Event event;
	SDL_Event mouseEvent{ SDL_MOUSEMOTION };

	SDL2SoundEffects se;
	se.addSoundEffect("res/sound/hit.mp3"); //0
	se.addSoundEffect("res/sound/wrong.mp3"); //1
	Mix_Music* bgm = Mix_LoadMUS("res/sound/music.mp3");
	clock_t time;
	bool stopMusic = false;


	//Archivos
	ofstream roscoyletra;
	fstream preguntas;
	fstream tiempo;
	stringstream tim;
	string aux;
	int timer =-1, timer2 = -1;
	string preguntasAzul[25];
	string respuestasAzul[25];
	string preguntasNaranja[25];
	string respuestasNaranja[25];
	tiempo.open("timers.txt", ios::in);
	getline(tiempo, aux);
	tim.clear();
	tim << aux;
	tim >> timer;
	getline(tiempo, aux);
	tim.clear();
	tim << aux;
	tim >> timer2;

	int auxtimer = timer, auxtimer2 = timer2;
	preguntas.open("questions.txt", ios::in);
	for (int i = 0; i < 25; i++) {
		getline(preguntas, preguntasAzul[i]);
		getline(preguntas, respuestasAzul[i]);
		//cout << answersAzul[i] << endl;
	}
	for (int i = 0; i < 25; i++) {
		getline(preguntas, preguntasNaranja[i]);
		getline(preguntas, respuestasNaranja[i]);
		//cout << answersAzul[i] << endl;
	}
	preguntas.close();

	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	bool SDLButton[3] = { 0,0,0};

	while (gameRunning)
	{	
		acertadas = 0;
		acertadas2 = 0;
		incorrectas = 0;
		incorrectas2 = 0;
		if (stopMusic==false and settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[8] == 1) {
			if (!Mix_PlayingMusic()) {
				Mix_PlayMusic(bgm, -1);
			}
			if (stopMusic ==false) {
				Mix_ResumeMusic();
				stopMusic = true;
			}
		
			SetMouseX = -1;
			SetMouseY = -1;
		}
		if (stopMusic == true and settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[8] == 1) {
			Mix_PauseMusic();
			stopMusic = false;
				
			SetMouseX = -1;
			SetMouseY = -1;
		}
	

		if (((rosco == 1 and timerOn == false) or (rosco == 2 and timer2On == false)) and settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[6] == 1 or GetAsyncKeyState('P')) {
			if (rosco == 1) {
				timerOn = true;
				
			}
			else timer2On = true;
			time = clock();
			SetMouseX = -1;
			SetMouseY = -1;
		}

		if (((rosco==1 and timerOn==true) or (rosco==2 and timer2On==true)) and settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[6] == 1 or GetAsyncKeyState('O')) {
			if (rosco == 1) {
				timerOn = false;
			}
			else timer2On = false;
			SetMouseX = -1;
			SetMouseY = -1;
		}
	
		if (timerOn == true or timer2On==true) {
			time = (clock() - time);
			if (float(time) / CLOCKS_PER_SEC >= 0.51 and float(time) / CLOCKS_PER_SEC <= 1) {
				if (rosco == 1) {
					if(timer!=0)timer -= 1;
				}
				if (rosco == 2) {
					if (timer2 != 0)timer2 -= 1;
				}
				time = 0;
			}
			/*if(float(timer)/CLOCKS_PER_SEC==0.5){
				total-=1;
				timer=0;
			}*/
			//cout<<timer/CLOCKS_PER_SEC<<endl;
		}
		if (timer == 0 and rosco1Over==false) {
			rosco1Over = true;
			timerOn = false;
		}
		if (timer2 == 0 and rosco2Over == false) {
			rosco2Over = true;
			timer2On = false;
		

		}
		
		// Get our controls and events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
			if (event.type == SDL_MOUSEMOTION) {

				mouseX = event.motion.x -25;
				mouseY = event.motion.y -25;
				//cout << mouseX << "," << mouseY << endl;
				
			}
			if (event.button.button == SDL_BUTTON_LEFT) {
				
				}
			
			
		}
		setMouseCallback("Settings", onMouse, reinterpret_cast<void*>(&Settings));
		reset.copyTo(Settings(Rect(0, 0, reset.cols, reset.rows)));
		accepted.copyTo(Settings(Rect(1, 1, accepted.cols, accepted.rows)));
		wrong.copyTo(Settings(Rect(65, 1, wrong.cols, wrong.rows)));
		pass.copyTo(Settings(Rect(130, 1, pass.cols, pass.rows)));
		leftArrowButton.copyTo(Settings(Rect(1, 60, leftArrowButton.cols, leftArrowButton.rows)));
		rightArrowButton.copyTo(Settings(Rect(120, 60, leftArrowButton.cols, leftArrowButton.rows)));
		resetButton.copyTo(Settings(Rect(60, 60, resetButton.cols, resetButton.rows)));
		timerButton.copyTo(Settings(Rect(60, 105, timerButton.cols, timerButton.rows)));
		musicButton.copyTo(Settings(Rect(140, 105, musicButton.cols, musicButton.rows)));

		if (rosco == 1) {
			R2.copyTo(Settings(Rect(15, 105, R2.cols, R2.rows)));
			show[0] = 1;
			show[1] = 0;
		}
		else {
			R1.copyTo(Settings(Rect(15, 105, R1.cols, R1.rows)));
			show[1] = 1;
			show[0] = 0;
		}

		if (settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[7] == 1) {
			if (rosco == 1) {
				rosco = 2;
				timerOn = false;
			}
			else {
				rosco = 1;
				timer2On = false;

			}
			SetMouseX = -1;
			SetMouseY = -1;
		}

		window.RenderWindow::clear();
		
		if (mask == true) {
			window.render(maskOn, 1);
		}
		else window.render(background, 1);
		window.render(letras, 1);	

		if (settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[0] == 1) {
			se.playSoundEffect(0);
			//cout << "Sound played" << endl;
			
		}
		if (settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[1] == 1) {
			se.playSoundEffect(1);
			//cout << "Sound played" << endl;
		
		}

		for (int i = 0; i < 25; i++) {
			window.drawText(abecedario[i].c_str(), x[i] + 3, y[i] + 3, 4, 21, 245, 38);
			window.drawText(abecedario[i].c_str(), x[i] + 3 + 625, y[i] + 3, 4, 21, 245, 38);
			if (answers[i] == 1) {
				Entity green(lugaresX[i] - 15, lugaresY[i], 52, 52, greenTexture);
				acertadas++;
				window.drawText(abecedario[i].c_str(), x[i] + 3, y[i] + 3, 4, 21, 245, 38);
				window.drawText(abecedario[i].c_str(), x[i] + 3 + 625, y[i] + 3, 4, 21, 245, 38);
				window.render(green, 1);
			}
			if (answers2[i] == 1) {
				acertadas2++;
				Entity green(lugaresX[i] - 15+625, lugaresY[i], 52, 52, greenTexture);
				window.drawText(abecedario[i].c_str(), x[i] + 3 + 625, y[i] + 3, 4, 21, 245, 38);
				window.render(green, 1);
			}			
			if (answers[i] == 2) {
				Entity yellow(lugaresX[i] - 15, lugaresY[i], 52, 52, yellowTexture);
				window.drawText(abecedario[i].c_str(), x[i] + 3, y[i] + 3, 4, 21, 245, 38);
				window.render(yellow, 1);
			}
			if (answers2[i] == 2) {
				Entity yellow(lugaresX[i] - 15+625, lugaresY[i], 52, 52, yellowTexture);
				window.drawText(abecedario[i].c_str(), x[i] + 3 + 625, y[i] + 3, 4, 21, 245, 38);
				window.render(yellow, 1);
			}
			if (answers[i] == 3) {
				incorrectas++;
				Entity red(lugaresX[i] - 15, lugaresY[i], 52, 52, redTexture);
				window.drawText(abecedario[i].c_str(), x[i] + 3, y[i] + 3, 4, 21, 245, 38);
				window.render(red, 1);
			}
			if (answers2[i] == 3) {
				incorrectas2++;
				Entity red(lugaresX[i] - 15+625, lugaresY[i], 52, 52, redTexture);
				window.drawText(abecedario[i].c_str(), x[i] + 3 + 625, y[i] + 3, 4, 21, 245, 38);
				window.render(red, 1);
			}
			if (selected[i] == 1 and show[0]==1) {
				Entity selectedEntity(lugaresX[i] - 15, lugaresY[i], 52, 52, selectedTexture);
				window.render(selectedEntity, 1);
				if (rosco == 1) {
					roscoyletra.open("./base-react/server/txt.txt", ios::in);
					roscoyletra << preguntasAzul[i] << endl;
					roscoyletra << abecedario[i] << endl;
					roscoyletra << "Azul" << endl;
					roscoyletra << respuestasAzul[i] << endl;
					roscoyletra.close();
				}
				
			}
			if (selected2[i] == 1 and show[1] == 1) {
				Entity selectedEntity(lugaresX[i] - 15 + 625, lugaresY[i], 52, 52, selectedTexture);
				window.render(selectedEntity, 1);
				if (rosco == 2) {
					roscoyletra.open("./base-react/server/txt.txt", ios::in);
					roscoyletra << preguntasNaranja[i] << endl;
					roscoyletra << abecedario[i] << endl;
					roscoyletra << "Naranja" << endl;
					roscoyletra << respuestasNaranja[i] << endl;
								
					roscoyletra.close();
				}
				
			}
			
			
			//window.drawText(abecedario[i].c_str(), x[i], y[i], 255, 255, 252, 38);
		}
		for (int i = 0; i < 2; i++) {
			Entity score(8+(625*i), 560, 108, 108, scoreTexture);
			window.render(score, 1);
		}
		
		
		if (timerOn == true) {
			angulo[0]+=5;
		}
		if (timer2On == true) {
			angulo[1]+=5;
		}

		for (int i = 0; i < 2; i++) {
			Entity timeEntity(117+(625*i), 590, 113, 113, timeTexture);
			window.render(timeEntity,angulo[i], 1);
			if (angulo[i] == 360) {
				angulo[i] = 0;
			}
		}
		
		

		if (settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[5] == 1) {
			for (int i = 0; i < 25; i++) {
				answers[i] = 0;
				answers2[i] = 0;
				selected[i] = 0;
				selected2[i] = 0;
				
			}
			posicion2 = 0;
			posicion = 0;
			selected[0] = 1;
			acertadas = 0;
			acertadas2 = 0;
			SetMouseX = -1;
			SetMouseY = -1;
			timer = auxtimer;
			timer2 = auxtimer2;
			timerOn = false;
			timer2On = false;

		}
		if (rosco1Over == true and rosco2Over==false) {
			rosco = 2;
			//checkposition(rosco2Over, answers2, posicion2, respondidas2, selected2);
		}
		if (rosco2Over == true and rosco1Over == false) {
			rosco = 1;
			//checkposition(rosco1Over, answers, posicion, respondidas, selected);
		}
		if (rosco1Over == true and rosco2Over == true) {
			cout << "Game over" << endl;
		}

		if (rosco == 1 and rosco1Over==false) {
			game(answers, selected, posicion, buttons, rosco1Over, respondidas,acertadas,rosco,selected2,posicion2,changesomething,rosco2Over,timerOn,incorrectas);
		}
		if(rosco == 2 and rosco2Over == false) {
			game(answers2, selected2, posicion2, buttons, rosco2Over, respondidas2,acertadas2, rosco,selected,posicion,changesomething,rosco1Over,timer2On,incorrectas);
		}
		tp.clear();
		tp << acertadas;
		tp >> STeam1Points;
		if (acertadas < 10) {
			window.drawText(STeam1Points.c_str(), 48+3, 582+3, 40, 40, 40, 50);
			window.drawText(STeam1Points.c_str(), 48, 582, 255, 255, 255, 50);
		}
		if (acertadas > 9) {
			window.drawText(STeam1Points.c_str(), 48 - 15+3, 582+3, 40, 40, 40, 50);
			window.drawText(STeam1Points.c_str(), 48-15, 582, 255, 255, 255, 50);
		}
		tp.clear();
		tp << acertadas2;
		tp >> STeam2Points;
		if (acertadas2 < 10) {
			window.drawText(STeam2Points.c_str(), 48 + 3+625, 582 + 3, 40, 40, 40, 50);
			window.drawText(STeam2Points.c_str(), 48+625, 582, 255, 255, 255, 50);
		}
		if (acertadas2 > 9) {
			window.drawText(STeam2Points.c_str(), 48 - 15 + 3+625, 582 + 3, 40, 40, 40, 50);
			window.drawText(STeam2Points.c_str(), 48 - 15+625, 582, 255, 255, 255, 50);
		}
			
	
		tp.clear();
		tp << timer;
		tp >> timerS;
		if (timer > 99) {
			window.drawText(timerS.c_str(), 130 + 3, 615 + 3, 191, 28, 85, 50);
			window.drawText(timerS.c_str(), 130, 615, 255, 255, 255, 50);
		}
		if (timer < 100 and timer>9) {
			window.drawText(timerS.c_str(), 130 + 3+15, 615 + 3, 191, 28, 85, 50);
			window.drawText(timerS.c_str(), 130+15, 615, 255, 255, 255, 50);
		}
		if (timer < 10) {
			window.drawText(timerS.c_str(), 130 + 3+30, 615 + 3, 191, 28, 85, 50);
			window.drawText(timerS.c_str(), 130+30, 615, 255, 255, 255, 50);
		}
		
	
		tp2.clear();
		tp2 << timer2;
		tp2 >> timerS2;
		if (timer2 > 99) {
			window.drawText(timerS2.c_str(),( 130 + 625 + 3), 615 + 3, 191, 28, 85, 50);
			window.drawText(timerS2.c_str(), (130 + 625 ), 615, 255, 255, 255, 50);
		}
		if (timer2 < 100 and timer2>9) {
			window.drawText(timerS2.c_str(), (130 + 625 + 3+15) , 615 + 3, 191, 28, 85, 50);
			window.drawText(timerS2.c_str(), (130 + 625+15) , 615, 255, 255, 255, 50);
		}
		if (timer2 < 10) {
			window.drawText(timerS2.c_str(), (130 + 625 + 3+30) , 615 + 3, 191, 28, 85, 50);
			window.drawText(timerS2.c_str(), (130 + 625+30), 615, 255, 255, 255, 50);
		}
		//window.drawText(abecedario[posicion].c_str(), 0, 0, 255, 255, 255, 50);

		
		window.render(abecedarioEnt, 1);
		window.display();
		imshow("Settings", Settings);
		if (movewindow == false) {
			moveWindow("Settings", 1600, 150);
			movewindow = true;
		}
	
		
	}


	window.cleanUp();
	SDL_Quit();
	TTF_Quit();

	return 0;
}

void checkposition(bool rosco1Over,int answers[],int &posicion,int &respondidas, int selected[]) {
	if (rosco1Over == false) {
		while (answers[posicion] != 0 && answers[posicion] != 2) {
			if (respondidas >= 25) {
				rosco1Over = true;
				break;
			}
			posicion++;

			if (posicion == 25) {
				selected[24] = 0;
				selected[0] = 1;
				
			}
			else {
				selected[posicion - 1] = 0;
				selected[posicion] = 1;
			}
			if (posicion < 0) {
				posicion = 24;
			}
			if (posicion > 24) {
				posicion = 0;
			}
			
		}
	}
	else {
		for (int i = 0; i < 25; i++) {
			selected[i] = 0;
		}
	}
}
void game(int answers[],int selected[],int &posicion,int buttons[],bool &roscoOver,int &respondidas,int &acertadas,int &rosco,int selected2[],int &posicion2, bool& changesomething,bool roscoOver2,bool &timerOn, int& incorrectas) {
	

	if (GetAsyncKeyState(VK_LEFT) or (settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[3] == 1)) {
		posicion--;
		if (posicion == -1) {
			selected[0] = 0;
			selected[24] = 1;
		}
		else {
			selected[posicion + 1] = 0;
			selected[posicion] = 1;
		}
		Sleep(40);
		changesomething = true;
		SetMouseX = -1;
		SetMouseY = -1;
	}
	if (GetAsyncKeyState(VK_RIGHT) or (settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[4] == 1)) {

		posicion++;
		if (posicion == 25) {
			selected[24] = 0;
			selected[0] = 1;
		}
		else {
			selected[posicion - 1] = 0;
			selected[posicion] = 1;
		}
		Sleep(40);
		checkposition(roscoOver, answers, posicion, respondidas, selected);
		SetMouseX = -1;
		SetMouseY = -1;
	}

	if (posicion < 0) {
		posicion = 24;
	}
	if (posicion > 24) {
		posicion = 0;
	}



	if ((settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[0] == 1)) {
	
		if (answers[posicion] == 0 or answers[posicion] == 2 or changesomething==true) {
			answers[posicion] = 1;
			respondidas++;
			
		}
		selected[posicion] = 0;
		posicion++;
		if (posicion == 25) {
			posicion = 0;
		}
		if (roscoOver == false) {
			selected[posicion] = 1;
		}
		
		checkposition(roscoOver, answers, posicion, respondidas, selected);
		if (changesomething == true) {
			changesomething = false;
		}
		SetMouseX = -1;
		SetMouseY = -1;
	}
	if ((settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[1] == 1)) {
		
		if (answers[posicion] == 0 or answers[posicion] == 2 or changesomething == true) {
			answers[posicion] = 3;
			respondidas++;
			timerOn = false;
			selected[posicion] = 0;
			posicion++;
			changesomething == false;
			if (posicion == 25) {
				posicion = 0;
			}
			selected[posicion] = 0;
			if (roscoOver == false) {
				selected[posicion] = 1;
			}
			checkposition(roscoOver, answers, posicion, respondidas, selected);
			if (roscoOver2 == false) {
				if (rosco == 1) {
					rosco = 2;
				}
				else rosco = 1;
			}
		}

		SetMouseX = -1;
		SetMouseY = -1;
		
		
	}

	if ((settingsmouse(SetMouseX, SetMouseY, buttons) == true and buttons[2] == 1)) {
		
		if (answers[posicion] == 0 or answers[posicion] == 2 or changesomething == true) {
			answers[posicion] = 2;
			changesomething == false;
			timerOn = false;
		}
		selected[posicion] = 0;
		posicion++;
		if (posicion == 25) {
			posicion = 0;
		}
		selected[posicion] = 0;
		if (roscoOver == false) {
			selected[posicion] = 1;
		}
		if (rosco == 1) {
			rosco = 2;
		}
		else rosco = 1;
		checkposition(roscoOver, answers, posicion, respondidas, selected);
		SetMouseX = -1;
		SetMouseY = -1;
	}

	if (acertadas+incorrectas >= 25) {
		roscoOver = true;
		checkposition(roscoOver, answers, posicion, respondidas, selected);
	}


}
