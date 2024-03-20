#include "ActorOperations.h"

AActor* UActorOperations::FindClosestActor(TArray<AActor*> Actors, AActor* Player)
{
    // Initialize variables to store the closest actor and the minimum distance
    AActor* ClosestActor = nullptr;
    float MinDistance = TNumericLimits<float>::Max();

    // Iterate through each actor in the array
    for (AActor* Actor : Actors)
    {
        // Calculate the distance between the current actor and the player
        float Distance = FVector::Dist(Actor->GetActorLocation(), Player->GetActorLocation());

        // Update the closest actor if the current distance is smaller than the minimum distance
        if (Distance < MinDistance)
        {
            MinDistance = Distance;
            ClosestActor = Actor;
        }
    }

    // Return the closest actor found
    return ClosestActor;
}

float UActorOperations::GetDistanceToClosestActor(TArray<AActor*> Actors, AActor* Player)
{
    // Initialize the distance to a default value
    float Distance = -1.0f;

    // Find the closest actor to the player
    AActor* ClosestActor = FindClosestActor(Actors, Player);

    // If a closest actor is found, calculate the distance between the player and that actor
    if (ClosestActor)
    {
        Distance = FVector::Dist(ClosestActor->GetActorLocation(), Player->GetActorLocation());
    }

    // Return the calculated distance
    return Distance;
}
