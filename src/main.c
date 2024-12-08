#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

constexpr size_t MAP_BUFFER_SIZE = 64;
constexpr int    TILE_WIDTH      = 80;
constexpr int    TILE_HEIGHT     = 60;
constexpr int    MAP_ROWS        = 8;
constexpr int    MAP_COLS        = 8;

constexpr int WIDTH  = 640;
constexpr int HEIGHT = 480;
const char *TITLE    = "Raycasting";

const bool MAP[MAP_BUFFER_SIZE] = {
  true, true, true, true, true, true, true ,true,
  true, false, false, false, false, false, false, true,
  true, false, false, false, false, false, false, true,
  true, false, false, false, false, false, false, true,
  true, false, false, false, false, false, false, true,
  true, false, false, false, false, false, false, true,
  true, false, false, false, false, false, false, true,
  true, true, true, true, true, true, true ,true,
};

struct Segment
{
  Vector2 origin;
  Vector2 direction;
};
struct Player
{
  Vector2 origin;
  float fov;
};
typedef struct Segment Segment;
typedef struct Player  Player;

void draw_2d_map()
{
  int x = 0;
  int y = 0;
  for(size_t i = 0; i < MAP_ROWS; i++)
  {
	for(size_t j = 0; j < MAP_COLS; j++)
	{
	  Color tile_color = {255, 255, 255, 255};
	  if(MAP[i * MAP_ROWS + j])
	  {
		tile_color = (Color){255, 0, 0, 255};
	  }
	  DrawRectangle(x, y, TILE_WIDTH, TILE_HEIGHT, tile_color);
	  DrawRectangleLines(x, y, TILE_WIDTH, TILE_HEIGHT, (Color){0, 0, 0, 255});

	  x += TILE_WIDTH;
	}
	x = 0;
	y += TILE_HEIGHT;
  }
}
void draw_player(const Player *player)
{
  DrawCircleV(player->origin, 10, (Color){255, 0, 255, 255});
}
void draw_ray(const Segment* ray)
{
  Vector2 ray_end = (Vector2){ray->direction.x * 10, ray->direction.y * 10};
  DrawLineV(ray->origin, ray_end, (Color){0, 255, 0, 255});
}
int main(int argc, [[maybe_unused]]char *argv[argc + 1])
{
  InitWindow(WIDTH, HEIGHT, TITLE);
  Player player = (Player){
	.origin=(Vector2){WIDTH/2.0f - 10.f, HEIGHT/2.0f - 10.f},
	.fov=60.0f
  };
  Segment ray = (Segment){
	.origin=player.origin,
	.direction=(Vector2){1.f, -1.f},
  };
  while(!WindowShouldClose())
  {
	BeginDrawing();
	ClearBackground((Color){0, 0, 0, 255});
	draw_2d_map();
	draw_ray(&ray);
	draw_player(&player);
	EndDrawing();
	
  }
  CloseWindow();
  return EXIT_SUCCESS;
}
