// Fill out your copyright notice in the Description page of Project Settings.


#include "LS_BaseBullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ALS_BaseBullet::ALS_BaseBullet()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RootComponent = CollisionComponent;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = Speed;
	ProjectileMovement->MaxSpeed = Speed;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	CollisionComponent->OnComponentHit.AddDynamic(this, &ALS_BaseBullet::OnHit);
}

void ALS_BaseBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALS_BaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALS_BaseBullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), this, UDamageType::StaticClass());

		UE_LOG(LogTemp, Log, TEXT("Bullet Hit"));
		// 벽 관통 로직 추가할 것
		Destroy();
	}
}

void ALS_BaseBullet::FireInDirection(const FVector& Direction)
{
	if(ProjectileMovement)
	{
		ProjectileMovement->Velocity = Direction * Speed;
	}
}

