

#include "SimpleBlueprintFunctionsLibrary.h"
#include <ctime>
#include "Misc/FileHelper.h"
#include "Internationalization/Text.h"
#include "Windows/MinWindows.h"
#include "Windows/AllowWindowsPlatformTypes.h" 
#include "Windows/HideWindowsPlatformTypes.h" 
#include "Math/UnrealMathUtility.h"

TArray<int32> USimpleBlueprintFunctionsLibrary::GenerateUniqueNumbers(int32 MinValue, int32 MaxValue, int32 Count)
{
	if (Count > (MaxValue - MinValue + 1))
	{
		UE_LOG(LogTemp, Warning, TEXT("Error: Cannot generate that many unique numbers in the given range."));
		return TArray<int32>();
	}

	TArray<int32> Result;
	for (int32 i = MinValue; i <= MaxValue; ++i)
	{
		Result.Add(i);
	}

	Result.Sort([](const int32 A, const int32 B) { return FMath::FRand() < 0.5f; }); // Random shuffle

	if (Count < Result.Num())
	{
		Result.SetNum(Count); // Truncate to the expected number of elements
	}

	return Result;
}

bool USimpleBlueprintFunctionsLibrary::bIsTodayHalloween()
{
	// current date/time based on current system
	time_t now = time(0);
	tm* ltm = localtime(&now);
	if (ltm != nullptr) {
		int day = ltm->tm_mday;
		int month = 1 + ltm->tm_mon;
		if (day == 31 && month == 10)
		{
			UE_LOG(LogTemp, Log, TEXT("Today is Halloween!"));
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Today is NOT Halloween!"));
			return false;
		}
	}
	else {
		// Log error
		UE_LOG(LogTemp, Error, TEXT("Local time could not be obtained."));
		return false;
	}
}

void USimpleBlueprintFunctionsLibrary::UpdateGameVersionFile(FString gameversion)
{
	// Create a path to the gameversion.txt file in the parent directory of the current directory
	FString FilePath = FPaths::ProjectContentDir() + TEXT("../../gameversion.txt");

	// New content to be written to the file
	FString NewContent = gameversion.Replace(TEXT("Version "), TEXT(""));

	// Check if the file exists
	if (FPaths::FileExists(FilePath))
	{
		// If the file exists, load its content
		FString FileContent;
		FFileHelper::LoadFileToString(FileContent, *FilePath);

		// If the file content is different from the new content, overwrite the file
		if (FileContent != NewContent)
		{
			FFileHelper::SaveStringToFile(NewContent, *FilePath);
		}
	}
	else
	{
		// If the file doesn't exist, create a new one
		FFileHelper::SaveStringToFile(NewContent, *FilePath);
	}
}

bool USimpleBlueprintFunctionsLibrary::RunExternalApp(FString AbsolutePath, FString Arguments)
{
	// Configure process execution options
	FProcHandle ProcessHandle = FPlatformProcess::CreateProc(
		*AbsolutePath,
		*Arguments,
		false,  // Set to false to hide the console window
		true,   // Set to true to detach the process from the console
		false,
		nullptr,
		0,
		nullptr,
		nullptr
	);

	if (ProcessHandle.IsValid())
	{
		// The process was successfully created
		FPlatformProcess::CloseProc(ProcessHandle);
		return true;
	}
	else
	{
		// Error during process creation
		UE_LOG(LogTemp, Error, TEXT("Error while running an external program. Path: %s, Arguments: %s"), *AbsolutePath, *Arguments);
		return false;
	}
}

bool USimpleBlueprintFunctionsLibrary::IsVCRedist2015OrNewerInstalled(bool bCloseGame)
{
	// Construct the registry key name for 64-bit version of VC++ Redistributable 2015 and newer
	TCHAR regKeyName[256];
	_stprintf_s(regKeyName, _T("SOFTWARE\\Wow6432Node\\Microsoft\\VisualStudio\\14.0\\VC\\Runtimes\\x64"));

	// Open the registry key
	HKEY hKey;
	LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, regKeyName, 0, KEY_READ, &hKey);

	// Check if the key exists
	if (result == ERROR_SUCCESS)
	{
		// The key exists, indicating that VC++ Redistributable 2015 or newer is installed
		RegCloseKey(hKey);
		return true;
	}

	// The key does not exist, indicating that VC++ Redistributable 2015 or newer is not installed
	if (bCloseGame)
	{
		MessageBox(nullptr, _T("Visual C++ Redistributable 2015 or newer for 64-bit machines is not installed. Please install the required libraries."), _T("Error"), MB_OK | MB_ICONERROR);

		// Exit the application
		FGenericPlatformMisc::RequestExit(false);
	}
	// Display an error message box


	return false;
}
float USimpleBlueprintFunctionsLibrary::ReturnLevelProgress(int PlayerScore)
{
	int RemainingScore = PlayerScore % 200;
	float RemainingScoreAsPercent = static_cast<float>(RemainingScore) / 200.0f;
	return RemainingScoreAsPercent;
}
int USimpleBlueprintFunctionsLibrary::CalculatePlayerLevel(int PlayerScore)
{
	int PlayerLevel = (floor(PlayerScore / 200) + 1);
	return PlayerLevel;
}
bool USimpleBlueprintFunctionsLibrary::HavePlayerLeveled(const int& CurrentScore, const int& OldScore)
{
	int OldPlayerLevel = CalculatePlayerLevel(OldScore);
	int NewLevel = CalculatePlayerLevel(CurrentScore);
	return OldPlayerLevel != NewLevel;
}

