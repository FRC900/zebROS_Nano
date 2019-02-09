#include <atomic>
#include "std_srvs/Empty.h"
#include <hardware_interface/joint_command_interface.h>
#include "sensor_msgs/Imu.h"
#include "sensor_msgs/JointState.h"
#include "ros/ros.h"
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include "angles/angles.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Float64MultiArray.h"


#include <vector>

ros::Publisher snapAnglePub;
std::atomic<double> navX_angle;
std::atomic<bool> has_cargo;
std::atomic<bool> has_panel;

std::vector<double> hatch_panel_angles;
std::vector<double> cargo_angles;
std::vector<double> nothing_angles;

int linebreak_debounce_iterations;


double nearest_angle(std::vector<double> angles)
{
	double snap_angle;
	double smallest_distance = std::numeric_limits<double>::max();
	double cur_angle = angles::normalize_angle_positive(navX_angle.load(std::memory_order_relaxed));
	for(int i = 0; i < angles.size(); i++){
		double distance = fabs(angles::shortest_angular_distance(cur_angle, angles[i]));
		if(distance < smallest_distance) {
			smallest_distance = distance;
			snap_angle = angles[i];
		}
	}
	return snap_angle;
}

void navXCallback(const sensor_msgs::Imu &navXState)
{
    const tf2::Quaternion navQuat(navXState.orientation.x, navXState.orientation.y, navXState.orientation.z, navXState.orientation.w);
    double roll;
    double pitch;
    double yaw;
    tf2::Matrix3x3(navQuat).getRPY(roll, pitch, yaw);

    if (yaw == yaw) // ignore NaN results
        navX_angle.store(-1*yaw, std::memory_order_relaxed);
}

