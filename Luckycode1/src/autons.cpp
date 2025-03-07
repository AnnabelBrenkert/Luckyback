#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

const int DRIVE_SPEED = 550;
const int TURN_SPEED = 300;
const int SWING_SPEED = 300;

///
// Constants
///
void default_constants() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(20.0, 0.0, 100.0);         // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(11.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(3.0, 0.05, 20.0, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 52.5);    // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions

  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.9);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
}

///
// Skills
///
void drive_example() {
// //SKILLS!

// //SKILLS!

// /////////////////////////////////////////////////////////LB dumps matchload 
// Intake1.move(127);
// Intake2.move(-127);
// pros::delay(800);

// Intake1.move(0);
// Intake2.move(-0);
// chassis.pid_drive_set(16_in, DRIVE_SPEED, false);
// pros::delay(600);

// /////////////////////////////////////////////////////////grab first mogo
// chassis.pid_turn_set(90_deg, 150);
// pros::delay(500);

// MOGO.set_value(0);
// chassis.pid_drive_set(-23_in, 50, false);
// pros::delay(1000);

// MOGO.set_value(1);
// pros::delay(100);

// /////////////////////////////////////////////////////////grab red rings 
// chassis.pid_turn_set(0_deg, TURN_SPEED);
// pros::delay(500);

// Intake1.move(127);
// Intake2.move(-127);
// pros::delay(10);

// chassis.pid_drive_set(21_in, DRIVE_SPEED, false);
// pros::delay(800);

// chassis.pid_turn_set(-90_deg, TURN_SPEED);
// pros::delay(500);

// chassis.pid_drive_set(15_in, DRIVE_SPEED, true);
// pros::delay(600);

// chassis.pid_turn_set(180_deg, TURN_SPEED);
// pros::delay(700);

// chassis.pid_drive_set(27_in, DRIVE_SPEED, true);
// pros::delay(1000);

// chassis.pid_turn_set(300_deg, 50);
// pros::delay(1500);

// chassis.pid_drive_set(13_in, DRIVE_SPEED, true);
// pros::delay(1000);

// ///////////////////////////////////////////////////////// put in corner 

// chassis.pid_turn_set(25_deg, TURN_SPEED);
// pros::delay(1000);

// chassis.pid_drive_set(-15_in, DRIVE_SPEED, true);
// pros::delay(1000);

// MOGO.set_value(0);
// Intake1.move(-127);
// Intake2.move(127);
// pros::delay(100);

// chassis.pid_turn_set(45_deg, TURN_SPEED);
// pros::delay(100);

// chassis.pid_drive_set(11_in, DRIVE_SPEED, true);
// pros::delay(800);

// /////////////////////////////////////////////////////////go grab second mogo

// Intake1.move(0);
// Intake2.move(-0);
// chassis.pid_turn_set(-90_deg, TURN_SPEED);
// pros::delay(1100);

// chassis.pid_drive_set(-47_in, DRIVE_SPEED, false);
// pros::delay(1100);
// chassis.pid_drive_set(-30_in, 40, false);
// pros::delay(1200);

// MOGO.set_value(1);
// pros::delay(100);

// /////////////////////////////////////////////////////////grab red rings 

// Intake1.move(127);
// Intake2.move(-127);
// chassis.pid_turn_set(0_deg, TURN_SPEED);
// pros::delay(500);

// chassis.pid_drive_set(21_in, DRIVE_SPEED, false);
// pros::delay(900);

// chassis.pid_turn_set(90_deg, TURN_SPEED);
// pros::delay(500);

// chassis.pid_drive_set(21_in, DRIVE_SPEED, true);
// pros::delay(800);

// chassis.pid_turn_set(180_deg, TURN_SPEED);
// pros::delay(500);

// chassis.pid_drive_set(29_in, DRIVE_SPEED, true);
// pros::delay(1000);

// chassis.pid_turn_set(-310_deg, 50);

// pros::delay(1500);

// chassis.pid_drive_set(14_in, DRIVE_SPEED, true);
// pros::delay(1000);

// chassis.pid_turn_set(-20_deg, TURN_SPEED);
// pros::delay(1000);

// ///////////////////////////////////////////////////////// put in corner 

// chassis.pid_drive_set(-17_in, DRIVE_SPEED, true);
// pros::delay(1300);

// MOGO.set_value(0);
// Intake1.move(-127);
// Intake2.move(127);
// pros::delay(100);

// chassis.pid_turn_set(-45_deg, TURN_SPEED);
// pros::delay(500);

// Intake1.move(-0);
// Intake2.move(0);
// chassis.pid_drive_set(21_in, DRIVE_SPEED, true);
// pros::delay(800);

// /////////////////////////////////////////////////////////score on wall stake 
// chassis.pid_turn_set(-0_deg, TURN_SPEED);
// pros::delay(1000);

// liftPID.target_set(300);
// chassis.pid_drive_set(40_in, DRIVE_SPEED, true);
// lift_wait();  // Wait for the lift to reach its target
// pros::delay(900);

// chassis.pid_turn_set(90_deg, TURN_SPEED);
// Intake1.move(127);
// Intake2.move(-127);
// pros::delay(600);

// chassis.pid_drive_set(12_in, 250, true);
// pros::delay(2000);

// Intake1.move(-227);
// Intake2.move(227);
// pros::delay(50);

// Intake1.move(0);
// Intake2.move(-0);
// lift_auto(3000);
// lift_wait();

// chassis.pid_drive_set(5_in, 250, true);
// pros::delay(500);

// chassis.pid_drive_set(-12_in, 250, true);
// pros::delay(600);

// /////////////////////////////////////////////////////////grab next wall stake ring 

// lift_auto(300);
// chassis.pid_turn_set(-0_deg, TURN_SPEED);
// lift_wait();
// pros::delay(100);


// Intake1.move(227);
// Intake2.move(-227);
// chassis.pid_drive_set(26_in, 250, true);
// pros::delay(2100);

// Intake1.move(-227);
// Intake2.move(227);
// pros::delay(50);

// Intake1.move(227);
// Intake2.move(-227);
// pros::delay(100);

// Intake1.move(0);
// Intake2.move(-0);
// lift_auto(800);
// lift_wait();

// /////////////////////////////////////////////////////////intake ring 
// chassis.pid_turn_set(-90_deg, TURN_SPEED);
// pros::delay(500);

// Intake1.move(80);
// Intake2.move(-80);
// chassis.pid_drive_set(27_in, DRIVE_SPEED, true);
// pros::delay(1000);

// /////////////////////////////////////////////////////////grab third mogo
// Intake1.move(0);
// Intake2.move(-0);
// chassis.pid_turn_set(135_deg, TURN_SPEED);
// pros::delay(900);

// chassis.pid_drive_set(-42_in, 55, true);
// pros::delay(1500);

// MOGO.set_value(1);
// pros::delay(100);

// /////////////////////////////////////////////////////////fill up mogo
// chassis.pid_turn_set(210_deg, TURN_SPEED);
// pros::delay(500);

// Intake1.move(127);
// Intake2.move(-127);
// chassis.pid_drive_set(30_in, DRIVE_SPEED, true);
// pros::delay(900);

// chassis.pid_turn_set(270_deg, TURN_SPEED);
// pros::delay(500);

// chassis.pid_drive_set(22_in, DRIVE_SPEED, true);
// pros::delay(800);

// chassis.pid_turn_set(205_deg, TURN_SPEED);
// pros::delay(500);

// chassis.pid_drive_set(22_in, DRIVE_SPEED, true);
// pros::delay(700);

// /////////////////////////////////////////////////////////score on second wall stake
// chassis.pid_turn_set(270_deg, TURN_SPEED);
// pros::delay(400);

// lift_auto(3000);
// lift_wait();

// Intake1.move(0);
// Intake2.move(-0);
// chassis.pid_drive_set(8_in, DRIVE_SPEED, true);
// pros::delay(300);

// chassis.pid_drive_set(-2_in, DRIVE_SPEED, true);
// lift_auto(900);
// lift_wait();

// /////////////////////////////////////////////////////////intake last two rings 
// chassis.pid_turn_set(-5_deg, TURN_SPEED);
// pros::delay(200);

// //arm.set_value(1);
// Intake1.move(127);
// Intake2.move(-127);
// chassis.pid_drive_set(42_in, DRIVE_SPEED, true);
// pros::delay(1800);

// chassis.pid_turn_set(90_deg, TURN_SPEED);
// pros::delay(700);

// chassis.pid_drive_set(8_in, DRIVE_SPEED, true);
// pros::delay(700);

// /////////////////////////////////////////////////////////put into corner 

// chassis.pid_turn_set(135_deg, TURN_SPEED);
// pros::delay(500);

// MOGO.set_value(0);
// chassis.pid_drive_set(-15_in, DRIVE_SPEED, true);
// pros::delay(800);

// Intake1.move(-127);
// Intake2.move(127);
// pros::delay(10);

// chassis.pid_drive_set(8_in, DRIVE_SPEED, true);
// pros::delay(500);

// chassis.pid_drive_set(-25_in, DRIVE_SPEED, true);
// pros::delay(500);

// Intake1.move(-0);
// Intake2.move(0);
// chassis.pid_drive_set(17_in, DRIVE_SPEED, true);
// pros::delay(500);

// /////////////////////////////////////////////////////////put last stake into corner 

// chassis.pid_turn_set(75_deg, TURN_SPEED);
// pros::delay(500);

// chassis.pid_drive_set(115_in, 127, true);
// pros::delay(2300);

// /////////////////////////////////////////////////////////hang 

// lift_auto(3000);
// chassis.pid_turn_set(45_deg, TURN_SPEED);
// lift_wait();

// chassis.pid_drive_set(-65_in, 127, true);
// pros::delay(1500);
 
}

