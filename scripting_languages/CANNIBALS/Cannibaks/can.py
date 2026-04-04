import pygame
import sys

pygame.init()

SCR_WID = 900
SCR_HIG = 600
FPS = 60
BG_COL = (135, 206, 235)
FON_COL = (0, 0, 0)
BOAT_CAPACITY = 2

BG_IMG = pygame.image.load('assets/background.png')
MIS_IMG = pygame.image.load('assets/missionary.png')
CAN_IMG = pygame.image.load('assets/cannibal.png')
BOAT_IMG = pygame.image.load('assets/boat.png')

BG_IMG = pygame.transform.scale(BG_IMG, (SCR_WID, SCR_HIG))
MIS_IMG = pygame.transform.scale(MIS_IMG, (80, 80))
CAN_IMG = pygame.transform.scale(CAN_IMG, (80, 80))
BOAT_IMG = pygame.transform.scale(BOAT_IMG, (120, 80))

screen = pygame.display.set_mode((SCR_WID, SCR_HIG))
pygame.display.set_caption("Missionaries and Cannibals")
font = pygame.font.Font(None, 36)
game_over_screen = False
game_result = None


def render_text(text, x, y, font_size=36, center=False):
    '''
    Renders a string of text on the screen at a specified position.
    - text: The string to display.
    - x, y: Coordinates of the position where the text will be rendered.
    - font_size: The size of the font for the text.
    - center: If True, centers the text at the specified coordinates.
    '''
    font = pygame.font.Font(None, font_size)
    text_surface = font.render(text, True, FON_COL)
    if center:
        text_rect = text_surface.get_rect(center=(x, y))
        screen.blit(text_surface, text_rect)
    else:
        screen.blit(text_surface, (x, y))


def checkGameOver():
    '''
    Checks whrther the player had lost the game.
    '''
    global game_over_screen
    game_result = state.is_game_over()
    if game_result == 'failure':
        game_over_screen = True
    elif game_result == 'success':
        game_over_screen = True


