/*
 * main.cpp
 *
 *  Created on: Feb 3, 2021
 *      Author: Ignacio
 */
#include "main.h"
#include <ros.h>
#include "std_msgs/String.h"

ros::NodeHandle nh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);
char hello[] = "Hello world from STM32!";

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->flush();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->reset_rbuf();
}

void CppMain(){
	nh.initNode();
	nh.advertise(chatter);

	while(1){
		HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);

		str_msg.data = hello;
		chatter.publish(&str_msg);
		nh.spinOnce();

		HAL_Delay(2000);
	}
}

