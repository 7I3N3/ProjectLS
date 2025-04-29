// Fill out your copyright notice in the Description page of Project Settings.


#include "LS_TestItem.h"
#include "LS_Character.h"

ALS_TestItem::ALS_TestItem()
{
	
}

void ALS_TestItem::BeginPlay()
{
	Super::BeginPlay();

	InteractionOptions.Add(TEXT("Test1"), [this](ALS_Character* Interactor) { ALS_TestItem::TestInteractionOptionFunction1(); });
	InteractionOptions.Add(TEXT("Test2"), [this](ALS_Character* Interactor) { ALS_TestItem::TestInteractionOptionFunction2(); });
	InteractionOptions.Add(TEXT("Test3"), [this](ALS_Character* Interactor) { ALS_TestItem::TestInteractionOptionFunction3(); });

	InteractionOptions.Add(TEXT("Take"), [this](ALS_Character* Interactor) { ALS_TestItem::TakeItem(Interactor); });
}

void ALS_TestItem::ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController)
{
	Super::ExecuteInteraction(SelectedOption, PlayerController);
}

void ALS_TestItem::TakeItem(ALS_Character* Taker)
{
	if (!Taker) return;

	if (Taker->TakeItem(this))
	{
		if (ItemMesh)
		{
			ItemMesh->SetSimulatePhysics(false);
			ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}

void ALS_TestItem::TestInteractionOptionFunction1()
{
	UE_LOG(LogTemp, Log, TEXT("Test1 Interacted!"));
}
void ALS_TestItem::TestInteractionOptionFunction2()
{
	UE_LOG(LogTemp, Log, TEXT("Test2 Interacted!"));
}
void ALS_TestItem::TestInteractionOptionFunction3()
{
	UE_LOG(LogTemp, Log, TEXT("Test3 Interacted!"));
}