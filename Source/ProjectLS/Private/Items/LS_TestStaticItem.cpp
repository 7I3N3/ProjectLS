// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/LS_TestStaticItem.h"

ALS_TestStaticItem::ALS_TestStaticItem()
{
	
}

void ALS_TestStaticItem::BeginPlay()
{
	Super::BeginPlay();

	InteractionOptions.Add(TEXT("Test1"), [this]() { ALS_TestStaticItem::TestInteractionOptionFunction1(); });
	InteractionOptions.Add(TEXT("Test2"), [this]() { ALS_TestStaticItem::TestInteractionOptionFunction2(); });
	InteractionOptions.Add(TEXT("Test3"), [this]() { ALS_TestStaticItem::TestInteractionOptionFunction3(); });
}

void ALS_TestStaticItem::ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController)
{
	Super::ExecuteInteraction(SelectedOption, PlayerController);
}

void ALS_TestStaticItem::TestInteractionOptionFunction1()
{
	UE_LOG(LogTemp, Log, TEXT("Test1 Interacted!"));
}
void ALS_TestStaticItem::TestInteractionOptionFunction2()
{
	UE_LOG(LogTemp, Log, TEXT("Test2 Interacted!"));
}
void ALS_TestStaticItem::TestInteractionOptionFunction3()
{
	UE_LOG(LogTemp, Log, TEXT("Test3 Interacted!"));
}