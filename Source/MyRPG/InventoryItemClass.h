// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include "CoreMinimal.h"
#include "ItemProperties.h"

/**
 * 
 */


class MYRPG_API InventoryItemClass
{
public:

	int itemWidth;
	int itemHeight;
	ItemProperties* properties;
	InventoryItemClass();
	InventoryItemClass(ItemProperties* newProperties, int width =1, int height =1);
	~InventoryItemClass();
};
