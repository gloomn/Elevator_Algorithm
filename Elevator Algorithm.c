//컴퓨터교육과 이기준
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#define MAX_PEOPLE 25


typedef enum
{
	STOPPED, UP, DOWN
} DIRECTION;

typedef struct
{
	int elevator_number;
	int current_floor;
	int request_count;
	int people;
	int door_opened;
	DIRECTION direction;
} Elevator;

typedef struct
{
	int user_floor;
	int going_floor;
	DIRECTION direction;
} Request;

int CalculateCost(Elevator* elevator, Request request);
int AssignedElevator(Request request, Elevator elevator1, Elevator elevator2);

int main(void)
{
	int elevator_number = 0;
	int current_floor = 0;
	int request_count = 0;
	int people = 0;
	int is_door_opened;

	int user_floor = 0;
	int going_floor = 0;
	DIRECTION direction = STOPPED;

	Request request;

	printf("방향: STOPPED = 0, UP = 1, DOWN = 2 중 하나\n");
	printf("문 열림 여부: 열림 = 1, 닫힘 = 0\n");
	printf("1번 엘리베이터의 상태를 입력하시오(현재 층, 요청 수, 인원 수, 문 열림 여부, 방향) : \n");
	printf("> ");
	scanf("%d %d %d %d %d", &current_floor, &request_count, &people, &is_door_opened, &direction);
	Elevator elevator1 = { 1, current_floor, request_count, people, is_door_opened, direction };

	printf("2번 엘리베이터의 상태를 입력하시오(현재 층, 요청 수, 인원 수, 문 열림 여부, 방향) : \n");
	printf("> ");
	scanf("%d %d %d %d %d", &current_floor, &request_count, &people, &is_door_opened, &direction);
	Elevator elevator2 = { 2, current_floor, request_count, people, is_door_opened, direction };

	printf("현재 있는 층수와 몇층을 갈 지 입력하시오(현재층수 갈층수) :\n");
	printf("> ");
	scanf("%d %d", &user_floor, &going_floor);
	if (user_floor < going_floor)
	{
		request.user_floor = user_floor;
		request.going_floor = going_floor;
		request.direction = UP;

		int assigned = AssignedElevator(request, elevator1, elevator2);
		printf("엘리베이터 %d번이 요청을 처리합니다.", assigned);
	}
	else if (user_floor > going_floor)
	{
		request.user_floor = user_floor;
		request.going_floor = going_floor;
		request.direction = DOWN;

		int assigned = AssignedElevator(request, elevator1, elevator2);
		printf("엘리베이터 %d번이 요청을 처리합니다.", assigned);
	}
	else
	{
		request.user_floor = user_floor;
		request.going_floor = going_floor;
		request.direction = STOPPED;
		printf("현재 있는 층과 같은 층입니다.");
	}
	system("pause");
	return 0;
}

int CalculateCost(Elevator* elevator, Request request)
{
	int cost = 0;
	if (elevator->people == MAX_PEOPLE)
	{
		return INT_MAX; // 정원이 꽉 찼으니까 비용을 무한대로 함.
	}
	else if (elevator->people < MAX_PEOPLE)
	{
		if (elevator->direction != request.direction)
		{
			if (elevator->door_opened)
			{
				cost = abs(elevator->current_floor - request.going_floor) + 1 + 1; //방향 다르고, door_opend가 true니까 페널티 + 2;
				return cost;
			}
			else
			{
				cost = abs(elevator->current_floor - request.going_floor) + 1; //방향 다르고, door_opend이니까 페널티 +1
				return cost;
			}
		}
		else if (elevator->direction == request.direction)
		{
			if (elevator->door_opened)
			{
				cost = abs(elevator->current_floor - request.going_floor) + 1; //방향 같고door_opend에 대한 페널티 +1
				return cost;
			}
			else
			{
				cost = abs(elevator->current_floor - request.going_floor); //방향 같고, door_opened 아니니니까 페널티 없음
				return cost;
			}
		}
		else
		{
			return INT_MAX;
		}
	}
	else
	{
		return INT_MAX;
	}
}

int AssignedElevator(Request request, Elevator elevator1, Elevator elevator2)
{
	int elevator1_cost = CalculateCost(&elevator1, request) + elevator1.request_count;
	int elevator2_cost = CalculateCost(&elevator2, request) + elevator2.request_count;
	int moving_elevator = (elevator1_cost <= elevator2_cost) ? elevator1.elevator_number : elevator2.elevator_number;

	if (request.user_floor == elevator1.current_floor && request.direction == elevator1.direction && elevator1.door_opened)
	{
		return elevator1.elevator_number;
	}
	else if (request.user_floor == elevator2.current_floor && request.direction == elevator2.direction && elevator2.door_opened)
	{
		return elevator2.elevator_number;
	}
	else
	{
		return moving_elevator;
	}
}
