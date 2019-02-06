#include <atomic>
#include <realtime_tools/realtime_buffer.h>
#include "teleop_joystick_control/teleop_joystick_comp.h"
#include "std_srvs/Empty.h"

#include "behaviors/IntakeAction.h"
#include "behaviors/IntakeGoal.h"
#include "behaviors/PlaceAction.h"
#include "behaviors/PlaceGoal.h"
#include "behaviors/ElevatorAction.h"
#include "behaviors/ElevatorGoal.h"
#include "behaviors/ClimbAction.h"
#include "behaviors/ClimbGoal.h"
#include "actionlib/client/simple_action_client.h"
#include "behaviors/enumerated_elevator_indices.h"

#include "std_srvs/SetBool.h"
#include <vector>
#include <vector>

double joystick_deadzone;
double slow_mode;
double max_speed;
double max_rot;
double joystick_pow;
double rotation_pow;

std::vector <frc_msgs::JoystickState> joystick_states_array;
std::vector <std::string> topic_array;

ros::Publisher JoystickRobotVel;
ros::ServiceClient BrakeSrv;
ros::ServiceClient run_align;
//use shared pointers to make the clients global 
std::shared_ptr<actionlib::SimpleActionClient<behaviors::IntakeAction>> intake_cargo_ac;
std::shared_ptr<actionlib::SimpleActionClient<behaviors::PlaceAction>> outtake_cargo_ac;
std::shared_ptr<actionlib::SimpleActionClient<behaviors::IntakeAction>> intake_hatch_panel_ac;
std::shared_ptr<actionlib::SimpleActionClient<behaviors::PlaceAction>> outtake_hatch_panel_ac;
std::shared_ptr<actionlib::SimpleActionClient<behaviors::ElevatorAction>> elevator_ac;
std::shared_ptr<actionlib::SimpleActionClient<behaviors::ClimbAction>> climber_ac;
std::atomic<double> navX_angle;

struct ElevatorGoal
{
    ElevatorGoal():
        index_(0)
    {
    }
    ElevatorGoal(double index):
        index_(index)
    {
    }
    double index_;

};

realtime_tools::RealtimeBuffer<ElevatorGoal> ElevatorGoal;


void deadzone_check(double &val1, double &val2)
{
	if (fabs(val1) <= joystick_deadzone && fabs(val2) <= joystick_deadzone)
	{
		val1 = 0;
		val2 = 0;
	}
}

// Use a realtime buffer to store the odom callback data
// The main teleop code isn't technically realtime but we
// want it to be the fast part of the code, so for now
// pretend that is the realtime side of the code
/*realtime_tools::RealtimeBuffer<ElevatorPos> elevatorPos;
realtime_tools::RealtimeBuffer<CubeState> cubeState;
realtime_tools::RealtimeBuffer<ElevatorPos> elevatorCmd;*/
void navXCallback(const sensor_msgs::Imu &navXState)
{
    const tf2::Quaternion navQuat(navXState.orientation.x, navXState.orientation.y, navXState.orientation.z, navXState.orientation.w);
    double roll;
    double pitch;
    double yaw;
    tf2::Matrix3x3(navQuat).getRPY(roll, pitch, yaw);

    if (yaw == yaw) // ignore NaN results
        navX_angle.store(yaw, std::memory_order_relaxed);
}

