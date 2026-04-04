import pygame
import sys

SCR_WDT = 1200  # SCREEN WIDTH
SCR_HGH = 800  # SCREEN HEIGHT

BAL_SIZ = 15  # BALL SIZE
BAL_SPD = [4, 4]  # BALL SPEED

PDL_WDT = 15  # PADDLE WIDTH
PDL_HGH = 150  # PADDLE HEIGHT
PDL_SPD = 8  # PADDLE SPEED

COL_WHI = (255, 255, 255)
COL_BLK = (0, 0, 0)
COL_GRY = (22, 22, 22)

FPS = 60

pygame.init()
screen = pygame.display.set_mode((SCR_WDT, SCR_HGH))
pygame.display.set_caption("PONG by Bartłomiej Ćwiklak")
clock = pygame.time.Clock()

ball = pygame.Rect(SCR_WDT // 2 - BAL_SIZ // 2, SCR_HGH // 2 - BAL_SIZ // 2,
                        BAL_SIZ, BAL_SIZ)
player_paddle = pygame.Rect(SCR_WDT - PDL_WDT - 10, SCR_HGH // 2 - PDL_HGH // 2,
                        PDL_WDT, PDL_HGH)
opponent_paddle = pygame.Rect(10, SCR_HGH // 2 - PDL_HGH // 2, PDL_WDT, PDL_HGH)

ball_multiplier = 1.0
player_score = 0
opponent_score = 0
mode = 0
font = pygame.font.Font(None, 36)
score = pygame.font.Font(None, 1000)


def draw_objects():
    """
    Draws all objects and UI elements on the screen.
    This includes:
    - Filling the screen with a COL_BLK background.
    - Drawing the player and opponent scores.
    - Drawing the player paddle, opponent paddle, and the ball.
    - Displaying the FPS counter at the top of the screen.
    """
    screen.fill(COL_BLK)
    player_text = score.render(str(player_score), True, COL_GRY)
    opponent_text = score.render(str(opponent_score), True, COL_GRY)
    screen.blit(player_text, (SCR_WDT // 2 + 130, 80))
    screen.blit(opponent_text, (100, 80))
    pygame.draw.rect(screen, COL_WHI, player_paddle)
    pygame.draw.rect(screen, COL_WHI, opponent_paddle)
    pygame.draw.ellipse(screen, COL_WHI, ball)
    fps_txt = font.render("FPS: " + str(round(clock.get_fps(), 1)), True, COL_WHI)
    screen.blit(fps_txt, (SCR_WDT // 2 - 50, 20))


def move_ball():
    """
    Moves the ball and handles its collisions with paddles and screen edges.
    - Updates the ball's position based on its speed and multiplier.
    - Reflects the ball if it hits the top or bottom of the screen.
    - Reflects the ball if it collides with either paddle.
    - Resets the ball position and updates scores if it goes
      off-screen on either side.
    """
    global player_score, opponent_score, ball_multiplier

    ball_multiplier += 0.001

    ball.x += BAL_SPD[0] * ball_multiplier
    ball.y += BAL_SPD[1] * ball_multiplier

    if ball.top <= 0 or ball.bottom >= SCR_HGH:
        BAL_SPD[1] = -BAL_SPD[1]

    if ball.colliderect(player_paddle) or ball.colliderect(opponent_paddle):
        BAL_SPD[0] = -BAL_SPD[0]

    if ball.left <= 0:
        player_score += 1
        ball_multiplier = 1
        reset_ball()
    if ball.right >= SCR_WDT:
        opponent_score += 1
        ball_multiplier = 1
        reset_ball()


def reset_paddles():
    """
    Resets the paddles to their starting positions at the center
    of their respective sides.
    Ensures paddles stay within the screen boundaries.
    """
    player_paddle.center = (SCR_WDT - PDL_WDT - 10, SCR_HGH // 2 - PDL_HGH // 2)
    opponent_paddle.center = (10, SCR_HGH // 2 - PDL_HGH // 2)
    player_paddle.clamp_ip(screen.get_rect())
    opponent_paddle.clamp_ip(screen.get_rect())


def move_paddles(keys):
    """
    Handles the movement of the player's paddle based on keyboard input.
    - Moves the paddle up or down if the corresponding keys (up/down arrow)
      are pressed.
    - Ensures the paddle stays within the screen boundaries.
    """
    if keys[pygame.K_UP] and player_paddle.top > 0:
        player_paddle.y -= PDL_SPD
    if keys[pygame.K_DOWN] and player_paddle.bottom < SCR_HGH:
        player_paddle.y += PDL_SPD
    player_paddle.clamp_ip(screen.get_rect())
    opponent_paddle.clamp_ip(screen.get_rect())


def single_paddles(keys):
    """
    Moves the opponent paddle automatically in singleplayer mode.
    - The paddle follows the ball's vertical position to simulate
      an AI opponent.
    """
    if opponent_paddle.centery < ball.centery:
        opponent_paddle.y += PDL_SPD
    if opponent_paddle.centery > ball.centery:
        opponent_paddle.y -= PDL_SPD
    player_paddle.clamp_ip(screen.get_rect())
    opponent_paddle.clamp_ip(screen.get_rect())


def multi_paddles(keys):
    """
    Handles the movement of the opponent paddle based on keyboard input
    in multiplayer mode.
    - Uses the 'W' and 'S' keys to move the opponent paddle up and down.
    - Ensures the paddle stays within the screen boundaries.
    """
    if keys[pygame.K_w] and opponent_paddle.top > 0:
        opponent_paddle.y -= PDL_SPD
    if keys[pygame.K_s] and opponent_paddle.bottom < SCR_HGH:
        opponent_paddle.y += PDL_SPD
    player_paddle.clamp_ip(screen.get_rect())
    opponent_paddle.clamp_ip(screen.get_rect())


def reset_ball():
    """
    Resets the ball to the center of the screen and reverses its horizontal direction.
    """
    ball.center = (SCR_WDT // 2, SCR_HGH // 2)
    BAL_SPD[0] *= -1


def end_screen():
    """
    Displays the end screen after a player wins or the game ends.
    - Shows the scores for both players and a button to return to the main menu.
    - Handles user input for returning to the menu or quitting the game.
    """
    button_font = pygame.font.Font(None, 48)
    title_font = pygame.font.Font(None, 110)
    button_back_text = button_font.render("Back to menu", True, COL_BLK)
    button_back_rect = button_back_text.get_rect(center=(SCR_WDT // 2, SCR_HGH // 2 + 250))
    end_title = title_font.render(str("Game Ended"), True, COL_WHI)
    left_score = button_font.render(str("Left player score: " + str(opponent_score)), True, COL_WHI)
    right_score = button_font.render(str("Right player score: " + str(player_score)), True, COL_WHI)

    running = True

    while running:
        screen.fill(COL_BLK)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.MOUSEBUTTONDOWN:
                if button_back_rect.collidepoint(event.pos):
                    main_menu()
                    return

        pygame.draw.rect(screen, COL_WHI, button_back_rect.inflate(40, 20))
        screen.blit(button_back_text, button_back_rect)
        screen.blit(end_title, (SCR_WDT // 2 - 240, SCR_HGH // 2 - 250))
        screen.blit(left_score, (SCR_WDT // 2 - 200, SCR_HGH // 2))
        screen.blit(right_score, (SCR_WDT // 2 - 200, SCR_HGH // 2 + 50))
        pygame.display.flip()


def main_menu():
    """
    Displays the main menu, allowing the user to select the game mode or quit.
    - Provides options for singleplayer, multiplayer, and quitting the game.
    """
    button_font = pygame.font.Font(None, 48)
    title_font = pygame.font.Font(None, 128)
    button_single_text = button_font.render("Singleplayer", True, COL_BLK)
    button_single_rect = button_single_text.get_rect(center=(SCR_WDT // 2, SCR_HGH // 2))
    button_multi_text = button_font.render(" Multiplayer ", True, COL_BLK)
    button_multi_rect = button_multi_text.get_rect(center=(SCR_WDT // 2, SCR_HGH // 2 + 70))
    button_quit_text = button_font.render("   Quit   ", True, COL_BLK)
    button_quit_rect = button_quit_text.get_rect(center=(SCR_WDT // 2, SCR_HGH // 2 + 210))
    menu_title = title_font.render(str("Pong Game"), True, COL_WHI)

    running = True

    global mode, player_score, opponent_score, ball_multiplier

    while running:
        screen.fill(COL_BLK)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.MOUSEBUTTONDOWN:
                if button_single_rect.collidepoint(event.pos):
                    mode = 0
                    player_score = 0
                    opponent_score = 0
                    reset_paddles()
                    reset_ball()
                    ball_multiplier = 1
                    return
                if button_multi_rect.collidepoint(event.pos):
                    mode = 1
                    player_score = 0
                    opponent_score = 0
                    reset_paddles()
                    reset_ball()
                    ball_multiplier = 1
                    return
                if button_quit_rect.collidepoint(event.pos):
                    pygame.quit()
                    sys.exit()

        pygame.draw.rect(screen, COL_WHI, button_single_rect.inflate(40, 20))
        pygame.draw.rect(screen, COL_WHI, button_multi_rect.inflate(40, 20))
        pygame.draw.rect(screen, COL_WHI, button_quit_rect.inflate(40, 20))
        screen.blit(button_single_text, button_single_rect)
        screen.blit(button_multi_text, button_multi_rect)
        screen.blit(button_quit_text, button_quit_rect)
        screen.blit(menu_title, (SCR_WDT // 2 - 250, SCR_HGH // 2 - 220))

        pygame.display.flip()
        clock.tick(FPS)


def main():
    """
    The main game loop.
    - Starts by displaying the main menu.
    - Handles game logic, rendering, and user input for singleplayer
    and multiplayer modes.
    - Ends the game if a player reaches the score limit or the escape
    key is pressed.
    """
    global player_score, opponent_score
    main_menu()

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

        global mode
        keys = pygame.key.get_pressed()
        if mode == 0:
            single_paddles(keys)
        else:
            multi_paddles(keys)

        move_paddles(keys)
        move_ball()
        draw_objects()

        if keys[pygame.K_ESCAPE] or player_score == 7 or opponent_score == 7:
            end_screen()

        pygame.display.flip()
        clock.tick(FPS)


if __name__ == "__main__":
    main()