void jointStateCallback(const sensor_msgs::JointState &joint_state)
{
		static int linebreak_true_panel_count = 0;
		static int linebreak_false_panel_count = 0;
		static int linebreak_true_cargo_count = 0;
		static int linebreak_false_cargo_count = 0;
        //get index of linebreak sensor for this actionlib server
        static size_t linebreak_idx_1 = std::numeric_limits<size_t>::max();
        static size_t linebreak_idx_2 = std::numeric_limits<size_t>::max();
        static size_t linebreak_idx_3 = std::numeric_limits<size_t>::max();
        static size_t linebreak_idx_4 = std::numeric_limits<size_t>::max();
        static size_t linebreak_idx_5 = std::numeric_limits<size_t>::max();

        if (linebreak_idx_1 >= joint_state.name.size()
            || linebreak_idx_2 >= joint_state.name.size()
            || linebreak_idx_3 >= joint_state.name.size()
            || linebreak_idx_4 >= joint_state.name.size()
			|| linebreak_idx_5 >= joint_state.name.size())
        {
            for (size_t i = 0; i < joint_state.name.size(); i++)
            {
                if (joint_state.name[i] == "panel_intake_linebreak_1")
                    linebreak_idx_1 = i;
                if (joint_state.name[i] == "panel_intake_linebreak_2")
                    linebreak_idx_2 = i;
                if (joint_state.name[i] == "panel_intake_linebreak_3")
                    linebreak_idx_3 = i;
                if (joint_state.name[i] == "panel_intake_linebreak_4")
                    linebreak_idx_4 = i;
                if (joint_state.name[i] == "cargo_intake_linebreak_1")
                    linebreak_idx_5 = i;
            }
        }

        //update linebreak counts based on the value of the linebreak sensor
        if (linebreak_idx_1 < joint_state.position.size()
            && linebreak_idx_2 < joint_state.position.size()
            && linebreak_idx_3 < joint_state.position.size()
            && linebreak_idx_4 < joint_state.position.size()
            && linebreak_idx_5 < joint_state.position.size() )
        {
            bool linebreak_true_cargo = ( joint_state.position[linebreak_idx_5] != 0);
            bool linebreak_true_panel = ( joint_state.position[linebreak_idx_1] != 0
                                    || joint_state.position[linebreak_idx_2] != 0
                                    || joint_state.position[linebreak_idx_3] != 0
                                    || joint_state.position[linebreak_idx_4] != 0
                                );
            if(linebreak_true_cargo)
            {
                linebreak_true_cargo_count += 1;
                linebreak_false_cargo_count = 0;
            }
            else
            {
                linebreak_true_cargo_count = 0;
                linebreak_false_cargo_count += 1;
            }
            if(linebreak_true_panel)
            {
                linebreak_true_panel_count += 1;
                linebreak_false_panel_count = 0;
            }
            else
            {
                linebreak_true_panel_count = 0;
                linebreak_false_panel_count += 1;
            }
			
		    if(linebreak_true_cargo_count >	linebreak_debounce_iterations) {
                has_cargo.store(true);
            }
            else {
                has_cargo.store(false);
            }
		    if(linebreak_true_panel_count >	linebreak_debounce_iterations) {
                has_panel.store(true);
            }
            else {
                has_panel.store(false);
            }
        }
        else
        {
            static int count = 0;
            if(count % 100 == 0)
            {
                ROS_WARN("intake line break sensor not found in joint_states");
            }
            count++;
            linebreak_true_panel_count = 0;
            linebreak_true_cargo_count = 0;
            linebreak_false_panel_count += 1;
            linebreak_false_cargo_count += 1;
        }
}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "Joystick_controller");
	ros::NodeHandle nh;
	ros::NodeHandle n_params(nh, "goal_angles");
	ros::NodeHandle n_params_actionlib(nh, "actionlib_params");

	if(!n_params.getParam("hatch_panel_angles", hatch_panel_angles))
	{
		ROS_ERROR("Could not read hatch_panel_angles in teleop_joystick_comp");
	}
	if(!n_params.getParam("cargo_angles", cargo_angles))
	{
		ROS_ERROR("Could not read cargo_angles in teleop_joystick_comp");
	}
	if(!n_params.getParam("nothing_angles", nothing_angles))
	{
		ROS_ERROR("Could not read nothing_angles in teleop_joystick_comp");
	}


	if(!n_params_actionlib.getParam("linebreak_debounce_iterations", linebreak_debounce_iterations))
	{
		ROS_ERROR("Could not read nothing_angles in teleop_joystick_comp");
	}


	navX_angle = M_PI / 2;
	has_panel = false;
	has_cargo = false;

	ros::Subscriber joint_states_sub_ = nh.subscribe("/frcrobot_jetson/joint_states", 1, jointStateCallback);
	ros::Subscriber navX_heading  = nh.subscribe("/frcrobot_rio/navx_mxp", 1, &navXCallback);
	ros::Publisher snapAnglePub = nh.advertise<std_msgs::Float64>("/navX_snap_to_goal_pid/navX_snap_to_goal_setpoint", 10);
	ros::Publisher navXStatePub = nh.advertise<std_msgs::Float64>("/navX_snap_to_goal_pid/navX_snap_to_goal_state", 10);
	ROS_INFO("snap_to_angle_init");

	ros::Rate r(100);
	double snap_angle;
	while(ros::ok()) {
		std_msgs::Float64 angle_snap;
		std_msgs::Float64 navX_state;
		if(has_panel) {
			snap_angle = nearest_angle(hatch_panel_angles);
		}
		else if(has_cargo) {
			snap_angle = nearest_angle(cargo_angles);
		}
		else {
			snap_angle = nearest_angle(nothing_angles);
		}
		angle_snap.data = snap_angle;
		navX_state.data = angles::normalize_angle_positive(navX_angle.load(std::memory_order_relaxed));
		snapAnglePub.publish(angle_snap);
        navXStatePub.publish(navX_state);

		r.sleep();
		ros::spinOnce();
	}
	return 0;
}