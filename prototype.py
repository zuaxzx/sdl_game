import pygame

# Constants
WIDTH, HEIGHT = 800, 600
GRAVITY = 1000  # Pixels per second²
FRICTION = 0.98
PLAYER_JUMP = -400  # Initial jump velocity
PLAYER_SPEED = 300  # Horizontal speed

# Initialize pygame
pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
clock = pygame.time.Clock()

class Player:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.width = 40
        self.height = 60
        self.vel_x = 0
        self.vel_y = 0
        self.acc_y = GRAVITY  # Only gravity affects acceleration
        self.on_ground = False

    def update(self, dt):
        # Apply gravity
        self.vel_y += self.acc_y * dt

        # Apply velocity to position
        self.x += self.vel_x * dt
        self.y += self.vel_y * dt

        # Basic floor collision
        if self.y + self.height > HEIGHT:
            self.y = HEIGHT - self.height
            self.vel_y = 0
            self.on_ground = True
        else:
            self.on_ground = False

        # Apply friction
        self.vel_x *= FRICTION

    def jump(self):
        if self.on_ground:
            self.vel_y = PLAYER_JUMP
            self.on_ground = False

    def move(self, direction):
        self.vel_x = direction * PLAYER_SPEED

    def draw(self, screen):
        pygame.draw.rect(screen, (0, 255, 0), (self.x, self.y, self.width, self.height))

# Game Loop
player = Player(WIDTH // 2, HEIGHT - 100)
running = True

while running:
    dt = clock.tick(60) / 1000  # Delta time in seconds
    screen.fill((0, 0, 0))

    # Event Handling
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    keys = pygame.key.get_pressed()
    if keys[pygame.K_LEFT]:
        player.move(-1)
    elif keys[pygame.K_RIGHT]:
        player.move(1)
    else:
        player.move(0)

    if keys[pygame.K_SPACE]:
        player.jump()

    # Update and Draw
    player.update(dt)
    player.draw(screen)

    pygame.display.flip()

pygame.quit()