///
// Red Front
///
void turn_example() {
//red front

// chassis.pid_drive_set(-17_in, DRIVE_SPEED, false);
// pros::delay(800);

// chassis.pid_swing_set(ez::RIGHT_SWING, 60_deg, 60, 20);
// pros::delay(900);

// chassis.pid_swing_set(ez::LEFT_SWING, 5_deg, 70, 10);
// pros::delay(800);

// chassis.pid_drive_set(-2_in, DRIVE_SPEED, false);
// pros::delay(500);

// MOGO.set_value(1);
// pros::delay(100);



// chassis.pid_drive_set(10_in, DRIVE_SPEED, false);
// pros::delay(500);

// MOGO.set_value(0);
// pros::delay(100);

// chassis.pid_drive_set(-5_in, DRIVE_SPEED, false);
// pros::delay(500);

// MOGO.set_value(1);
// pros::delay(100);

// Intake1.move(127);
// Intake2.move(-127);
// chassis.pid_turn_set(-20_deg, TURN_SPEED);
// pros::delay(500);

// chassis.pid_drive_set(12_in, DRIVE_SPEED, false);
// pros::delay(1000);

// chassis.pid_turn_set(-225_deg, TURN_SPEED);
// pros::delay(500);

// MOGO.set_value(0);
// pros::delay(100);

// chassis.pid_turn_set(-90_deg, TURN_SPEED);
// pros::delay(500);

// chassis.pid_drive_set(-23_in, 50, false);
// pros::delay(2000);

// MOGO.set_value(1);
// pros::delay(100);

// PNUEINT.set_value(1);
// chassis.pid_turn_set(45_deg, TURN_SPEED);
// pros::delay(500);

// chassis.pid_drive_set(24_in, DRIVE_SPEED, false);
// pros::delay(1000);

// PNUEINT.set_value(0);
// pros::delay(1000);

// Intake1.move(0);
// Intake2.move(-0);
// pros::delay(100);

// chassis.pid_drive_set(-15_in, DRIVE_SPEED, false);
// pros::delay(1000);

// chassis.pid_turn_set(-45_deg, TURN_SPEED);
// pros::delay(500);

// lift_auto(900);
// lift_wait();

// chassis.pid_drive_set(-20_in, DRIVE_SPEED, false);
// pros::delay(1000);
}

