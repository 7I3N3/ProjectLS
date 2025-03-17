// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

template<typename TEnum>
FString EnumToString(TEnum Value)
{
	const UEnum* EnumPtr = StaticEnum<TEnum>();
	if (!EnumPtr)
	{
		return TEXT("Invalid");
	}

	return EnumPtr->GetNameStringByIndex(static_cast<int32>(Value));
}