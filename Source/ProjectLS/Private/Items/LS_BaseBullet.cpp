// Fill out your copyright notice in the Description page of Project Settings.


#include "LS_BaseBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"

ALS_BaseBullet::ALS_BaseBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh->SetNotifyRigidBodyCollision(true);
	ItemMesh->SetSimulatePhysics(false);
	ItemMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	ItemMesh->OnComponentHit.AddDynamic(this, &ALS_BaseBullet::OnBulletHit);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = MaxSpeed;
	ProjectileMovement->MaxSpeed = MaxSpeed;
	ProjectileMovement->ProjectileGravityScale = GravityScale;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = Bounciness;
	ProjectileMovement->Friction = Friction;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bInitialVelocityInLocalSpace = true;
}

void ALS_BaseBullet::BeginPlay()
{
	Super::BeginPlay();

	PreviousLocation = GetActorLocation();
}

void ALS_BaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsActive) return;

	FVector CurrentLocation = GetActorLocation();
	float CurrentSpeed = ProjectileMovement->Velocity.Size();

	float SpeedRatio = FMath::Clamp(CurrentSpeed / MaxSpeed, 0.0f, 1.0f);
	float Hue = SpeedRatio * 120.0f; // 120 �� 0 ���� ������ ����
	FLinearColor HSVColor = FLinearColor::MakeFromHSV8((uint8)Hue, 255, 255);
	FColor LineColor = HSVColor.ToFColor(true);

	DrawDebugLine(GetWorld(), PreviousLocation, CurrentLocation, LineColor, false, 1.0f, 0, 1.5f );

	PreviousLocation = CurrentLocation;

	ProjectileMovement->Velocity *= 0.995f;
}

void ALS_BaseBullet::ExecuteInteraction(const FString& SelectedOption, APlayerController* PlayerController)
{
	Super::ExecuteInteraction(SelectedOption, PlayerController);
}

void ALS_BaseBullet::ActivateBullet(FVector Direction, float Speed)
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
	bIsActive = true;

	ProjectileMovement->Velocity = Direction * Speed;
	ProjectileMovement->Activate();
}

void ALS_BaseBullet::DeactivateBullet()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
	bIsActive = false;

	ProjectileMovement->StopMovementImmediately();
}

void ALS_BaseBullet::OnBulletHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor || OtherActor == GetOwner()) return;

	FVector BulletDirection = ProjectileMovement->Velocity.GetSafeNormal();
	FVector HitNormal = Hit.Normal;

	bool bShouldRicochet = ShouldRicochet(HitNormal, BulletDirection);

	if (!bShouldRicochet)
	{
		// ����
		// ������
		// Ǯ�� ����
		DeactivateBullet();
		return;
	}

	// ��ź
	FVector ReflectDir = FMath::GetReflectionVector(BulletDirection, HitNormal);
	ReflectDir = ReflectDir.GetSafeNormal();

	// �ӵ� ������ ������Ʈ�� ������ ���� ����
	float NewSpeed = ProjectileMovement->Velocity.Size() * 0.5f;

	ProjectileMovement->Velocity = ReflectDir * NewSpeed;

	SetActorRotation(ReflectDir.Rotation());
}

bool ALS_BaseBullet::ShouldRicochet(const FVector& HitNormal, const FVector& BulletDirection) const
{
	float Dot = FVector::DotProduct(HitNormal, -BulletDirection);
	float AngleDegrees = FMath::RadiansToDegrees(FMath::Acos(Dot));

	if (FMath::Abs(AngleDegrees - 90.0f) <= 5.0f)
	{
		return false; // ���� ó��
	}

	float RicochetChance = FMath::Clamp(1.0f - Sharpness, 0.0f, 1.0f);
	return FMath::FRand() < RicochetChance;
}