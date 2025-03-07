#include "main.h"
#include "EZ-Template/util.hpp"
#include "autons.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rotation.h"
#include "pros/rotation.hpp"
#include "subsystems.hpp"


const int DRIVE_SPEED = 105;
const int TURN_SPEED = 87;
const int SWING_SPEED = 100;

/*clamp Variables*/
	bool lastKnownButtonBState;
	int ClampState = 0; /*0 = off, 1 = Grab*/
  int rotateState = 0;

  extern pros::Motor Intake1;
  extern pros::Motor Intake2;
  extern pros::Motor LB;
  extern pros::Controller master;
  
  extern pros::adi::DigitalOut MOGO;
  extern pros::adi::DigitalOut arm;
  pros::Motor Intake1(9);
  pros::Motor Intake2(11);
  pros::Motor LB (4);
  pros::Controller master (pros::E_CONTROLLER_MASTER);
      #define MOGO_PORT 'a'
      #define ARM_PORT 'f'
      #define intakep 'b'
      #define LIMIT_SWITCH 'h'
  pros::Rotation rot(12);
  pros::adi::DigitalOut MOGO(MOGO_PORT);
  pros::adi::DigitalOut arm(ARM_PORT);
  pros::adi::DigitalOut PNUEINT(intakep);
  
  ez::PID liftPID{0.45, 0, 0, 0, "Lift"};
  
  inline void set_lift(int input) {
      LB.move(input);
      LB.move(input);
    }


// Chassis constructor
ez::Drive chassis(
    {-19, -20, -7},     // Left Chassis Ports (negative port will reverse it!)
    {18, 17, 5},  // Right Chassis Ports (negative port will reverse it!)

    16,      // IMU Port
    3.25,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
    450);   // Wheel RPM = cartridge * (motor gear / wheel gear)

// Uncomment the trackers you're using here!
// - `8` and `9` are smart ports (making these negative will reverse the sensor)
//  - you should get positive values on the encoders going FORWARD and RIGHT
// - `2.75` is the wheel diameter
// - `4.0` is the distance from the center of the wheel to the center of the robot
// ez::tracking_wheel horiz_tracker(8, 2.75, 4.0);  // This tracking wheel is perpendicular to the drive wheels
// ez::tracking_wheel vert_tracker(9, 2.75, 4.0);   // This tracking wheel is parallel to the drive wheels

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::ez_template_print();

  pros::delay(500);  // Stop the user from doing anything while legacy ports configure

  // Look at your horizontal tracking wheel and decide if it's in front of the midline of your robot or behind it
  //  - change `back` to `front` if the tracking wheel is in front of the midline
  //  - ignore this if you aren't using a horizontal tracker
  // chassis.odom_tracker_back_set(&horiz_tracker);
  // Look at your vertical tracking wheel and decide if it's to the left or right of the center of the robot
  //  - change `left` to `right` if the tracking wheel is to the right of the centerline
  //  - ignore this if you aren't using a vertical tracker
  // chassis.odom_tracker_left_set(&vert_tracker);

  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(true);   // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0.0);   // Sets the active brake kP. We recommend ~2.  0 will disable.
  chassis.opcontrol_curve_default_set(7, 0.0);  // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)
  LB.tare_position();
  // Set the drive to your own constants from autons.cpp!
  default_constants();
  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);  // If using tank, only the left side is used.
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);


  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  master.rumble(chassis.drive_imu_calibrated() ? "." : "---");

  liftPID.exit_condition_set(80, 50, 300, 150, 500, 500);

}

void lift_auto(double target) {
  liftPID.target_set(target);
  while (liftPID.exit_condition(LB, true) == ez::RUNNING) {
    double output = liftPID.compute(LB.get_position());
    set_lift(output);
    pros::delay(ez::util::DELAY_TIME);
  }
  set_lift(0);
}

void disabled() {
  // . . .
}


void competition_initialize() {
  // . . .
}

void lift_task() {
  pros::delay(2000);  // Set EZ-Template calibrate before this function starts running
  while (true) {
    set_lift(liftPID.compute(LB.get_position()));

    pros::delay(ez::util::DELAY_TIME);
  }
}
pros::Task Lift_Task(lift_task);  // Create the task, this will cause the function to start running

inline void lift_wait() {
  while (liftPID.exit_condition(LB, true) == ez::RUNNING) {
    pros::delay(ez::util::DELAY_TIME);
  }
}

