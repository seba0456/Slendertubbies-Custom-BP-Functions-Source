#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ActorOperations.generated.h"

UCLASS()
class SLENDERTUBBIES_API UActorOperations : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	//Line skip 1
	//Line skip 2

public:
    /**
     * Finds the closest actor to the specified player from an array of actors.
     *
     * @param Actors The array of actors to search.
     * @param Player The player actor.
     * @return A reference to the closest actor.
     */
    UFUNCTION(BlueprintCallable, Category = "Actor Operations", meta = (DisplayName = "Get Closest Actor", Description = "Returns a reference to the closest actor to the specified actor from an array of actors."))
    static AActor* FindClosestActor(TArray<AActor*> Actors, AActor* Player);

    /**
     * Calculates the distance to the closest actor in the array for the specified player.
     *
     * @param Actors The array of actors to search.
     * @param Player The player actor.
     * @return The distance to the closest actor. Returns -1 if no closest actor is found.
     */
    UFUNCTION(BlueprintCallable, Category = "Actor Operations", meta = (DisplayName = "Get Distance to Closest Actor in Array", Description = "Returns the distance to the closest actor from array for the specified player."))
    static float GetDistanceToClosestActor(TArray<AActor*> Actors, AActor* Player);
};