void evaluateCommands(const ros::MessageEvent<frc_msgs::JoystickState const>& event)
{
	int i = 0;

	const ros::M_string &header = event.getConnectionHeader();

	std::string topic = header.at("topic");
	for(bool msg_assign = false; msg_assign == false; i++)
	{
		if(topic == topic_array[i])
		{
			joystick_states_array[i] = *(event.getMessage());
			msg_assign = true;
		}
	}
	
	//Only do this for the first joystick
	if(i == 1)
	{
		double leftStickX = joystick_states_array[0].leftStickX;
		double leftStickY = joystick_states_array[0].leftStickY;

		double rightStickX = joystick_states_array[0].rightStickX;
		double rightStickY = joystick_states_array[0].rightStickY;

		deadzone_check(leftStickX, leftStickY);
		deadzone_check(rightStickX, rightStickY);

		leftStickX =  pow(leftStickX, joystick_pow) * max_speed;
		leftStickY = -pow(leftStickY, joystick_pow) * max_speed;

		rightStickX =  pow(rightStickX, joystick_pow);
		rightStickY = -pow(rightStickY, joystick_pow);

		//rotate based off of triggers
		//const double rotation = (pow(joystick_states_array[0].leftTrigger, rotation_pow) - pow(joystick_states_array[0].rightTrigger, rotation_pow)) * max_rot;
		//
		//rotate based off of joysticks
		double rotation = pow(rightStickX, rotation_pow) * max_rot;

		static bool sendRobotZero = false;
		if (leftStickX == 0.0 && leftStickY == 0.0 && rotation == 0.0)
		{
			if (!sendRobotZero)
			{
				std_srvs::Empty empty;
				if (!BrakeSrv.call(empty))
				{
					ROS_ERROR("BrakeSrv call failed in sendRobotZero");
				}
				ROS_INFO("BrakeSrv called");
				sendRobotZero = true;
			}
		}

		else // X or Y or rotation != 0 so tell the drive base to move
		{
			//Publish drivetrain messages and call servers
			Eigen::Vector2d joyVector;
			joyVector[0] = leftStickX; //intentionally flipped
			joyVector[1] = -leftStickY;
			const Eigen::Rotation2Dd r(-navX_angle.load(std::memory_order_relaxed) - M_PI / 2.);
			const Eigen::Vector2d rotatedJoyVector = r.toRotationMatrix() * joyVector;

			geometry_msgs::Twist vel;
			vel.linear.x = rotatedJoyVector[1];
			vel.linear.y = rotatedJoyVector[0];
			vel.linear.z = 0;

			vel.angular.x = 0;
			vel.angular.y = 0;
			vel.angular.z = rotation;

			JoystickRobotVel.publish(vel);
			sendRobotZero = false;
		}

		//Joystick1: buttonA
		if(joystick_states_array[0].buttonAPress)
		{
			ROS_INFO_STREAM("Joystick1: buttonAPress");
			behaviors::ElevatorGoal goal;
			goal.setpoint_index = INTAKE;
			goal.place_cargo = false;
			elevator_ac->sendGoal(goal);
		}
		if(joystick_states_array[0].buttonAButton)
		{
			ROS_INFO_THROTTLE(1, "buttonAButton");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[0].buttonARelease)
		{
			ROS_INFO_STREAM("Joystick1: buttonARelease");
			std_srvs::SetBool msg;
			msg.request.data = false;
			run_align.call(msg);
		}
		//Joystick1: buttonB
		if(joystick_states_array[0].buttonBPress)
		{
			ROS_INFO_STREAM("Joystick1: buttonAPress");
			behaviors::ElevatorGoal goal;
			goal.setpoint_index = CARGO_SHIP;
			goal.place_cargo = false;
			elevator_ac->sendGoal(goal);
		}
		if(joystick_states_array[0].buttonBButton)
		{
			ROS_INFO_THROTTLE(1, "buttonBButton");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[0].buttonBRelease)
		{
			ROS_INFO_STREAM("Joystick1: buttonBRelease");
			std_srvs::SetBool msg;
			msg.request.data = false;
			run_align.call(msg);
		}
		//Joystick1: buttonX
		if(joystick_states_array[0].buttonXPress)
		{
			ROS_INFO_STREAM("Joystick1: buttonXPress");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[0].buttonXButton)
		{
			ROS_INFO_THROTTLE(1, "buttonXButton");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[0].buttonXRelease)
		{
			ROS_INFO_STREAM("Joystick1: buttonXRelease");
			std_srvs::SetBool msg;
			msg.request.data = false;
			run_align.call(msg);
		}
		//Joystick1: buttonY
		if(joystick_states_array[0].buttonYPress)
		{
			ROS_INFO_STREAM("Joystick1: buttonYPress");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[0].buttonYButton)
		{
			ROS_INFO_THROTTLE(1, "buttonYButton");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[0].buttonYRelease)
		{
			ROS_INFO_STREAM("Joystick1: buttonYRelease");
			std_srvs::SetBool msg;
			msg.request.data = false;
			run_align.call(msg);
		}
		//Joystick1: bumperLeft
		if(joystick_states_array[0].bumperLeftPress)
		{
			ROS_INFO_STREAM("Joystick1: bumperLeftPress");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[0].bumperLeftButton)
		{
			ROS_INFO_THROTTLE(1, "bumperLeftButton");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[0].bumperLeftRelease)
		{
			ROS_INFO_STREAM("Joystick1: bumperLeftRelease");
			std_srvs::SetBool msg;
			msg.request.data = false;
			run_align.call(msg);
		}
		//Joystick1: bumperRight
		if(joystick_states_array[0].bumperRightPress)
		{
			ROS_INFO_STREAM("Joystick1: bumperRightPress");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[0].bumperRightButton)
		{
			ROS_INFO_THROTTLE(1, "bumperRightButton");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[0].bumperRightRelease)
		{
			ROS_INFO_STREAM("Joystick1: bumperRightRelease");
			std_srvs::SetBool msg;
			msg.request.data = false;
			run_align.call(msg);
		}
		//Joystick1: directionLeft
		if(joystick_states_array[0].directionLeftPress)
		{
			ROS_INFO_STREAM("Joystick1: directionLeftPress");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[0].directionLeftButton)
		{
			ROS_INFO_THROTTLE(1, "directionLeftButton");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[0].directionLeftRelease)
		{
			ROS_INFO_STREAM("Joystick1: directionLeftRelease");
			std_srvs::SetBool msg;
			msg.request.data = false;
			run_align.call(msg);
		}
		//Joystick1: directionRight
		if(joystick_states_array[0].directionRightPress)
		{
			ROS_INFO_STREAM("Joystick1: directionRightPress");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[0].directionRightButton)
		{
			ROS_INFO_THROTTLE(1, "directionRightButton");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[0].directionRightRelease)
		{
			ROS_INFO_STREAM("Joystick1: directionRightRelease");
			std_srvs::SetBool msg;
			msg.request.data = false;
			run_align.call(msg);
		}
		//Joystick1: directionUp
		if(joystick_states_array[0].directionUpPress)
		{
			ROS_INFO_STREAM("Joystick1: directionUpPress");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[0].directionUpButton)
		{
			ROS_INFO_THROTTLE(1, "directionUpButton");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[0].directionUpRelease)
		{
			ROS_INFO_STREAM("Joystick1: directionUpRelease");
			std_srvs::SetBool msg;
			msg.request.data = false;
			run_align.call(msg);
		}
		//Joystick1: directionDown
		if(joystick_states_array[0].directionDownPress)
		{
			ROS_INFO_STREAM("Joystick1: directionDownPress");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[0].directionDownButton)
		{
			ROS_INFO_THROTTLE(1, "directionDownButton");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[0].directionDownRelease)
		{
			ROS_INFO_STREAM("Joystick1: directionDownRelease");
			std_srvs::SetBool msg;
			msg.request.data = false;
			run_align.call(msg);
		}
	}

	else if(i == 2)
	{
		//Joystick2: buttonA
		if(joystick_states_array[1].buttonAPress)
		{
			ROS_INFO_STREAM("Joystick2: buttonAPress");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[1].buttonAButton)
		{
			ROS_INFO_THROTTLE(1, "buttonAButton");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[1].buttonARelease)
		{
			ROS_INFO_STREAM("Joystick2: buttonARelease");
			std_srvs::SetBool msg;
			msg.request.data = false;
			run_align.call(msg);
		}
		//Joystick2: buttonB
		if(joystick_states_array[1].buttonBPress)
		{
			ROS_INFO_STREAM("Joystick2: buttonBPress");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[1].buttonBButton)
		{
			ROS_INFO_THROTTLE(1, "buttonBButton");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[1].buttonBRelease)
		{
			ROS_INFO_STREAM("Joystick2: buttonBRelease");
			std_srvs::SetBool msg;
			msg.request.data = false;
			run_align.call(msg);
		}
		//Joystick2: buttonX
		if(joystick_states_array[1].buttonXPress)
		{
			ROS_INFO_STREAM("Joystick2: buttonXPress");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[1].buttonXButton)
		{
			ROS_INFO_THROTTLE(1, "buttonXButton");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[1].buttonXRelease)
		{
			ROS_INFO_STREAM("Joystick2: buttonXRelease");
			std_srvs::SetBool msg;
			msg.request.data = false;
			run_align.call(msg);
		}
		//Joystick2: buttonY
		if(joystick_states_array[1].buttonYPress)
		{
			ROS_INFO_STREAM("Joystick2: buttonYPress");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[1].buttonYButton)
		{
			ROS_INFO_THROTTLE(1, "buttonYButton");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[1].buttonYRelease)
		{
			ROS_INFO_STREAM("Joystick2: buttonYRelease");
			std_srvs::SetBool msg;
			msg.request.data = false;
			run_align.call(msg);
		}
		//Joystick2: bumperLeft
		if(joystick_states_array[1].bumperLeftPress)
		{
			ROS_INFO_STREAM("Joystick2: bumperLeftPress");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[1].bumperLeftButton)
		{
			ROS_INFO_THROTTLE(1, "bumperLeftButton");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[1].bumperLeftRelease)
		{
			ROS_INFO_STREAM("Joystick2: bumperLeftRelease");
			std_srvs::SetBool msg;
			msg.request.data = false;
			run_align.call(msg);
		}
		//Joystick2: bumperRight
		if(joystick_states_array[1].bumperRightPress)
		{
			ROS_INFO_STREAM("Joystick2: bumperRightPress");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[1].bumperRightButton)
		{
			ROS_INFO_THROTTLE(1, "bumperRightButton");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[1].bumperRightRelease)
		{
			ROS_INFO_STREAM("Joystick2: bumperRightRelease");
			std_srvs::SetBool msg;
			msg.request.data = false;
			run_align.call(msg);
		}
		//Joystick2: directionLeft
		if(joystick_states_array[1].directionLeftPress)
		{
			ROS_INFO_STREAM("Joystick2: directionLeftPress");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[1].directionLeftButton)
		{
			ROS_INFO_THROTTLE(1, "directionLeftButton");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[1].directionLeftRelease)
		{
			ROS_INFO_STREAM("Joystick2: directionLeftRelease");
			std_srvs::SetBool msg;
			msg.request.data = false;
			run_align.call(msg);
		}
		//Joystick2: directionRight
		if(joystick_states_array[1].directionRightPress)
		{
			ROS_INFO_STREAM("Joystick2: directionRightPress");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[1].directionRightButton)
		{
			ROS_INFO_THROTTLE(1, "directionRightButton");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[1].directionRightRelease)
		{
			ROS_INFO_STREAM("Joystick2: directionRightRelease");
			std_srvs::SetBool msg;
			msg.request.data = false;
			run_align.call(msg);
		}
		//Joystick2: directionUp
		if(joystick_states_array[1].directionUpPress)
		{
			ROS_INFO_STREAM("Joystick2: directionUpPress");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[1].directionUpButton)
		{
			ROS_INFO_THROTTLE(1, "directionUpButton");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[1].directionUpRelease)
		{
			ROS_INFO_STREAM("Joystick2: directionUpRelease");
			std_srvs::SetBool msg;
			msg.request.data = false;
			run_align.call(msg);
		}
		//Joystick2: directionDown
		if(joystick_states_array[1].directionDownPress)
		{
			ROS_INFO_STREAM("Joystick2: directionDownPress");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[1].directionDownButton)
		{
			ROS_INFO_THROTTLE(1, "directionDownButton");
			std_srvs::SetBool msg;
			msg.request.data = true;
			run_align.call(msg);
		}
		if(joystick_states_array[1].directionDownRelease)
		{
			ROS_INFO_STREAM("Joystick2: directionDownRelease");
			std_srvs::SetBool msg;
			msg.request.data = false;
			run_align.call(msg);
		}
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "Joystick_controller");
	ros::NodeHandle n;
	ros::NodeHandle n_params(n, "teleop_params");

	if(!n_params.getParam("joystick_deadzone", joystick_deadzone))
	{
		ROS_ERROR("Could not read joystick_deadzone in teleop_joystick_comp");
	}
	if(!n_params.getParam("slow_mode", slow_mode))
	{
		ROS_ERROR("Could not read slow_mode in teleop_joystick_comp");
	}
	if(!n_params.getParam("max_speed", max_speed))
	{
		ROS_ERROR("Could not read max_speed in teleop_joystick_comp");
	}
	if(!n_params.getParam("max_rot", max_rot))
	{
		ROS_ERROR("Could not read max_rot in teleop_joystick_comp");
	}
	if(!n_params.getParam("joystick_pow", joystick_pow))
	{
		ROS_ERROR("Could not read joystick_pow in teleop_joystick_comp");
	}
	if(!n_params.getParam("rotation_pow", rotation_pow))
	{
		ROS_ERROR("Could not read rotation_pow in teleop_joystick_comp");
	}


	std::vector <ros::Subscriber> subscriber_array;

	navX_angle = M_PI / 2;

	//Read from two joysticks
	topic_array.push_back("/frcrobot_jetson/joystick_states");
	topic_array.push_back("/frcrobot_jetson/joystick_states1");
	for(size_t j = 0; (subscriber_array.size()) < (topic_array.size()); j++)
	{
		subscriber_array.push_back(n.subscribe((topic_array[j]), 1, &evaluateCommands));
	}

	joystick_states_array.resize(topic_array.size());

	std::map<std::string, std::string> service_connection_header;
	service_connection_header["tcp_nodelay"] = "1";
	BrakeSrv = n.serviceClient<std_srvs::Empty>("swerve_drive_controller/brake", false, service_connection_header);
	JoystickRobotVel = n.advertise<geometry_msgs::Twist>("swerve_drive_controller/cmd_vel", 1);
	ros::Subscriber navX_heading  = n.subscribe("navx_mxp", 1, &navXCallback);

	//initialize actionlib clients
	intake_cargo_ac = std::make_shared<actionlib::SimpleActionClient<behaviors::IntakeAction>>("cargo_intake_server", true);
	outtake_cargo_ac = std::make_shared<actionlib::SimpleActionClient<behaviors::PlaceAction>>("cargo_outtake_server", true);
	intake_hatch_panel_ac = std::make_shared<actionlib::SimpleActionClient<behaviors::IntakeAction>>("intake_hatch_panel_server", true);
	outtake_hatch_panel_ac = std::make_shared<actionlib::SimpleActionClient<behaviors::PlaceAction>>("outtake_hatch_panel_server", true);
	climber_ac = std::make_shared<actionlib::SimpleActionClient<behaviors::ClimbAction>>("climber_server", true);
	elevator_ac = std::make_shared<actionlib::SimpleActionClient<behaviors::ElevatorAction>>("elevator_server", true);


	run_align = n.serviceClient<std_srvs::SetBool>("run_align");

	ROS_WARN("joy_init");

	ros::spin();
	return 0;
}
