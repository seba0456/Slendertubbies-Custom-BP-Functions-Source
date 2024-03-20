#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SimpleBlueprintFunctionsLibrary.generated.h"

/**
 * Structure representing a top player with an ID, nickname, and points.
 */
    USTRUCT(BlueprintType)
    struct SLENDERTUBBIES_API FTopPlayer
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TopPlayer")
    FString PlayerPublicID;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TopPlayer")
    FString PlayerName;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TopPlayer")
    int32 Score; // Consider renaming "Punkty" to "Points" for consistency.
};

/**
 * A collection of simple blueprint functions.
 */
UCLASS()
class SLENDERTUBBIES_API USimpleBlueprintFunctionsLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /**
     * Generates an array of unique random numbers between MinValue and MaxValue (inclusive).
     *
     * @param MinValue The minimum value for the random numbers.
     * @param MaxValue The maximum value for the random numbers.
     * @param Count The number of random numbers to generate.
     * @return An array of unique random numbers.
     */
    UFUNCTION(BlueprintCallable, Category = "CustomFunctions", meta = (DisplayName = "Generate Unique Numbers", Description = "Generates an array of unique random numbers"))
    static TArray<int32> GenerateUniqueNumbers(int32 MinValue, int32 MaxValue, int32 Count);

    /**
     * Checks if today is Halloween.
     *
     * @return True if today is Halloween, false otherwise.
     */
    UFUNCTION(BlueprintPure, Category = "CustomFunctions", meta = (DisplayName = "Is Today Halloween?", Description = "Returns true if today is Halloween."))
    static bool bIsTodayHalloween();

    /**
     * Updates the gameversion.txt file with the provided version string.
     *
     * @param GameVersion The game version string to update.
     */
    UFUNCTION(BlueprintCallable, Category = "CustomFunctions", meta = (DisplayName = "Update gameversion.txt", Description = "Updates gameversion.txt"))
    static void UpdateGameVersionFile(FString GameVersion);

    /**
     * Runs an external application.
     *
     * @param AbsolutePath The absolute path to the external application.
     * @param Arguments The command-line arguments to pass to the external application.
     * @return True if the external application was successfully launched, false otherwise.
     */
    UFUNCTION(BlueprintCallable, Category = "CustomFunctions", meta = (DisplayName = "Run External Application", Description = "Runs External Application"))
    static bool RunExternalApp(FString AbsolutePath, FString Arguments);

    /**
     * Checks if Visual C++ Redistributable 2015 or newer is installed.
     *
     * @param bCloseGame Whether to close the game if VCRedist is not installed.
     * @return True if VCRedist is installed, false otherwise.
     */
    UFUNCTION(BlueprintCallable, Category = "CustomFunctions", meta = (DisplayName = "Is VCRedist installed", Description = "Checks if Visual C++ Redistributable Installed"))
    static bool IsVCRedist2015OrNewerInstalled(bool bCloseGame);

    /**
     * Returns the level progress in the scale of 0 to 1 based on player score.
     *
     * @param PlayerScore The player's score.
     * @return Level progress in the range of 0 to 1.
     */
    UFUNCTION(BlueprintCallable, Category = "SimpleLevelingSystem", meta = (DisplayName = "Return Level Progress", Description = "Return level progress in scale 0-1"))
    static float ReturnLevelProgress(int PlayerScore);

    /**
     * Returns the player's level based on the player's score.
     *
     * @param PlayerScore The player's score.
     * @return Player's level.
     */
    UFUNCTION(BlueprintCallable, Category = "SimpleLevelingSystem", meta = (DisplayName = "Return Level", Description = "Return player level"))
    static int CalculatePlayerLevel(int PlayerScore);

    /**
     * Checks if the player has leveled up based on current and old scores.
     *
     * @param CurrentScore The player's current score.
     * @param OldScore The player's old score.
     * @return True if the player has leveled up, false otherwise.
     */
    UFUNCTION(BlueprintCallable, Category = "SimpleLevelingSystem", meta = (DisplayName = "Have Player Leveled", Description = "Returns true when player leveled"))
    static bool HavePlayerLeveled(const int& CurrentScore, const int& OldScore);

    /**
     * Parses string and returns an array of top players.
     *
     * @param TextString The JSON string containing top player information.
     * @return An array of top players.
     */
    UFUNCTION(BlueprintCallable, Category = "CustomFunctions", meta = (DisplayName = "Parse String with top players", Description = "Parses string and returns an array of top players"))
    static TArray<FTopPlayer> ParseTopPlayers(const FString& TextString);

    /**
     * Gets unique random elements from an array.
     *
     * @param InputArray The input array from which to get unique random elements.
     * @param NumberOfElements The number of unique random elements to retrieve.
     * @return An array of unique random elements.
     */
    UFUNCTION(BlueprintCallable, Category = "CustomFunctions", meta = (DisplayName = "Get Unique Random Elements From Array", Description = "Gets unique random elements from an array"))
    static TArray<AActor*> GetUniqueRandomElementsFromArray(const TArray<AActor*>& InputArray, int32 NumberOfElements);

    /**
     * Randomizes a reward based on chances and speedrun mode.
     *
     * @param bWon Reference to a boolean indicating whether the player won.
     * @param LootId Reference to an integer representing the id of the reward.
     * @param bIsSpeedrunModeEnabled Indicates whether speedrun mode is enabled.
     */
    UFUNCTION(BlueprintCallable, Category = "CustomFunctions", meta = (DisplayName = "Randomize Reward", Description = "Randomizes a reward based on chances and speedrun mode"))
    static void RandomizeReward(bool& bWon, int32& LootId, bool bIsSpeedrunModeEnabled);

    /**
     * Adds leading zeros to a number string.
     *
     * @param Number The number to which leading zeros will be added.
     * @param Length The desired length of the resulting string. Defaults to 1.
     * @return A string representation of the number with leading zeros added.
     */
    UFUNCTION(BlueprintCallable, Category = "CustomFunctions", meta = (DisplayName = "Add Zeros", Description = "Adds leading zeros to a number string. Useful for converting 2 to 02, etc."))
    static FString AddZeros(int Number, int Length = 1);

};