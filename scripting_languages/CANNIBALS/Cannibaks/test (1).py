import pygame
import sys

pygame.init()

SCREEN_WIDTH = 900
SCREEN_HEIGHT = 600
FPS = 60
BACKGROUND_COLOR = (135, 206, 235)
FONT_COLOR = (0, 0, 0)
BOAT_CAPACITY = 2

BACKGROUND_IMG = pygame.image.load('assets/background.png')
MISSIONARY_IMG = pygame.image.load('assets/missionary.png')
CANNIBAL_IMG = pygame.image.load('assets/cannibal.png')
BOAT_IMG = pygame.image.load('assets/boat.png')

BACKGROUND_IMG = pygame.transform.scale(BACKGROUND_IMG, (SCREEN_WIDTH, SCREEN_HEIGHT))
MISSIONARY_IMG = pygame.transform.scale(MISSIONARY_IMG, (80, 80))
CANNIBAL_IMG = pygame.transform.scale(CANNIBAL_IMG, (80, 80))
BOAT_IMG = pygame.transform.scale(BOAT_IMG, (120, 80))

screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Missionaries and Cannibals")
font = pygame.font.Font(None, 36)


def render_text(text, x, y, font_size=36, center=False):
    '''
    Displays text on the screen at the specified position.
    '''
    font = pygame.font.Font(None, font_size)
    text_surface = font.render(text, True, FONT_COLOR)
    if center:
        text_rect = text_surface.get_rect(center=(x, y))
        screen.blit(text_surface, text_rect)
    else:
        screen.blit(text_surface, (x, y))


class GameState:
    '''
    Represents the game state and logic.
    '''

    def __init__(self):
        '''
        Initializes the game state.
        '''
        self.left_bank = {'missionaries': 3, 'cannibals': 3}
        self.right_bank = {'missionaries': 0, 'cannibals': 0}
        self.boat = {'missionaries': 0, 'cannibals': 0}
        self.boat_on_left = True
        self.boat_position = 200
        self.boat_moving = False
        self.moves = 0

    def is_valid_state(self, bank):
        '''
        Checks if a bank state is valid.
        '''
        missionaries = bank['missionaries']
        cannibals = bank['cannibals']
        return missionaries == 0 or missionaries >= cannibals

    def is_game_over(self):
        '''
        Checks if the game is over (win or loss).
        '''
        if not self.is_valid_state(self.left_bank) or not self.is_valid_state(self.right_bank):
            return 'failure'
        if self.right_bank['missionaries'] == 3 and self.right_bank['cannibals'] == 3:
            return 'success'
        return None

    def move_boat(self):
        '''
        Initiates the boat movement.
        '''
        if self.boat['missionaries'] + self.boat['cannibals'] == 0:
            return
        self.boat_moving = True
        self.boat_target = 600 if self.boat_on_left else 200
        self.moves += 1

    def update_boat_position(self):
        '''
        Updates the boat's position and transfers characters.
        '''
        if self.boat_moving:
            if self.boat_position < self.boat_target:
                self.boat_position += 8
            elif self.boat_position > self.boat_target:
                self.boat_position -= 8
            if abs(self.boat_position - self.boat_target) < 8:
                self.boat_position = self.boat_target
                self.boat_moving = False
                self.boat_on_left = not self.boat_on_left
                if self.boat_on_left:
                    self.left_bank['missionaries'] += self.boat['missionaries']
                    self.left_bank['cannibals'] += self.boat['cannibals']
                else:
                    self.right_bank['missionaries'] += self.boat['missionaries']
                    self.right_bank['cannibals'] += self.boat['cannibals']
                self.boat = {'missionaries': 0, 'cannibals': 0}


state = GameState()


