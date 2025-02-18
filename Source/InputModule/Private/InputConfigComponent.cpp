// Fill out your copyright notice in the Description page of Project Settings.


#include "InputConfigComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputConfigSave.h"
#include "Kismet/GameplayStatics.h"
#include "InputMappingContext.h"
#include "BaseInputComponent.h"
#include "InputAction.h"
#include "GameFramework/Character.h"

UInputConfigComponent::UInputConfigComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UInputConfigComponent::BeginPlay()
{
	Super::BeginPlay();
	
	LoadKeyBindings();
}

void UInputConfigComponent::RegisterInputComponent(UBaseInputComponent* InputComponent)
{
    if (InputComponent && InputComponent->InputAction)
    {
        InputMappings.Add(InputComponent, InputComponent->InputAction);
    }
}
void UInputConfigComponent::RegisterAllInputComponents()
{
    if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
    {
        TArray<UBaseInputComponent*> TempInputComponents;

        Character->GetComponents<UBaseInputComponent>(TempInputComponents);

        if (TempInputComponents.Num() > 0)
        {
            for (UBaseInputComponent* InputComponent : TempInputComponents)
            {
                RegisterInputComponent(InputComponent);
            }
        }
    }
}

void UInputConfigComponent::OnControllerChanged()
{
    if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
    {
        if (APlayerController* PlayerController = Cast<APlayerController>(Character->Controller))
        {
            InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
            if (InputSubsystem && DefaultMappingContext)
            {
                InputSubsystem->AddMappingContext(DefaultMappingContext, 0);
            }
        }
    }
}

void UInputConfigComponent::SetupInput(UEnhancedInputComponent* InputComponent)
{
    if (!InputComponent) return;

    EnhancedInputComponent = InputComponent;

    OnControllerChanged();
    RegisterAllInputComponents();
    for (const auto& Pair : InputMappings)
    {
        Pair.Key->BindInput(InputComponent);
    }
}

void UInputConfigComponent::ChangeKeyBinding(UBaseInputComponent* InputComponent, FKey NewKey)
{
    if (!InputComponent || !InputSubsystem || !DefaultMappingContext) return;

    UInputAction* Action = InputMappings.FindRef(InputComponent);
    if (Action)
    {
        DefaultMappingContext->MapKey(Action, NewKey);

        InputSubsystem->ClearAllMappings();
        InputSubsystem->AddMappingContext(DefaultMappingContext, 0);
        SaveKeyBindings();
    }
}

void UInputConfigComponent::SaveKeyBindings()
{
    if (!DefaultMappingContext) return;
    
    UInputConfigSave* SaveData = Cast<UInputConfigSave>(UGameplayStatics::LoadGameFromSlot(UInputConfigSave::GetSaveSlotName(), 0));
    if (!SaveData)
    {
        SaveData = Cast<UInputConfigSave>(UGameplayStatics::CreateSaveGameObject(UInputConfigSave::StaticClass()));
    }

    SaveData->KeyBindings.Empty();
    for (const FEnhancedActionKeyMapping& Mapping : DefaultMappingContext->GetMappings())
    {
        FKeyConfig NewKey(Mapping.Action->GetFName(), Mapping.Key);
        SaveData->KeyBindings.Add(NewKey);
    }

    UGameplayStatics::SaveGameToSlot(SaveData, UInputConfigSave::GetSaveSlotName(), 0);
}

void UInputConfigComponent::LoadKeyBindings()
{
    if (!InputSubsystem || !DefaultMappingContext) return;

    if (UGameplayStatics::DoesSaveGameExist(UInputConfigSave::GetSaveSlotName(), 0))
    {
        UInputConfigSave* LoadData = Cast<UInputConfigSave>(UGameplayStatics::LoadGameFromSlot(UInputConfigSave::GetSaveSlotName(), 0));

        if (LoadData)
        {
            InputSubsystem->ClearAllMappings();

            for (const FKeyConfig& KeyConfig : LoadData->KeyBindings)
            {
                if (UInputAction* Action = FindActionByName(KeyConfig.ActionName))
                {
                    DefaultMappingContext->MapKey(Action, KeyConfig.Key);
                }
            }

            InputSubsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

UInputAction* UInputConfigComponent::FindActionByName(const FName& ActionName)
{
    for (const auto& Pair : InputMappings)
    {
        if (Pair.Value->GetFName() == ActionName)
        {
            return Pair.Value;
        }
    }
    return nullptr;
}