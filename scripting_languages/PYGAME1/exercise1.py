import pygame, random, sys

win = (800, 800)
white = pygame.Color("white")
pygame.init()
s = pygame.display.set_mode(win)
s.fill(white)

for i in range(100):
    rgb = random.randint(0,0xFFFFFFFF)
    color = pygame.color.Color(rgb)
    size = (random.randint(1,win[1]))
    orig = (random.randint(1,win[0]))
    rad = random.randint(10,100)
    rect = (orig, size)
    pygame.draw.circle(s, color, rect, rad)
    pygame.display.flip()

while True:
    for event in pygame.event.get():
        if event.type in (pygame.QUIT, pygame.MOUSEBUTTONDOWN):
            pygame.quit()
            sys.exit()
