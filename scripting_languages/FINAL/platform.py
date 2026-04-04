import pygame
import sys

# Initialize Pygame
pygame.init()

# Screen dimensions
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600

# Colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

# Set up the display
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Platformer Game")

# Load assets
character_image = pygame.image.load("character.png")
projectile_image = pygame.image.load("projectile.png")
background_image = pygame.image.load("background.png")
platform_image = pygame.image.load("platform.png")

# Scale assets to fit the screen (adjust as needed)
character_image = pygame.transform.scale(character_image, (50, 50))
projectile_image = pygame.transform.scale(projectile_image, (20, 10))
platform_image = pygame.transform.scale(platform_image, (100, 20))

# Game clock
clock = pygame.time.Clock()
FPS = 60

# Character settings
character_speed = 5
character_jump_speed = -15
gravity = 0.8

class Button:
    def __init__(self, x, y, width, height, text):
        self.rect = pygame.Rect(x, y, width, height)
        self.text = text
        self.color = BLACK
        self.text_color = WHITE
        self.font = pygame.font.Font(None, 40)

    def draw(self, screen):
        pygame.draw.rect(screen, self.color, self.rect)
        text_surface = self.font.render(self.text, True, self.text_color)
        text_rect = text_surface.get_rect(center=self.rect.center)
        screen.blit(text_surface, text_rect)

    def is_clicked(self, pos):
        return self.rect.collidepoint(pos)

class Player(pygame.sprite.Sprite):
    def __init__(self, x, y):
        super().__init__()
        self.image = character_image
        self.rect = self.image.get_rect()
        self.rect.topleft = (x, y)
        self.vel_y = 0
        self.on_ground = False

    def update(self, keys):
        # Horizontal movement
        if keys[pygame.K_LEFT]:
            self.rect.x -= character_speed
        if keys[pygame.K_RIGHT]:
            self.rect.x += character_speed

        # Apply gravity
        self.vel_y += gravity
        self.rect.y += self.vel_y

        # Jump
        if keys[pygame.K_UP] and self.on_ground:
            self.vel_y = character_jump_speed
            self.on_ground = False

        # Check boundaries
        if self.rect.left < 0:
            self.rect.left = 0
        if self.rect.right > SCREEN_WIDTH:
            self.rect.right = SCREEN_WIDTH

class Projectile(pygame.sprite.Sprite):
    def __init__(self, x, y, direction):
        super().__init__()
        self.image = projectile_image
        self.rect = self.image.get_rect()
        self.rect.center = (x, y)
        self.speed = 8 * direction

    def update(self):
        self.rect.x += self.speed
        # Remove the projectile if it goes off-screen
        if self.rect.right < 0 or self.rect.left > SCREEN_WIDTH:
            self.kill()

class Platform(pygame.sprite.Sprite):
    def __init__(self, x, y):
        super().__init__()
        self.image = platform_image
        self.rect = self.image.get_rect()
        self.rect.topleft = (x, y)

# Groups
all_sprites = pygame.sprite.Group()
platforms = pygame.sprite.Group()
projectiles = pygame.sprite.Group()

# Create platforms
platform = Platform(200, 500)
platforms.add(platform)
all_sprites.add(platform)

# Create player
player = Player(100, 400)
all_sprites.add(player)

def check_collisions():
    for platform in platforms:
        if player.rect.colliderect(platform.rect) and player.vel_y > 0:
            player.rect.bottom = platform.rect.top
            player.on_ground = True
            player.vel_y = 0
            break
    else:
        player.on_ground = False

def game():
    running = True
    while running:
        screen.blit(background_image, (0, 0))

        keys = pygame.key.get_pressed()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_z:  # Shoot projectile
                    direction = 1 if keys[pygame.K_RIGHT] else -1
                    projectile = Projectile(player.rect.centerx, player.rect.centery, direction)
                    projectiles.add(projectile)
                    all_sprites.add(projectile)

        # Update
        player.update(keys)
        check_collisions()
        projectiles.update()

        # Draw everything
        all_sprites.draw(screen)
        pygame.display.flip()

        clock.tick(FPS)

def title_screen():
    title_font = pygame.font.Font(None, 80)
    title_text = title_font.render("Platformer Game", True, BLACK)
    title_rect = title_text.get_rect(center=(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 4))

    start_button = Button(SCREEN_WIDTH // 2 - 100, SCREEN_HEIGHT // 2, 200, 50, "Start")

    while True:
        screen.fill(WHITE)
        screen.blit(title_text, title_rect)
        start_button.draw(screen)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.MOUSEBUTTONDOWN:
                if start_button.is_clicked(event.pos):
                    return

        pygame.display.flip()
        clock.tick(FPS)

# Main program
title_screen()
game()