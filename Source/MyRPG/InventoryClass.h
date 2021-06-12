// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include <list>
#include "CoreMinimal.h"
#include "InventoryItemClass.h"

/**
 * 
 */
class MYRPG_API InventoryClass
{
public:
	std::list<InventoryItemClass> items;
	int inventoryWidth;
	int inventoryHeight;


	InventoryClass();
	~InventoryClass();
};
