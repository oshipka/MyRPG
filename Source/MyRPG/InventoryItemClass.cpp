// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemClass.h"

InventoryItemClass::InventoryItemClass()
{
	itemWidth = 1;
	itemHeight = 1;
	properties = new ItemProperties();
}

InventoryItemClass::InventoryItemClass(ItemProperties* newProperties, int width, int height)
{
	itemWidth = width;
	itemHeight = height;
	properties = newProperties;
}

InventoryItemClass::~InventoryItemClass()
{
}
