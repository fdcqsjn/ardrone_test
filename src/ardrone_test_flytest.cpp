//本程序发布控制命令到cmd_vel主题
#include <ros/ros.h>  //标准的ROS类的声明,每个程序都需要
#include <std_msgs/Empty.h>  //用到的消息类型的声明的 头文件
#include <geometry_msgs/Twist.h>//

	geometry_msgs::Twist twist_msg;
	geometry_msgs::Twist twist_msg_hover;
	geometry_msgs::Twist twist_msg_pshover;
	std_msgs::Empty emp_msg; 
	//使用范围解析运算符(::)重定义全局类的对象
int main(int argc, char** argv)
{
                    
    ROS_INFO("Manual Test Node Starting");
	ros::init(argc, argv,"ARDrone_manual_test"); //初始化ROS系统,"ARDrone_manual_test"为节点名字,可修改或覆盖
    ros::NodeHandle node;                                   //节点句柄对象,在roscore中注册节点
    ros::Rate loop_rate(50);                                   //定义对象控制循环运行速度为50hz,直到节点关闭

//创建发布者对象
	ros::Publisher pub_empty_land;              
	ros::Publisher pub_twist;
	ros::Publisher pub_empty_takeoff;
	ros::Publisher pub_empty_reset;
//赋值悬停控制消息类型域的包含的数据成员
			twist_msg_hover.linear.x=0.0; 
			twist_msg_hover.linear.y=0.0;
			twist_msg_hover.linear.z=0.0;
			twist_msg_hover.angular.x=0.0; 
			twist_msg_hover.angular.y=0.0;
			
//赋值控制飞行数据类型域包含的数据成员 让飞行器绕Yaw轴旋转
			twist_msg.linear.x=0.0; 
			twist_msg.linear.y=0.5;
			twist_msg.linear.z=0.0;
			twist_msg.angular.x=0.0; 
			twist_msg.angular.y=0.0;
			twist_msg.angular.z=0.0;

//继续创建发布者对象
    pub_twist = node.advertise<geometry_msgs::Twist>("/cmd_vel", 1); //注意这里消息序列的大小只需要1
	pub_empty_takeoff = node.advertise<std_msgs::Empty>("/ardrone/takeoff", 1); 
	pub_empty_land = node.advertise<std_msgs::Empty>("/ardrone/land", 1);
    pub_empty_reset = node.advertise<std_msgs::Empty>("/ardrone/reset", 1); 
	
	double time;
	time =(double)ros::Time::now().toSec();	  //定义这里的time为时间点
	ROS_INFO("Starting ARdrone_test loop");		

while (ros::ok()){  //ros::ok()检测节点是否停止工作
	
		if ( (double)ros::Time::now().toSec()< time +3){
			pub_empty_takeoff.publish(emp_msg); //发布起飞消息
			pub_twist.publish(twist_msg_hover); //悬停模式
			ROS_INFO_ONCE("Taking off");

			}//持续5秒
			
		else if  ((double)ros::Time::now().toSec()<time + 4)
		{
		
			pub_twist.publish(twist_msg); //悬停
			ROS_INFO_ONCE("FLYING");
			}//时间大于9+5 降落
		else if  ((double)ros::Time::now().toSec()<time + 10)
		{
		
			pub_empty_land.publish(emp_msg); 
			ROS_INFO_ONCE("landing");
			
			};//时间大于9+5 降落

		//else  
		//{
	//	pub_empty_reset.publish(emp_msg); 
		//	ROS_INFO("Land and Closing Node");
			//break; 
			
		//	}//时间大于9+5+2后,重置飞行器,并结束 节点
	
	 //  else
	//	{	
		//	pub_twist.publish(twist_msg_pshover);
	//		pub_empty_reset.publish(emp_msg); 
	// ROS_INFO_ONCE("RESET");

	//	};//时间小于9+5 悬停
	
	ros::spinOnce();      //调用该函数确保允许回调发生
	loop_rate.sleep();   //调用对象的sleep方法产生延迟,使得循环以之前定义50Hz速度运行

}//ros::ok

}//main



