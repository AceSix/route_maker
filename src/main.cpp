#include <ros/ros.h>
#include <serial/serial.h>  //ROS has built-in serial port package
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <move_base_msgs/MoveBaseActionGoal.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include "time.h"
#include <math.h>

using namespace std;


class MakeRoad
{
public:
    MakeRoad(int argc, char** argv){




        ros::Rate loop_rate(100);
        ros::init(argc, argv, "makeroad_node");
        ros::NodeHandle nh;
        ros::Subscriber pose_sub = nh.subscribe<geometry_msgs::PoseStamped>("/robot_pose", 1, &MakeRoad::check_callback);
        ros::Publisher destiny_pub = nh.advertise<move_base_msgs::MoveBaseActionGoal>("/move_base/goal", 1);
        while(ros::ok())
        {
            destiny_pub.publish(current_goal);
            ros::spinOnce();
        }

    }
    void check_callback(const geometry_msgs::PoseStampedPtr pose)
    {
        double dx = pose->pose.position.x-current_goal.pose.position.x;
        double dy = pose->pose.position.y-current_goal.pose.position.y;
        if(pow(dx,2)+pow(dy,2)<9)
            if(goal_id<2) goal_id++;
    }

    void set_goals(){
        goal_id=0;

        goals[0].goal.target_pose.pose.position.x = 30;
        goals[0].goal.target_pose.pose.position.y = 50;
        goals[0].goal.target_pose.pose.position.z = 0;

        goals[1].goal.target_pose.pose.position.x = 80;
        goals[1].goal.target_pose.pose.position.y = -20;
        goals[1].goal.target_pose.pose.position.z = 0;

        goals[2].goal.target_pose.pose.position.x = 30;
        goals[2].goal.target_pose.pose.position.y = 50;
        goals[2].goal.target_pose.pose.position.z = 0;

        current_goal = goals[goal_id].goal.target_pose;
    }
private:
    geometry_msgs::PoseStamped current_goal;
    int goal_id;
    move_base_msgs::MoveBaseActionGoal goals[3];


};


int main (int argc, char** argv)
{

    MakeRoad maker(argc,argv);
}
