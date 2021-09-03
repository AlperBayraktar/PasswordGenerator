#include "Frame.h"
#include <iostream>



int Frame::PointsLength()
{
	int l = 0;
	for (int i = 0; i < 6; i++)
		if (points[i] != 0)
			l++;
		else
			break;

	return l;
}

void Frame::AddPoint(int add)
{
	points[PointsLength()] = add;
}

void Frame::AddIfHaveOne(std::string chars, int add)
{
	for (int i = 0; i < chars.length(); i++)
	{
		if (password.find(chars[i]) != std::string::npos)
		{
			AddPoint(add);
			return;
		}
	}
}


int Frame::PasswordStrength()
{
	/*
	---- Found From Stack overflow link is at github repo's README.md ---
	At least 8 characters - 10 pts
	At least a lowercase char - 5 pts
	At least a uppercase char - 5 pts
	At least a digit - 5 pts
	At least a symbol - 10 pts
	5 unique characters at least  - 5 pts

	Result:
	total points + how many points * 10
	*/


	// Setup
	uniques = "";
	for (int i = 0; i < 6; i++)
		points[i] = 0;

	// Length
	if (passwordLength >= 9)
		AddPoint(10);

	// At least a ? char - ? pts
	AddIfHaveOne(CHARS.LOWERCASE, 5);
	AddIfHaveOne(CHARS.UPPERCASE, 5);
	AddIfHaveOne(CHARS.DIGITS, 5);
	AddIfHaveOne(CHARS.SYMBOLS, 10);

	// 5 unique characters
	for (int i = 0; i < passwordLength; i++)
	{
		if (uniques.find(password[i]) == std::string::npos)
			uniques += password[i];
	}
	if (uniques.length() >= 5)
		AddPoint(5);

	// Return
	int total = 0;
	for (int i = 0; i < PointsLength(); i++)
		total += points[i];

	int result = total + PointsLength() * 10;

	return result;
}
