# Slendertubbies Custom Functions Source 

Slendertubbies was built using the Blueprint visual scripting language; however, a few functions have been written in C++. This repository contains some interesting functions, so feel free to use my code in your project. ^^

## The functions 

*Slendertubbies\Public\SimpleBlueprintFunctionsLibrary.h*

### `GenerateUniqueNumbers(int32 MinValue, int32 MaxValue, int32 Count)`
Generates an array of unique random numbers between `MinValue` and `MaxValue` (inclusive).

### `bIsTodayHalloween()`
Checks if today is Halloween.
- Returns `true` if today is Halloween, `false` otherwise.

### `UpdateGameVersionFile(FString GameVersion)`
Updates the `gameversion.txt` file with the provided version string.

### `RunExternalApp(FString AbsolutePath, FString Arguments)`
Runs an external application.
- Returns `true` if the external application was successfully launched, `false` otherwise.

### `IsVCRedist2015OrNewerInstalled(bool bCloseGame)`
Checks if Visual C++ Redistributable 2015 or newer is installed.
- Returns `true` if VCRedist is installed, `false` otherwise.

### `ReturnLevelProgress(int PlayerScore)`
Returns the level progress in the scale of 0 to 1 based on player score.

### `CalculatePlayerLevel(int PlayerScore)`
Returns the player's level based on the player's score.

### `HavePlayerLeveled(const int& CurrentScore, const int& OldScore)`
Checks if the player has leveled up based on current and old scores.
- Returns `true` if the player has leveled up, `false` otherwise.

### `ParseTopPlayers(const FString& TextString)`
Parses string and returns an array of top players.

### `GetUniqueRandomElementsFromArray(const TArray<AActor*>& InputArray, int32 NumberOfElements)`
Gets unique random elements from an array.

### `RandomizeReward(bool& bWon, int32& LootId, bool bIsSpeedrunModeEnabled)`
Randomizes a reward based on chances and speedrun mode.

### `AddZeros(int Number, int Length = 1)`
Adds leading zeros to a number string.
- Returns a string representation of the number with leading zeros added.

*Slendertubbies\Public\ActorOperations.h*

### `FindClosestActor(TArray<AActor*> Actors, AActor* Player)`
Finds the closest actor to the specified player from an array of actors.
- Returns a reference to the closest actor.

### `GetDistanceToClosestActor(TArray<AActor*> Actors, AActor* Player)`
Calculates the distance to the closest actor in the array for the specified player.
- Returns the distance to the closest actor. Returns -1 if no closest actor is found.