///
// Blue front
///
void drive_and_turn() {
  // blue front

// chassis.pid_drive_set(-20_in, DRIVE_SPEED, false);
// pros::delay(800);

// chassis.pid_swing_set(ez::LEFT_SWING, -60_deg, 70, 10);
// pros::delay(900);

// chassis.pid_swing_set(ez::RIGHT_SWING, -0_deg, 70, 10);
// pros::delay(800);

// chassis.pid_drive_set(-3_in, DRIVE_SPEED, false);
// pros::delay(500);

// MOGO.set_value(1);
// pros::delay(100);



// chassis.pid_drive_set(15_in, DRIVE_SPEED, false);
// pros::delay(500);

// MOGO.set_value(0);
// pros::delay(100);

// chassis.pid_drive_set(-5_in, DRIVE_SPEED, false);
// pros::delay(500);

// MOGO.set_value(1);
// pros::delay(100);

// Intake1.move(127);
// Intake2.move(-127);
// chassis.pid_turn_set(20_deg, 70);
// pros::delay(700);

// chassis.pid_drive_set(12_in, DRIVE_SPEED, false);
// pros::delay(1200);


// chassis.pid_turn_set(180_deg, TURN_SPEED);
// pros::delay(500);

// MOGO.set_value(0);
// pros::delay(500);

// chassis.pid_turn_set(90_deg, TURN_SPEED);
// pros::delay(500);

// chassis.pid_drive_set(-22_in, 70, false);
// pros::delay(1500);

// MOGO.set_value(1);
// pros::delay(100);

// PNUEINT.set_value(1);
// chassis.pid_turn_set(-45_deg, TURN_SPEED);
// pros::delay(500);

// chassis.pid_drive_set(27_in, DRIVE_SPEED, false);
// pros::delay(1200);

// PNUEINT.set_value(0);
// pros::delay(1000);

// chassis.pid_drive_set(-18_in, DRIVE_SPEED, false);
// pros::delay(1000);

// chassis.pid_turn_set(45_deg, TURN_SPEED);
// pros::delay(500);

// Intake1.move(0);
// Intake2.move(-0);
// lift_auto(900);
// lift_wait();

// chassis.pid_drive_set(-20_in, DRIVE_SPEED, false);
// pros::delay(1000);
}

