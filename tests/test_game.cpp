#include "Ball.h"
#include "Box.h"
#include "Common.h"
#include <cstdio>
#include <cassert>

static int tests_passed = 0;
static int tests_failed = 0;

#define TEST(name) do { std::printf("  TEST: %-30s ... ", name); } while(0)
#define PASS() do { std::printf("PASS\n"); tests_passed++; } while(0)
#define FAIL(msg) do { std::printf("FAIL: %s\n", msg); tests_failed++; } while(0)

static void test_ball_left_wall_bounce()
{
    Ball b;
    b.x_position = 1;
    b.y_position = 10;
    b.x_velocity = -1;
    b.y_velocity = -1;
    b.moving = true;
    b.Update();
    if (b.x_velocity != 1) { FAIL("x_vel should become 1"); return; }
    if (b.x_position != 1) { FAIL("x_pos should stay 1 (bounce frame)"); return; }
    b.Update();
    if (b.x_position != 2) { FAIL("x_pos should be 2 after moving"); return; }
    PASS();
}

static void test_ball_right_wall_bounce()
{
    Ball b;
    b.x_position = WINDOW_WIDTH - 3;
    b.y_position = 10;
    b.x_velocity = 1;
    b.y_velocity = -1;
    b.moving = true;
    b.Update();
    if (b.x_position != WINDOW_WIDTH - 2) { FAIL("should move right one step"); return; }
    b.Update();
    if (b.x_velocity != -1) { FAIL("x_vel should reverse at right wall"); return; }
    if (b.x_position != WINDOW_WIDTH - 2) { FAIL("x_pos should stay at wall"); return; }
    PASS();
}

static void test_ball_top_wall_bounce()
{
    Ball b;
    b.x_position = 10;
    b.y_position = 1;
    b.x_velocity = 1;
    b.y_velocity = -1;
    b.moving = true;
    b.Update();
    if (b.y_velocity != 1) { FAIL("y_vel should become 1"); return; }
    if (b.y_position != 1) { FAIL("y_pos should stay 1 (bounce frame)"); return; }
    b.Update();
    if (b.y_position != 2) { FAIL("y_pos should be 2 after moving"); return; }
    PASS();
}

static void test_ball_not_moving()
{
    Ball b;
    b.x_position = 5;
    b.y_position = 5;
    b.x_velocity = 1;
    b.y_velocity = -1;
    b.moving = false;
    b.Update();
    if (b.x_position != 5) { FAIL("x should not change when not moving"); return; }
    if (b.y_position != 5) { FAIL("y should not change when not moving"); return; }
    PASS();
}

static void test_ball_bottom_falls()
{
    Ball b;
    b.x_position = 10;
    b.y_position = WINDOW_HEIGHT - 2;
    b.x_velocity = 0;
    b.y_velocity = 1;
    b.moving = true;
    b.Update();
    if (b.x_velocity != 0) { FAIL("x_vel should remain 0"); return; }
    if (b.y_velocity != 1) { FAIL("y_vel should remain 1 (bottom not a bounce)"); return; }
    PASS();
}

static void test_box_contains()
{
    Box bx;
    bx.x_position = 10;
    bx.y_position = 10;
    bx.width = 5;
    bx.height = 3;

    if (!bx.Contains(10, 10)) { FAIL("should contain top-left"); return; }
    if (!bx.Contains(14, 12)) { FAIL("should contain bottom-right"); return; }
    if (bx.Contains(9, 10)) { FAIL("should not contain left"); return; }
    if (bx.Contains(10, 9)) { FAIL("should not contain above"); return; }
    if (bx.Contains(15, 10)) { FAIL("should not contain right edge"); return; }
    if (bx.Contains(10, 13)) { FAIL("should not contain below"); return; }
    PASS();
}

static void test_box_contains_corner_cases()
{
    Box bx;
    bx.x_position = 5;
    bx.y_position = 5;
    bx.width = 1;
    bx.height = 1;

    if (!bx.Contains(5, 5)) { FAIL("single-pixel box should contain its pixel"); return; }
    if (bx.Contains(4, 5)) { FAIL("should not contain left"); return; }
    if (bx.Contains(5, 4)) { FAIL("should not contain above"); return; }
    if (bx.Contains(6, 5)) { FAIL("should not contain right"); return; }
    if (bx.Contains(5, 6)) { FAIL("should not contain below"); return; }
    PASS();
}

int main()
{
    std::printf("Ball tests:\n");
    TEST("Left wall bounce");        test_ball_left_wall_bounce();
    TEST("Right wall bounce");       test_ball_right_wall_bounce();
    TEST("Top wall bounce");         test_ball_top_wall_bounce();
    TEST("Not moving");              test_ball_not_moving();
    TEST("Bottom (falls through)");  test_ball_bottom_falls();

    std::printf("\nBox tests:\n");
    TEST("Contains basic");          test_box_contains();
    TEST("Contains edge cases");     test_box_contains_corner_cases();

    std::printf("\n%d passed, %d failed\n", tests_passed, tests_failed);
    return tests_failed > 0 ? 1 : 0;
}
