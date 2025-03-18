// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInputComponent.h"

UBaseInputComponent::UBaseInputComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UBaseInputComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBaseInputComponent::BeginPlay()
{
	Super::BeginPlay();

}
