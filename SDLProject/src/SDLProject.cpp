#include <SDLProject.hpp> 

const int WIDTH = 600, HEIGHT = 600;
const int maxIter = 500;

long double xx = 3.4;
long double yy = 3.4;
long double factor = 1;

int jobs = 0;

mutex m;
sem_t m1;
sem_t m2;
sem_t m3;

auto magic = [](complex<long double> a, complex<long double> y) -> complex<long double> {return a * a + y;};
auto magic2 = [](long double x, long double y) -> long double {return y - 0.35294117647058826 * x;};

int main() {
	signal(SIGINT, &handler);
	signal(SIGTERM, &handler);
	signal(SIGHUP, &handler);
	
	if(SDL_Init(SDL_INIT_EVERYTHING)) {
		cout << "Video initialization error: " << SDL_GetError() << endl;
		exit(-1);
	}

	int cpu_cores =  thread::hardware_concurrency();
	cout << "Number of threads is " << cpu_cores << endl;

	MWindow<int> source(0, (int)WIDTH, 0, (int)HEIGHT);
 	MWindow<long double> fractal(-2.2, 1.2, -1.7, 1.7);

	RenderWindow *window = new RenderWindow("Process", WIDTH, HEIGHT);

	vector<int> colors(WIDTH * HEIGHT);

	sem_init(&m1, 0, 6);
	sem_init(&m2, 0, 0);
	sem_init(&m3, 0, 0);

	array<thread*, 6> workers;
	for(int i = 0; i < 6; ++i)
		workers[i] = new thread(run, ref(source), ref(fractal), ref(colors), i, i + 1);

	

	while(1) {
		sem_getvalue(&m3, &jobs);
		if(jobs == 6) {
			drawx(window, colors);
			factor *= 0.9994;
			xx *= factor;
			yy *= factor;

			jobs = 0;
			for(int i = 0; i < 6; i++)
				sem_wait(&m3);
            // mandel(source, fractal, colors, maxIter, 0, 600);
			
			for(int i = 0; i < 6; i++) {
				sem_post(&m1);
			}
		}

	}
	delete window;
	SDL_Quit();
	return 0;
}

#pragma GCC push_options 
#pragma GCC optimize ("O2")
void run(MWindow<int>& source, MWindow<long double>& fractal, vector<int>& colors, int section, int offset) {
	while(true) {
		sem_wait(&m1);
		mandel(source, fractal, colors, maxIter, section * 100, offset * 100);
		sem_post(&m3);

	}
}
#pragma GCC pop_options

void func() {
	while(true) {
		sem_getvalue(&m3, &jobs);
		if(jobs == 6) {
			sem_post(&m2);
			for(int i = 0; i < 6; i++)
				sem_wait(&m3);
			sem_wait(&m2);
			jobs = 0;
			
			for(int i = 0; i < 6; i++) {
				sem_post(&m1);
			}
		}
	}

}

void drawx(RenderWindow *window, vector<int>& colors) {
	for(int i{0}; i < WIDTH; ++i) {
		for(int j{0}; j < HEIGHT; ++j) {
			int c = colors[i * HEIGHT + j];
			double f = static_cast<double>(c) / static_cast<double> (maxIter);
			// int e = f * (1 << 24);

			// int r = e & 0xFF;
			// int g = (e >> 8) & 0xFF;
			// int b = (e >> 16) & 0xFF;

			int b = (int)(9*(1-f)*f*f*f*255);
			int g = (int)(15*(1-f)*(1-f)*f*f*255);
			int r =  (int)(8.5*(1-f)*(1-f)*(1-f)*f*255);
			window->SetColor(r, g, b);
			window->DrawPoint(i, j);
		}
	}
		window->Present();
}

void handler(int ) {
	exit(0);
}

complex<long double> scale(MWindow<int> &scr, MWindow<long double> &fr, std::complex<long double> c) {
   	std::complex<long double> aux(c.real() / static_cast<long double>(scr.Width()) * (xx) + fr.minX + magic2(xx, -1.250001 - fr.minX),
   		c.imag() / static_cast<long double>(scr.Height()) * yy + fr.minY + magic2(yy, -0.0500058-fr.minY));
   	return aux;
   }

int escape(complex<long double> c, int iter) {
   	std::complex<double> z(0);
   	int i = 0;
   	while (abs(z) < 2.0 && i < iter) {
   		z = magic(z, c);
   		i++;
   	}
   	return i;
   }

void mandel(MWindow<int>& source, MWindow<long double>& fractal, vector<int>& colors, int iter, int secx, int secy) {
	for(int i = secx; i < secy; ++i)
		for(int j = source.minX; j < source.maxX; ++j) {
			complex<long double> c(i, j);
			c = scale(source, fractal, c);
			colors[i * source.maxY + j] = escape(c, iter);
		}
}