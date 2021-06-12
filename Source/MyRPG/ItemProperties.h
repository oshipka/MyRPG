// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <string>
#include <list>

/**
 * 
 */
class MYRPG_API ItemProperties
{
public:
	int itemId;
	int itemTypeId;
	std::string itemName;
	double itemWeight;

	//todo: effects list
	//std::list<Effects> effects

	ItemProperties();
	~ItemProperties();
};
