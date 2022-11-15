#include <stdio.h>

void FirstMenu()
{
    printf("Welcome to the server!!!\nPlease enter a choice\n1.Registrate to server\n2.Login to the server\n3.Close the program\nChoice: ");
}

void EnterUserName()
{
    printf("Please enter UserName: ");
}

void EnterPass()
{
    printf("Please enter password: ");
}

void RegSuccess()
{
    printf("Registrate to server Successfully\n");
}

void RegFail()
{
    printf("Registration fail\n");
}

void LoginSuccess()
{
    printf("Login to server Successfully\n");
}

void LoginFail()
{
    printf("Login fail\n");
}

void GroupMenu()
{
    printf("Please enter a choice\n1. Join group\n2. Leave group\n3. Create group\n4.Logout from server\n");
}

void CloseProg()
{
    printf("close\n");
}