void autonomous() {
  chassis.pid_targets_reset();                // Resets PID targets to 0
  chassis.drive_imu_reset();                  // Reset gyro position to 0
  chassis.drive_sensor_reset();               // Reset drive sensors to 0
 // chassis.odom_xyt_set(0_in, 0_in, 0_deg);    // Set the current position, you can start at a specific position with this
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency

// ez::as::auton_selector.selected_auton_call();  // Calls selected auton from autonomous selector


//SKILLS!

/////////////////////////////////////////////////////////LB dumps matchload 
Intake1.move(127);
Intake2.move(-127);
pros::delay(800);

Intake1.move(0);
Intake2.move(-0);
chassis.pid_drive_set(16_in, DRIVE_SPEED, false);
pros::delay(600);

/////////////////////////////////////////////////////////grab first mogo
chassis.pid_turn_set(90_deg, 150);
pros::delay(500);

MOGO.set_value(0);
chassis.pid_drive_set(-23_in, 50, false);
pros::delay(1000);

MOGO.set_value(1);
pros::delay(100);

/////////////////////////////////////////////////////////grab red rings 
chassis.pid_turn_set(0_deg, TURN_SPEED);
pros::delay(500);

Intake1.move(127);
Intake2.move(-127);
pros::delay(10);

chassis.pid_drive_set(21_in, DRIVE_SPEED, false);
pros::delay(800);

chassis.pid_turn_set(-90_deg, TURN_SPEED);
pros::delay(500);

chassis.pid_drive_set(15_in, DRIVE_SPEED, true);
pros::delay(600);

chassis.pid_turn_set(180_deg, TURN_SPEED);
pros::delay(700);

chassis.pid_drive_set(27_in, DRIVE_SPEED, true);
pros::delay(1000);

chassis.pid_turn_set(300_deg, 50);
pros::delay(1500);

chassis.pid_drive_set(13_in, DRIVE_SPEED, true);
pros::delay(1000);

///////////////////////////////////////////////////////// put in corner 

chassis.pid_turn_set(25_deg, TURN_SPEED);
pros::delay(1000);

chassis.pid_drive_set(-15_in, DRIVE_SPEED, true);
pros::delay(1000);

MOGO.set_value(0);
Intake1.move(-127);
Intake2.move(127);
pros::delay(100);

chassis.pid_turn_set(45_deg, TURN_SPEED);
pros::delay(100);

chassis.pid_drive_set(11_in, DRIVE_SPEED, true);
pros::delay(800);

/////////////////////////////////////////////////////////go grab second mogo

Intake1.move(0);
Intake2.move(-0);
chassis.pid_turn_set(-90_deg, TURN_SPEED);
pros::delay(1100);

chassis.pid_drive_set(-47_in, DRIVE_SPEED, false);
pros::delay(1100);
chassis.pid_drive_set(-30_in, 40, false);
pros::delay(1200);

MOGO.set_value(1);
pros::delay(100);

/////////////////////////////////////////////////////////grab red rings 

Intake1.move(127);
Intake2.move(-127);
chassis.pid_turn_set(0_deg, TURN_SPEED);
pros::delay(500);

chassis.pid_drive_set(21_in, DRIVE_SPEED, false);
pros::delay(900);

chassis.pid_turn_set(90_deg, TURN_SPEED);
pros::delay(500);

chassis.pid_drive_set(21_in, DRIVE_SPEED, true);
pros::delay(800);

chassis.pid_turn_set(180_deg, TURN_SPEED);
pros::delay(500);

chassis.pid_drive_set(29_in, DRIVE_SPEED, true);
pros::delay(1000);

chassis.pid_turn_set(-310_deg, 50);

pros::delay(1500);

chassis.pid_drive_set(14_in, DRIVE_SPEED, true);
pros::delay(1000);

chassis.pid_turn_set(-20_deg, TURN_SPEED);
pros::delay(1000);

///////////////////////////////////////////////////////// put in corner 

chassis.pid_drive_set(-17_in, DRIVE_SPEED, true);
pros::delay(1300);

MOGO.set_value(0);
Intake1.move(-127);
Intake2.move(127);
pros::delay(100);

chassis.pid_turn_set(-45_deg, TURN_SPEED);
pros::delay(500);

Intake1.move(-0);
Intake2.move(0);
chassis.pid_drive_set(21_in, DRIVE_SPEED, true);
pros::delay(800);

/////////////////////////////////////////////////////////score on wall stake 
chassis.pid_turn_set(-0_deg, TURN_SPEED);
pros::delay(1000);

liftPID.target_set(300);
chassis.pid_drive_set(40_in, DRIVE_SPEED, true);
lift_wait();  // Wait for the lift to reach its target
pros::delay(900);

chassis.pid_turn_set(90_deg, TURN_SPEED);
Intake1.move(127);
Intake2.move(-127);
pros::delay(600);

chassis.pid_drive_set(12_in, 250, true);
pros::delay(2000);

Intake1.move(-227);
Intake2.move(227);
pros::delay(50);

Intake1.move(0);
Intake2.move(-0);
lift_auto(3000);
lift_wait();

chassis.pid_drive_set(5_in, 250, true);
pros::delay(500);

chassis.pid_drive_set(-12_in, 250, true);
pros::delay(600);

/////////////////////////////////////////////////////////grab next wall stake ring 

lift_auto(300);
chassis.pid_turn_set(-0_deg, TURN_SPEED);
lift_wait();
pros::delay(100);


Intake1.move(227);
Intake2.move(-227);
chassis.pid_drive_set(26_in, 250, true);
pros::delay(2100);

Intake1.move(-227);
Intake2.move(227);
pros::delay(50);

Intake1.move(227);
Intake2.move(-227);
pros::delay(50);

Intake1.move(0);
Intake2.move(-0);
lift_auto(800);
lift_wait();

/////////////////////////////////////////////////////////intake ring 
chassis.pid_turn_set(-90_deg, TURN_SPEED);
pros::delay(500);

Intake1.move(80);
Intake2.move(-80);
chassis.pid_drive_set(27_in, DRIVE_SPEED, true);
pros::delay(1000);

/////////////////////////////////////////////////////////grab third mogo
Intake1.move(0);
Intake2.move(-0);
chassis.pid_turn_set(135_deg, TURN_SPEED);
pros::delay(900);

chassis.pid_drive_set(-42_in, 55, true);
pros::delay(1500);

MOGO.set_value(1);
pros::delay(100);

/////////////////////////////////////////////////////////fill up mogo
chassis.pid_turn_set(210_deg, TURN_SPEED);
pros::delay(500);

Intake1.move(127);
Intake2.move(-127);
chassis.pid_drive_set(30_in, DRIVE_SPEED, true);
pros::delay(900);

chassis.pid_turn_set(270_deg, TURN_SPEED);
pros::delay(500);

chassis.pid_drive_set(22_in, DRIVE_SPEED, true);
pros::delay(800);

chassis.pid_turn_set(205_deg, TURN_SPEED);
pros::delay(500);

chassis.pid_drive_set(22_in, DRIVE_SPEED, true);
pros::delay(700);

/////////////////////////////////////////////////////////score on second wall stake
chassis.pid_turn_set(270_deg, TURN_SPEED);
pros::delay(400);

lift_auto(3000);
lift_wait();

Intake1.move(0);
Intake2.move(-0);
chassis.pid_drive_set(8_in, DRIVE_SPEED, true);
pros::delay(300);

chassis.pid_drive_set(-2_in, DRIVE_SPEED, true);
lift_auto(900);
lift_wait();

/////////////////////////////////////////////////////////intake last two rings 
chassis.pid_turn_set(-5_deg, TURN_SPEED);
pros::delay(200);

//arm.set_value(1);
Intake1.move(127);
Intake2.move(-127);
chassis.pid_drive_set(42_in, DRIVE_SPEED, true);
pros::delay(1800);

chassis.pid_turn_set(90_deg, TURN_SPEED);
pros::delay(700);

chassis.pid_drive_set(8_in, DRIVE_SPEED, true);
pros::delay(700);

/////////////////////////////////////////////////////////put into corner 

chassis.pid_turn_set(135_deg, TURN_SPEED);
pros::delay(500);

MOGO.set_value(0);
chassis.pid_drive_set(-15_in, DRIVE_SPEED, true);
pros::delay(800);

Intake1.move(-127);
Intake2.move(127);
pros::delay(10);

chassis.pid_drive_set(8_in, DRIVE_SPEED, true);
pros::delay(500);

chassis.pid_drive_set(-28_in, DRIVE_SPEED, true);
pros::delay(500);

Intake1.move(-0);
Intake2.move(0);
chassis.pid_drive_set(17_in, DRIVE_SPEED, true);
pros::delay(500);

/////////////////////////////////////////////////////////put last stake into corner 

chassis.pid_turn_set(75_deg, TURN_SPEED);
pros::delay(500);

chassis.pid_drive_set(115_in, 127, true);
pros::delay(2300);

/////////////////////////////////////////////////////////hang 

lift_auto(3000);
chassis.pid_turn_set(45_deg, TURN_SPEED);
lift_wait();

chassis.pid_drive_set(-65_in, 127, true);
pros::delay(1500);

}

