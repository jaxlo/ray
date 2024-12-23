#include <stdio.h>
#include <math.h>
#include "raylib.h"

typedef struct Player {
    Vector2 position; // Raylib's Vector2 for position (x, y)
    int facingAngle;  // Rotation in degrees
    bool alive;
    Color color;
} Player;

// Function to rotate a point around an origin
Vector2 RotatePoint(Vector2 point, Vector2 origin, float angle) {
    float radians = angle * DEG2RAD; // Convert angle to radians
    float cosTheta = cosf(radians);
    float sinTheta = sinf(radians);

    // Translate point back to origin
    Vector2 translated = { point.x - origin.x, point.y - origin.y };

    // Rotate point
    Vector2 rotated = {
        translated.x * cosTheta - translated.y * sinTheta,
        translated.x * sinTheta + translated.y * cosTheta
    };

    // Translate point back to its original position
    rotated.x += origin.x;
    rotated.y += origin.y;

    return rotated;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Janks");

    Player mainPlayer = { .position = { 100, 200 }, .facingAngle = 360, .alive = true }; // 270 degrees is up

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {    // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // Main player movement
        if (IsKeyDown(KEY_LEFT)) mainPlayer.facingAngle -= 2; // Rotate left
        if (IsKeyDown(KEY_RIGHT)) mainPlayer.facingAngle += 2; // Rotate right

        // Keep angle within 0-360
        if (mainPlayer.facingAngle >= 360) mainPlayer.facingAngle -= 360;
        if (mainPlayer.facingAngle < 0) mainPlayer.facingAngle += 360;

        // Move forward in the direction of rotation
        if (IsKeyDown(KEY_UP)) {
            float radians = mainPlayer.facingAngle * DEG2RAD; // Convert rotation to radians
            mainPlayer.position.x += sinf(radians) * 2.0f; // Move in the X direction
            mainPlayer.position.y -= cosf(radians) * 2.0f; // Move in the Y direction
        }

        // Move backward in the direction of rotation
        if (IsKeyDown(KEY_DOWN)) {
            float radians = mainPlayer.facingAngle * DEG2RAD; // Convert rotation to radians
            mainPlayer.position.x -= sinf(radians) * 2.0f; // Move in the X direction
            mainPlayer.position.y += cosf(radians) * 2.0f; // Move in the Y direction
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            // Setup
            ClearBackground(RAYWHITE);
            DrawText("Move with wasd or the arrow keys.", 20, 20, 20, LIGHTGRAY);
            DrawText("Shoot with spacebar.", 20, 40, 20, LIGHTGRAY);

            // Define the triangle's points relative to the player's position
            Vector2 p1 = { mainPlayer.position.x, mainPlayer.position.y - 14 }; // Top point
            Vector2 p2 = { mainPlayer.position.x - 6, mainPlayer.position.y + 6 }; // Bottom-left point
            Vector2 p3 = { mainPlayer.position.x + 6, mainPlayer.position.y + 6 }; // Bottom-right point

            // Rotate the points around the player's position
            p1 = RotatePoint(p1, mainPlayer.position, mainPlayer.facingAngle);
            p2 = RotatePoint(p2, mainPlayer.position, mainPlayer.facingAngle);
            p3 = RotatePoint(p3, mainPlayer.position, mainPlayer.facingAngle);

            // Draw the rotated triangle
            DrawTriangle(p1, p2, p3, GREEN);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}