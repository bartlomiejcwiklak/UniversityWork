#include "primlib.h"
#include <math.h>
#include <unistd.h>

#define VERTICES 8
#define ROTATION_SPEED 0.02
#define SIZE_CHANGE_SPEED 0.03
#define MIN_RADIUS 10
#define MAX_RADIUS 200

void drawPolygon(int x[], int y[], int vertices, int color)
{
	for (int i = 0; i < vertices; i++) {
		gfx_line(x[i], y[i], x[(i + 1) % vertices], y[(i + 1) % vertices],
				 color);
	}
}

void calculateCoordinates(int x[], int y[], int vertices, int radius,
						  double angleOffset)
{
	for (int i = 0; i < vertices; i++) {
		double angle = 2 * M_PI * i / vertices + angleOffset;
		x[i] = (gfx_screenWidth() / 2) + radius * cos(angle);
		y[i] = (gfx_screenHeight() / 2) + radius * sin(angle);
	}
}

int main()
{
	if (gfx_init() != 0) {
		return 1;
	}

	double angleOffset = 0;
	double sizeOffset = 0;

	while (1) {
		gfx_filledRect(0, 0, gfx_screenWidth(), gfx_screenHeight(), BLACK);

		int radius =
			MAX_RADIUS + (MAX_RADIUS - MIN_RADIUS) * (0.5 * (sin(sizeOffset)));
		int x[VERTICES], y[VERTICES];
		calculateCoordinates(x, y, VERTICES, radius, angleOffset);
		drawPolygon(x, y, VERTICES, WHITE);

		gfx_updateScreen();
		SDL_Delay(20);

		angleOffset += ROTATION_SPEED;
		sizeOffset += SIZE_CHANGE_SPEED;

		if (angleOffset >= 2 * M_PI) {
			angleOffset -= 2 * M_PI;
		}

		if (gfx_isKeyDown(SDLK_ESCAPE)) {
			break;
		}
	}
	return 0;
}