/**
 * Simplifies printing tracker values to the brain screen
 */
// void screen_print_tracker(ez::tracking_wheel *tracker, std::string name, int line) {
//   std::string tracker_value = "", tracker_width = "";
//   // Check if the tracker exists
//   if (tracker != nullptr) {
//     tracker_value = name + " tracker: " + util::to_string_with_precision(tracker->get());             // Make text for the tracker value
//     tracker_width = "  width: " + util::to_string_with_precision(tracker->distance_to_center_get());  // Make text for the distance to center
//   }
//   ez::screen_print(tracker_value + tracker_width, line);  // Print final tracker text
// }

/**
 * Ez screen task
 * Adding new pages here will let you view them during user control or autonomous
 * and will help you debug problems you're having
 */
// void ez_screen_task() {
//   while (true) {
//     // Only run this when not connected to a competition switch
//     if (!pros::competition::is_connected()) {
//       // Blank page for odom debugging
//       if (chassis.odom_enabled() && !chassis.pid_tuner_enabled()) {
//         // If we're on the first blank page...
//         if (ez::as::page_blank_is_on(0)) {
//           // Display X, Y, and Theta
//           ez::screen_print("x: " + util::to_string_with_precision(chassis.odom_x_get()) +
//                                "\ny: " + util::to_string_with_precision(chassis.odom_y_get()) +
//                                "\na: " + util::to_string_with_precision(chassis.odom_theta_get()),
//                            1);  // Don't override the top Page line