TArray<FTopPlayer> USimpleBlueprintFunctionsLibrary::ParseTopPlayers(const FString& TextString)
{
	// Array to hold parsed top players
	TArray<FTopPlayer> LoadedPlayers;

	// Split the text into individual player pairs
	TArray<FString> PlayerPairs;
	TextString.ParseIntoArray(PlayerPairs, TEXT("),("), true);

	// Iterate through each player pair
	for (const FString& PlayerPair : PlayerPairs)
	{
		// Remove parentheses from each pair
		FString CleanedPair = PlayerPair.Replace(TEXT("("), TEXT("")).Replace(TEXT(")"), TEXT(""));

		// Split the pair into individual values
		TArray<FString> PlayerValues;
		CleanedPair.ParseIntoArray(PlayerValues, TEXT(","), true);

		// Check if the pair contains correct number of values
		if (PlayerValues.Num() == 3)
		{
			// Create a new FTopPlayer object
			FTopPlayer Player;
			Player.PlayerPublicID = PlayerValues[0];
			Player.PlayerName = PlayerValues[1];
			Player.Score = FCString::Atoi(*PlayerValues[2]);

			// Add the player to the loaded players array
			LoadedPlayers.Add(Player);
		}
		else
		{
			// Handle error for invalid number of values in pair
			UE_LOG(LogTemp, Error, TEXT("Invalid player pair: %s"), *PlayerPair);
		}
	}

	// Return the array of loaded players
	return LoadedPlayers;
}

TArray<AActor*> USimpleBlueprintFunctionsLibrary::GetUniqueRandomElementsFromArray(const TArray<AActor*>& InputArray, int32 NumberOfElements)
{
	// Check if the input array contains enough elements
	if (InputArray.Num() < NumberOfElements)
	{
		// If not, return an empty array or handle the error appropriately
		return TArray<AActor*>();
	}

	// Copy the input array to avoid modifying its original version
	TArray<AActor*> ModifiedArray = InputArray;

	// Prepare the result array
	TArray<AActor*> ResultArray;

	// Set seed for the random number generator (optional)
	FMath::RandInit(FDateTime::Now().ToUnixTimestamp());

	// Generate the specified number of unique indices
	for (int32 i = 0; i < NumberOfElements; ++i)
	{
		// Select a random index from the modified array
		int32 RandomIndex = FMath::RandRange(0, ModifiedArray.Num() - 1);

		// Add the selected element to the result array
		ResultArray.Add(ModifiedArray[RandomIndex]);

		// Remove this element from the modified array to prevent it from being selected again
		ModifiedArray.RemoveAt(RandomIndex);
	}

	return ResultArray;
}

void USimpleBlueprintFunctionsLibrary::RandomizeReward(bool& bWon, int32& LootId, bool bIsSpeedrunModeEnabled)
{
	// Chance for each of the elements
	float Chance1 = 0.2f;
	float Chance2 = 0.1f;

	// Adjust chances if speedrun mode is enabled
	if (bIsSpeedrunModeEnabled)
	{
		Chance1 *= 3;
		Chance2 *= 3;
	}

	// Randomize the id of the element
	float Rand = FMath::FRand();  // Random number in the range [0, 1)

	if (Rand < Chance1)
	{
		LootId = 1;
	}
	else if (Rand < Chance1 + Chance2)
	{
		LootId = 2;
	}
	else
	{
		LootId = 0; // No win
	}

	// Check if the player won
	bWon = (LootId != 0);
}


FString USimpleBlueprintFunctionsLibrary::AddZeros(int Number, int Length)
{
	// Convert the number to a string
	FString NumberStr = FString::FromInt(Number);

	// Calculate the number of missing zeros
	int MissingZeros = Length - NumberStr.Len();

	// String to hold the zeros
	FString Zeros;

	// If there are missing zeros, add them to the beginning of the number
	if (MissingZeros > 0)
	{
		for (int i = 0; i < MissingZeros; i++)
		{
			Zeros += "0";
		}
		return Zeros + NumberStr;
	}
	else
	{
		// If no missing zeros, return the original number string
		return NumberStr;
	}
}
