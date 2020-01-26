#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

template<class TMeshComponent, class TShapeComponent>
class TAItem : public AActor
{
	TAItem()
	{
		// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		PrimaryActorTick.bCanEverTick = false;

		collisionComponent = CreateDefaultSubobject<TShapeComponent>();;
		collisionComponent->SetupAttachment(GetRootComponent());
		SetRootComponent(collisionComponent);

		meshComponent = CreateDefaultSubobject<TMeshComponent>();;
		meshComponent->SetupAttachment(newCollisionComponent);
	}

protected:
	UPROPERTY(VisibleAnywhere)
		TMeshComponent* meshComponent;
	UPROPERTY(VisibleAnywhere)
		TShapeComponent* collisionComponent;

};