class GameState:
    '''
    Represents the current state of the game and contains logic for validating
    and updating the game. This includes the state of both banks, the boat,
    and tracking moves.
    '''
    def __init__(self):
        '''
        Initializes the game state with the initial setup:
        - 3 missionaries and 3 cannibals on the left bank.
        - An empty boat positioned on the left bank.
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
        Verifies that the state of a given bank is valid.
        A valid state is one where missionaries are not outnumbered
        by cannibals, unless there are no missionaries on that bank.
        - bank: Dictionary representing the state of a bank.
        Returns True if the state is valid, otherwise False.
        '''
        missionaries = bank['missionaries']
        cannibals = bank['cannibals']
        return missionaries == 0 or missionaries >= cannibals

    def is_game_over(self):
        '''
        Determines if the game has reached a terminal state.
        Checks for success (all characters safely transported) or failure
        (a bank has more cannibals than missionaries).
        Returns:
        - 'success' if the game is won.
        - 'failure' if the game is lost.
        - None if the game is ongoing.
        '''
        if not self.is_valid_state(self.left_bank) or not self.is_valid_state(self.right_bank):
            return 'failure'
        if self.right_bank['missionaries'] == 3 and self.right_bank['cannibals'] == 3:
            return 'success'
        return None

    def move_boat(self):
        '''
        Initiates the movement of the boat to the opposite bank if it contains
        at least one character. Updates the move count accordingly.
        '''
        if self.boat['missionaries'] + self.boat['cannibals'] == 0:
            return
        self.boat_moving = True
        self.boat_target = 600 if self.boat_on_left else 200
        self.moves += 1

    def update_boat_position(self):
        '''
        Smoothly moves the boat toward its target position. Once the boat
        reaches its destination, switches its position to the opposite bank.
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


state = GameState()


def main():
    '''
    Runs the main game loop.
    '''
    global state
    global game_over_screen
    global game_result
    clock = pygame.time.Clock()
    running = True
    welcome_screen = True

    while running:
        screen.fill(BG_COL)
        screen.blit(BG_IMG, (0, 0))

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
            render_text("Missionaries and Cannibals", SCR_WID // 2, SCR_HIG // 4, 92, center=True)
            render_text("Get everyone across the river safely.", SCR_WID // 2, SCR_HIG // 3 + 20, center=True)
            render_text("Click to start", SCR_WID // 2, SCR_HIG - 120, center=True)
        elif game_over_screen:
            if game_result == 'success':
                render_text("You Won!", SCR_WID // 2, SCR_HIG // 3, 48, center=True)
            elif game_result == 'failure':
                render_text("Game Over!", SCR_WID // 2, SCR_HIG // 3, 96, center=True)
            render_text("Click to continue", SCR_WID // 2, SCR_HIG // 2, 36, center=True)
        else:
            game_result = state.update_boat_position()
            if game_result:
                game_over_screen = True
            draw_game_state()

        pygame.display.flip()
        clock.tick(FPS)

    pygame.quit()
    sys.exit()


def handle_click(pos):
    '''
    Processes mouse click events to interact with the game.
    Depending on the clicked position, the user can:
    - Move a character onto the boat.
    - Move a character off the boat.
    - Move the boat to the opposite bank.
    '''
    x, y = pos

    boat_x = state.boat_position if state.boat_moving else (200 if state.boat_on_left else 600)
    if boat_x < x < boat_x + 120 and 270 < y < 330:
        if state.boat['missionaries'] + state.boat['cannibals'] > 0:
            state.move_boat()
            checkGameOver()
        return

    if state.boat_on_left:
        for i in range(state.left_bank['missionaries']):
            if 50 + i * 50 < x < 50 + i * 50 + 80 and 150 < y < 230:
                move_character_to_boat(state.left_bank, 'missionaries')
                return
        for i in range(state.left_bank['cannibals']):
            if 50 + i * 50 < x < 50 + i * 50 + 80 and 250 < y < 330:
                move_character_to_boat(state.left_bank, 'cannibals')
                return

    if not state.boat_on_left:
        for i in range(state.right_bank['missionaries']):
            if 700 + i * 50 < x < 700 + i * 50 + 80 and 150 < y < 230:
                move_character_to_boat(state.right_bank, 'missionaries')
                return
        for i in range(state.right_bank['cannibals']):
            if 700 + i * 50 < x < 700 + i * 50 + 80 and 250 < y < 330:
                move_character_to_boat(state.right_bank, 'cannibals')
                return

    for i in range(state.boat['missionaries']):
        if boat_x + i * 50 < x < boat_x + i * 50 + 80 and 240 < y < 320:
            move_character_from_boat('missionaries')
            return
    for i in range(state.boat['cannibals']):
        if boat_x + 10 + i * 50 < x < boat_x + 10 + i * 50 + 80 and 240 < y < 320:
            move_character_from_boat('cannibals')
            return


def move_character_to_boat(bank, character_type):
    '''
    Transfers a character from a bank to the boat, ensuring the boat does not exceed
    its capacity. Decrements the count of the character type on the bank.
    '''
    if state.boat['missionaries'] + state.boat['cannibals'] < BOAT_CAPACITY and bank[character_type] > 0:
        bank[character_type] -= 1
        state.boat[character_type] += 1


def move_character_from_boat(character_type):
    '''
    Transfers a character from the boat to the respective bank.
    Increments the count of the character type on the bank.
    '''
    if state.boat[character_type] > 0:
        state.boat[character_type] -= 1
        if state.boat_on_left:
            state.left_bank[character_type] += 1
        else:
            state.right_bank[character_type] += 1


def draw_game_state():
    '''
    Draws the current game state, including:
    - Boat position and contents.
    - Characters on each bank.
    - Number of moves taken by the player.
    '''
    render_text(f"Moves: {state.moves}", 20, 20)

    boat_x = state.boat_position if state.boat_moving else (200 if state.boat_on_left else 600)
    screen.blit(BOAT_IMG, (boat_x, 250))

    for i in range(state.left_bank['missionaries']):
        screen.blit(MIS_IMG, (50 + i * 50, 150))
    for i in range(state.left_bank['cannibals']):
        screen.blit(CAN_IMG, (50 + i * 50, 250))

    for i in range(state.right_bank['missionaries']):
        screen.blit(MIS_IMG, (700 + i * 50, 150))
    for i in range(state.right_bank['cannibals']):
        screen.blit(CAN_IMG, (700 + i * 50, 250))

    character_index = 0
    for _ in range(state.boat['missionaries']):
        screen.blit(MIS_IMG, (boat_x + character_index * 50, 240))
        character_index += 1
    for _ in range(state.boat['cannibals']):
        screen.blit(CAN_IMG, (boat_x + character_index * 50, 240))
        character_index += 1


if __name__ == "__main__":
    main()
