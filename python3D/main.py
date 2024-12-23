import pyray as pr

pr.init_window(800, 450, "Zero City")
pr.set_target_fps(60)

camera = pr.Camera3D([18.0, 16.0, 18.0], [0.0, 0.0, 0.0], [0.0, 1.0, 0.0], 45.0, 0)

while not pr.window_should_close():
    pr.update_camera(camera, pr.CAMERA_ORBITAL)
    pr.begin_drawing()
    pr.clear_background(pr.RAYWHITE)
    pr.begin_mode_3d(camera)
    pr.draw_grid(20, 1.0)
    pr.end_mode_3d()
    pr.draw_text("Hello world", 190, 200, 20, pr.VIOLET)
    pr.end_drawing()
pr.close_window()
