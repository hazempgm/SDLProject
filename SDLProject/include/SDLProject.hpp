// SDLProject.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <csignal>
#include <complex>
#include <MandelWindow.hpp>
#include <vector>
#include <thread>
#include <array>
#include <semaphore.h>
#include <RenderWindow.hpp>
#include <mutex>

using namespace std;

void func();
void drawx(RenderWindow*, vector<int>&);
void handler(int);
int escape(complex<long double> c, int iter);
void mandel(MWindow<int>& source, MWindow<long double>& fractal, vector<int>& colors, int iter, int,int);
complex<long double> scale(MWindow<int> &scr, MWindow<long double> &fr, std::complex<long double> c);
void run(MWindow<int>& source, MWindow<long double>& fractal, vector<int>& colors, int section, int offset);

// TODO: Reference additional headers your program requires here.
