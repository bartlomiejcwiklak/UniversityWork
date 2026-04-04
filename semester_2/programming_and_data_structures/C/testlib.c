#include "pieces.inl"
#include "primlib.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 15
#define DROP_INTERVAL_MS 500
#define SCORE_PER_LINE 100
#define SCORE_TEXT_MARGIN 20
#define FONT_COLOR WHITE

enum { false, true };
typedef int bool;

typedef struct {
	int kind;
	int rotation;
	int x, y;
} Piece;

static int field[FIELD_HEIGHT][FIELD_WIDTH];
static enum color pieceColors[8] = {BLACK, YELLOW, CYAN,	GREEN,
									RED,   BLUE,   MAGENTA, WHITE};
static int score;
static Piece currentPiece;
static int offsetX, offsetY;
static int blockSize;

static int clearLines(void);
static bool spawnPiece(void);
static bool updateDrop(bool*, int*);
static bool checkCollision(int, int, int, int);
static void initGame(void);
static void calculateOffsets(void);
static void lockPiece(void);
static void processInput(bool*, int*);
static void drawBorder(void);
static void drawField(void);
static void drawPiece(void);
static void drawScore(void);
static void render(void);
static void showEndMessage(int);

int main(void)
{
	gfx_init();
	srand((unsigned)time(NULL));
	initGame();
	calculateOffsets();
	bool running = true;
	int gameOverReason = 0;
	Uint32 lastDrop = SDL_GetTicks();
	while (running) {
		processInput(&running, &gameOverReason);
		Uint32 now = SDL_GetTicks();
		if (now - lastDrop >= DROP_INTERVAL_MS) {
			updateDrop(&running, &gameOverReason);
			lastDrop = now;
		}
		render();
		SDL_Delay(20);
	}
	showEndMessage(gameOverReason);
	return 0;
}

static void initGame(void)
{
	score = 0;
	for (int i = 0; i < FIELD_HEIGHT; i++)
		for (int j = 0; j < FIELD_WIDTH; j++)
			field[i][j] = 0;
	spawnPiece();
}

static void calculateOffsets(void)
{
	int screenW = gfx_screenWidth();
	int screenH = gfx_screenHeight();
	int sizeW = screenW / FIELD_WIDTH;
	int sizeH = screenH / FIELD_HEIGHT;
	blockSize = (sizeW < sizeH) ? sizeW : sizeH;
	if (blockSize < 1)
		blockSize = 1;
	offsetX = (screenW - FIELD_WIDTH * blockSize) / 2;
	offsetY = (screenH - FIELD_HEIGHT * blockSize) / 2;
}

static bool spawnPiece(void)
{
	currentPiece.kind = rand() % 7;
	currentPiece.rotation = 0;
	currentPiece.x = FIELD_WIDTH / 2 - 2;
	currentPiece.y = -2;
	return !checkCollision(currentPiece.kind, currentPiece.rotation,
						   currentPiece.x, currentPiece.y);
}

static bool checkCollision(int kind, int rot, int x, int y)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (pieces[kind][rot][i][j]) {
				int globalx = x + j;
				int globaly = y + i;
				if (globalx < 0 || globalx >= FIELD_WIDTH ||
					globaly >= FIELD_HEIGHT)
					return true;
				if (globaly >= 0 && field[globaly][globalx])
					return true;
			}
	return false;
}

static void lockPiece(void)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (pieces[currentPiece.kind][currentPiece.rotation][i][j]) {
				int globalx = currentPiece.x + j;
				int globaly = currentPiece.y + i;
				if (globaly >= 0)
					field[globaly][globalx] = currentPiece.kind + 1;
			}
}

static int clearLines(void)
{
	int linesCleared = 0;
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		bool full = true;
		for (int j = 0; j < FIELD_WIDTH; j++)
			if (!field[i][j]) {
				full = false;
				break;
			}
		if (full) {
			linesCleared++;
			for (int newI = i; newI > 0; newI--)
				for (int newJ = 0; newJ < FIELD_WIDTH; newJ++)
					field[newI][newJ] = field[newI - 1][newJ];
			for (int newJ = 0; newJ < FIELD_WIDTH; newJ++)
				field[0][newJ] = 0;
		}
	}
	score += linesCleared * SCORE_PER_LINE;
	return linesCleared;
}