def main():
    '''
    Runs the main game loop.
    '''
    global state
    clock = pygame.time.Clock()
    running = True
    welcome_screen = True
    game_over_screen = False
    game_result = None

    while running:
        screen.fill(BACKGROUND_COLOR)
        screen.blit(BACKGROUND_IMG, (0, 0))

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            if event.type == pygame.MOUSEBUTTONDOWN:
                if welcome_screen:
                    welcome_screen = False
                elif game_over_screen:
                    state = GameState()
                    game_over_screen = False
                elif not state.boat_moving:
                    handle_click(event.pos)

        if welcome_screen:
            render_text("Missionaries and Cannibals", SCREEN_WIDTH // 2, SCREEN_HEIGHT // 4, 92, center=True)
            render_text("Goal: Get everyone across the river safely.", SCREEN_WIDTH // 2, SCREEN_HEIGHT // 3 + 20, center=True)
            render_text("Click to start", SCREEN_WIDTH // 2, SCREEN_HEIGHT - 120, center=True)
        elif game_over_screen:
            if game_result == 'success':
                render_text("Congratulations! You Won!", SCREEN_WIDTH // 2, SCREEN_HEIGHT // 3, 48, center=True)
            elif game_result == 'failure':
                render_text("Game Over!", SCREEN_WIDTH // 2, SCREEN_HEIGHT // 3, 96, center=True)
            render_text("Click to try again", SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2, 36, center=True)
        else:
            state.update_boat_position()
            draw_game_state()
            game_result = state.is_game_over()
            if game_result:
                game_over_screen = True

        pygame.display.flip()
        clock.tick(FPS)

    pygame.quit()
    sys.exit()


def handle_click(pos):
    '''
    Handles user clicks to move characters or the boat.
    '''
    x, y = pos

    boat_x = state.boat_position if state.boat_moving else (200 if state.boat_on_left else 600)
    if boat_x < x < boat_x + 120 and 470 < y < 530:
        if state.boat['missionaries'] + state.boat['cannibals'] > 0:
            state.move_boat()
        return

    if state.boat_on_left:
        for i in range(state.left_bank['missionaries']):
            if 50 + i * 50 < x < 50 + i * 50 + 80 and 350 < y < 430:
                move_character_to_boat(state.left_bank, 'missionaries')
                return
        for i in range(state.left_bank['cannibals']):
            if 50 + i * 50 < x < 50 + i * 50 + 80 and 450 < y < 530:
                move_character_to_boat(state.left_bank, 'cannibals')
                return

    if not state.boat_on_left:
        for i in range(state.right_bank['missionaries']):
            if 700 + i * 50 < x < 700 + i * 50 + 80 and 350 < y < 430:
                move_character_to_boat(state.right_bank, 'missionaries')
                return
        for i in range(state.right_bank['cannibals']):
            if 700 + i * 50 < x < 700 + i * 50 + 80 and 450 < y < 530:
                move_character_to_boat(state.right_bank, 'cannibals')
                return

    for i in range(state.boat['missionaries']):
        if boat_x + i * 50 < x < boat_x + i * 50 + 80 and 470 < y < 550:
            move_character_from_boat('missionaries')
            return
    for i in range(state.boat['cannibals']):
        if boat_x + 10 + i * 50 < x < boat_x + 10 + i * 50 + 80 and 470 < y < 550:
            move_character_from_boat('cannibals')
            return


def move_character_to_boat(bank, character_type):
    '''
    Moves a character from a bank to the boat.
    '''
    if state.boat['missionaries'] + state.boat['cannibals'] < BOAT_CAPACITY and bank[character_type] > 0:
        bank[character_type] -= 1
        state.boat[character_type] += 1


def move_character_from_boat(character_type):
    '''
    Moves a character from the boat to a bank.
    '''
    if state.boat[character_type] > 0:
        state.boat[character_type] -= 1
        if state.boat_on_left:
            state.left_bank[character_type] += 1
        else:
            state.right_bank[character_type] += 1


def draw_game_state():
    '''
    Draws the current state of the game on the screen.
    '''
    render_text(f"Moves: {state.moves}", 10, 10)

    boat_x = state.boat_position if state.boat_moving else (200 if state.boat_on_left else 600)
    screen.blit(BOAT_IMG, (boat_x, 450))

    for i in range(state.left_bank['missionaries']):
        screen.blit(MISSIONARY_IMG, (50 + i * 50, 350))
    for i in range(state.left_bank['cannibals']):
        screen.blit(CANNIBAL_IMG, (50 + i * 50, 450))

    for i in range(state.right_bank['missionaries']):
        screen.blit(MISSIONARY_IMG, (700 + i * 50, 350))
    for i in range(state.right_bank['cannibals']):
        screen.blit(CANNIBAL_IMG, (700 + i * 50, 450))

    for i in range(state.boat['missionaries']):
        screen.blit(MISSIONARY_IMG, (boat_x + i * 50, 440))
    for i in range(state.boat['cannibals']):
        screen.blit(CANNIBAL_IMG, (boat_x + 10 + i * 50, 440))


if __name__ == "__main__":
    main()