//           // Display all trackers that are being used
//           screen_print_tracker(chassis.odom_tracker_left, "l", 4);
//           screen_print_tracker(chassis.odom_tracker_right, "r", 5);
//           screen_print_tracker(chassis.odom_tracker_back, "b", 6);
//           screen_print_tracker(chassis.odom_tracker_front, "f", 7);
//         }
//       }
//     }

//     // Remove all blank pages when connected to a comp switch
//     else {
//       if (ez::as::page_blank_amount() > 0)
//         ez::as::page_blank_remove_all();
//     }

//     pros::delay(ez::util::DELAY_TIME);
//   }
// }
// pros::Task ezScreenTask(ez_screen_task);

/**
 * Gives you some extras to run in your opcontrol:
 * - run your autonomous routine in opcontrol by pressing DOWN and B
 *   - to prevent this from accidentally happening at a competition, this
 *     is only enabled when you're not connected to competition control.
 * - gives you a GUI to change your PID values live by pressing X
 */
void ez_template_extras() {
  // Only run this when not connected to a competition switch
  if (!pros::competition::is_connected()) {
    // PID Tuner
    // - after you find values that you're happy with, you'll have to set them in auton.cpp

    // Enable / Disable PID Tuner
    //  When enabled:
    //  * use A and Y to increment / decrement the constants
    //  * use the arrow keys to navigate the constants
    if (master.get_digital_new_press(DIGITAL_X))
      chassis.pid_tuner_toggle();

    // Trigger the selected autonomous routine
    if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) {
      pros::motor_brake_mode_e_t preference = chassis.drive_brake_get();
      autonomous();
      chassis.drive_brake_set(preference);
    }

    // Allow PID Tuner to iterate
    chassis.pid_tuner_iterate();
  }

  // Disable PID Tuner when connected to a comp switch
  else {
    if (chassis.pid_tuner_enabled())
      chassis.pid_tuner_disable();
  }
}



void opcontrol() {


/*
tank 
mogo-B
lb- downset, l1,l2 
intake - r1 
outtake-r2 
arm - down, right  

*/
    LB.set_brake_mode(MOTOR_BRAKE_HOLD);


  chassis.drive_brake_set(MOTOR_BRAKE_COAST);

  while (true) {
    // Gives you some extras to make EZ-Template ezier
    ez_template_extras();    
    chassis.opcontrol_tank();  // Tank control

   
 /*arm Control*/
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
		{
			  arm.set_value(1);
		}
		else 
		{
			  arm.set_value(0);
		}

 /*Intake Control*/
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
		{
        Intake1.move(-127);
        Intake2.move(127);
    
		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
		{
       Intake1.move(127);
       Intake2.move(-127);
		}
		else 
		{
			  Intake2.move(0);
        Intake1.move(0);
		}

    /*LB Control*/
    
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT))
		{
      liftPID.target_set(300);

		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
		{
      liftPID.target_set(1700);
      Intake2.move(127);
      Intake1.move(-127);

    }
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
		{

      liftPID.target_set(0);
    }

    set_lift(liftPID.compute(LB.get_position()));
   
//MOGO code
   	if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B) != lastKnownButtonBState)
		{
			lastKnownButtonBState = master.get_digital(pros::E_CONTROLLER_DIGITAL_B);
			if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B) && ClampState == 0 || ClampState == 2)
			{
				ClampState = 1;
			} 
			else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B) && ClampState == 1)
			{
				ClampState = 0;
			}
		}  

    switch (ClampState)
    {
      case 0:
			 MOGO.set_value(0);
      
      pros::delay(10);
      break;
			
      case 1:
        MOGO.set_value(1);
				
      pros::delay(10);
				break;
    }

    pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