static void processInput(bool* running, int* gameOverReason)
{
	int key;
	while ((key = gfx_pollkey()) != -1) {
		if (key == SDLK_ESCAPE) {
			*running = false;
			*gameOverReason = 2;
			return;
		}
		if (key == SDLK_RETURN) {
			*running = false;
			*gameOverReason = 1;
			return;
		}
		if (key == SDLK_LEFT &&
			!checkCollision(currentPiece.kind, currentPiece.rotation,
							currentPiece.x - 1, currentPiece.y)) {
			currentPiece.x--;
		}
		if (key == SDLK_RIGHT &&
			!checkCollision(currentPiece.kind, currentPiece.rotation,
							currentPiece.x + 1, currentPiece.y)) {
			currentPiece.x++;
		}
		if (key == SDLK_DOWN &&
			!checkCollision(currentPiece.kind, currentPiece.rotation,
							currentPiece.x, currentPiece.y + 1)) {
			currentPiece.y++;
		}
		if (key == SDLK_SPACE) {
			int oldRot = currentPiece.rotation;
			int newRot = (oldRot + 1) % 4;
			int pivotOldI = 0, pivotOldJ = 0;
			int pivotNewI = 0, pivotNewJ = 0;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (pieces[currentPiece.kind][oldRot][i][j] == 2) {
						pivotOldI = i;
						pivotOldJ = j;
					}
					if (pieces[currentPiece.kind][newRot][i][j] == 2) {
						pivotNewI = i;
						pivotNewJ = j;
					}
				}
			}
			int newX = currentPiece.x + pivotOldJ - pivotNewJ;
			int newY = currentPiece.y + pivotOldI - pivotNewI;
			if (!checkCollision(currentPiece.kind, newRot, newX, newY)) {
				currentPiece.rotation = newRot;
				currentPiece.x = newX;
				currentPiece.y = newY;
			}
		}
	}
}

static bool updateDrop(bool* running, int* gameOverReason)
{
	if (!checkCollision(currentPiece.kind, currentPiece.rotation,
						currentPiece.x, currentPiece.y + 1)) {
		currentPiece.y++;
		return true;
	}
	if (currentPiece.y < 0) {
		*running = false;
		*gameOverReason = 2;
		return false;
	}
	lockPiece();
	clearLines();
	if (!spawnPiece()) {
		*running = false;
		*gameOverReason = 2;
	}
	return false;
}

static void drawBorder(void)
{
	gfx_rect(offsetX - 1, offsetY - 1, offsetX + FIELD_WIDTH * blockSize,
			 offsetY + FIELD_HEIGHT * blockSize, FONT_COLOR);
}

static void drawField(void)
{
	for (int r = 0; r < FIELD_HEIGHT; r++)
		for (int c = 0; c < FIELD_WIDTH; c++)
			if (field[r][c]) {
				int x = offsetX + c * blockSize;
				int y = offsetY + r * blockSize;
				gfx_filledRect(x, y, x + blockSize - 1, y + blockSize - 1,
							   pieceColors[field[r][c]]);
			}
}

static void drawPiece(void)
{
	enum color col = pieceColors[currentPiece.kind + 1];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (pieces[currentPiece.kind][currentPiece.rotation][i][j]) {
				int x = offsetX + (currentPiece.x + j) * blockSize;
				int y = offsetY + (currentPiece.y + i) * blockSize;
				gfx_filledRect(x, y, x + blockSize - 1, y + blockSize - 1, col);
			}
}

static void drawScore(void)
{
	char buf[32];
	sprintf(buf, "Score: %d", score);
	gfx_textout(offsetX + FIELD_WIDTH * blockSize + SCORE_TEXT_MARGIN, offsetY + SCORE_TEXT_MARGIN,
				buf, FONT_COLOR);
}

static void render(void)
{
	gfx_filledRect(0, 0, gfx_screenWidth(), gfx_screenHeight(), BLACK);
	drawBorder();
	drawField();
	drawPiece();
	drawScore();
	gfx_updateScreen();
}

static void showEndMessage(int gameOverReason)
{
	gfx_filledRect(0, 0, gfx_screenWidth(), gfx_screenHeight(), BLACK);
	if (gameOverReason == 1)
		gfx_textout(offsetX, offsetY, "Congratulations", FONT_COLOR);
	else
		gfx_textout(offsetX, offsetY, "Try again", FONT_COLOR);
	gfx_updateScreen();
	gfx_getkey();
}