///
// red back 
///
void wait_until_change_speed() {
 //red back
// chassis.pid_turn_set(55_deg, 70);
// pros::delay(700);

// chassis.pid_drive_set(12_in, DRIVE_SPEED, false);
// pros::delay(800);

// lift_auto(2000);
// lift_wait();

// // chassis.pid_turn_set(90_deg, 70);
// // pros::delay(700);

// lift_auto(0);
// lift_wait();

// chassis.pid_turn_set(70_deg, 70);
// pros::delay(700);

// chassis.pid_drive_set(-28_in, DRIVE_SPEED, false);
// pros::delay(1000);

// MOGO.set_value(1);
// pros::delay(100);

// // Intake1.move(127);
// // Intake2.move(-127);
// // chassis.pid_turn_set(90_deg, 70);
// // pros::delay(700);
}

///
// Blue back
///
void swing_example() {
 
}

///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // Your final motion should still be a normal pid_wait
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Odom Drive PID
///
void odom_drive_example() {
  // This works the same as pid_drive_set, but it uses odom instead!
  // You can replace pid_drive_set with pid_odom_set and your robot will
  // have better error correction.

  chassis.pid_odom_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_odom_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
}

///
// Odom Pure Pursuit
///
void odom_pure_pursuit_example() {
  // Drive to 0, 30 and pass through 6, 10 and 0, 20 on the way, with slew
  chassis.pid_odom_set({{{6_in, 10_in}, fwd, DRIVE_SPEED},
                        {{0_in, 20_in}, fwd, DRIVE_SPEED},
                        {{0_in, 30_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait();

  // Drive to 0, 0 backwards
  chassis.pid_odom_set({{0_in, 0_in}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}

///
// Odom Pure Pursuit Wait Until
///
void odom_pure_pursuit_wait_until_example() {
  chassis.pid_odom_set({{{0_in, 24_in}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait_until_index(1);  // Waits until the robot passes 12, 24
  // Intake.move(127);  // Set your intake to start moving once it passes through the second point in the index
  chassis.pid_wait();
  // Intake.move(0);  // Turn the intake off
}

///
// Odom Boomerang
///
void odom_boomerang_example() {
  chassis.pid_odom_set({{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
                       true);
  chassis.pid_wait();

  chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}

///
// Odom Boomerang Injected Pure Pursuit
///
void odom_boomerang_injected_pure_pursuit_example() {
  chassis.pid_odom_set({{{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait();

  chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}

///
// Calculate the offsets of your tracking wheels
///
void measure_offsets() {
  // Number of times to test
  int iterations = 10;

  // Our final offsets
  double l_offset = 0.0, r_offset = 0.0, b_offset = 0.0, f_offset = 0.0;

  // Reset all trackers if they exist
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->reset();
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->reset();
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->reset();
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->reset();
  
  for (int i = 0; i < iterations; i++) {
    // Reset pid targets and get ready for running an auton
    chassis.pid_targets_reset();
    chassis.drive_imu_reset();
    chassis.drive_sensor_reset();
    chassis.drive_brake_set(MOTOR_BRAKE_HOLD);
    chassis.odom_xyt_set(0_in, 0_in, 0_deg);
    double imu_start = chassis.odom_theta_get();
    double target = i % 2 == 0 ? 90 : 270;  // Switch the turn target every run from 270 to 90

    // Turn to target at half power
    chassis.pid_turn_set(target, 63, ez::raw);
    chassis.pid_wait();
    pros::delay(250);

    // Calculate delta in angle
    double t_delta = util::to_rad(fabs(util::wrap_angle(chassis.odom_theta_get() - imu_start)));

    // Calculate delta in sensor values that exist
    double l_delta = chassis.odom_tracker_left != nullptr ? chassis.odom_tracker_left->get() : 0.0;
    double r_delta = chassis.odom_tracker_right != nullptr ? chassis.odom_tracker_right->get() : 0.0;
    double b_delta = chassis.odom_tracker_back != nullptr ? chassis.odom_tracker_back->get() : 0.0;
    double f_delta = chassis.odom_tracker_front != nullptr ? chassis.odom_tracker_front->get() : 0.0;

    // Calculate the radius that the robot traveled
    l_offset += l_delta / t_delta;
    r_offset += r_delta / t_delta;
    b_offset += b_delta / t_delta;
    f_offset += f_delta / t_delta;
  }

  // Average all offsets
  l_offset /= iterations;
  r_offset /= iterations;
  b_offset /= iterations;
  f_offset /= iterations;

  // Set new offsets to trackers that exist
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->distance_to_center_set(l_offset);
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->distance_to_center_set(r_offset);
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->distance_to_center_set(b_offset);
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->distance_to_center_set(f_offset);
}

// . . .
// Make your own autonomous functions here!
// . . .