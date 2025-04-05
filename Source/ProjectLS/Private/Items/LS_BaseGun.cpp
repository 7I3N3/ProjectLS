// Fill out your copyright notice in the Description page of Project Settings.


#include "LS_BaseGun.h"

ALS_BaseGun::ALS_BaseGun()
{

}

void ALS_BaseGun::BeginPlay()
{
	Super::BeginPlay();

	InteractionOptions.Add(TEXT("Take"), [this]() { ALS_BaseGun::Take(); });
	InteractionOptions.Add(TEXT("Equip"), [this]() { ALS_BaseGun::Equip(); });
	InteractionOptions.Add(TEXT("Examine"), [this]() { ALS_BaseGun::Examine(); });
}

void ALS_BaseGun::Take()
{

}

void ALS_BaseGun::Equip()
{

}

void ALS_BaseGun::Examine()
{

}


void ALS_BaseGun::ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController)
{
	Super::ExecuteInteraction(SelectedOption, PlayerController);
}

bool ALS_BaseGun::AttachAttachment(EAttachmentSlotType SlotType, FName SlotName, TScriptInterface<ILS_Attachable> NewAttachment)
{
	if (!NewAttachment) return false;

	// ºó ½½·ÔÀÌ ÀÖÀ¸¸é
	for (auto& Slot : Attachments)
	{
		if (Slot.SlotType == SlotType && !Slot.Attachment)
		{
			Slot.Attachment = NewAttachment; 

			NewAttachment->OnAttached(this, Slot.SlotName);

			return true;
		}
	}

	//ºó ½½·ÔÀÌ ¾øÀ¸¸é SlotName¿¡ ¸Â°Ô ±³Ã¼
	for (auto& Slot : Attachments)
	{
		if (Slot.SlotType == SlotType && Slot.SlotName == SlotName)
		{
			DetachAttachment(SlotType, SlotName);

			Slot.Attachment = NewAttachment;

			NewAttachment->OnAttached(this, Slot.SlotName);

			return true;
		}
	}

	return false;
}

bool ALS_BaseGun::DetachAttachment(EAttachmentSlotType SlotType, FName SlotName)
{
	for (auto& Slot : Attachments)
	{
		if (Slot.SlotType == SlotType && Slot.SlotName == SlotName)
		{
			if (Slot.Attachment)
			{
				Slot.Attachment->OnDetached();

				Slot.Attachment = nullptr;
				return true;
			}
		}
	}

	return false;
}