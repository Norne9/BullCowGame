// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"

UBullCowCartridge::UBullCowCartridge()
{
	MaxLives = 10;
}

void UBullCowCartridge::BeginPlay() // When the game starts
{
	Super::BeginPlay();

	// Load words
	const auto WordListPath = FPaths::ProjectContentDir() / TEXT("TextData/WordList.txt");
	FFileHelper::LoadFileToStringArray(Words, *WordListPath);
	
	// Start game
	PrintLine(TEXT("Welcome to game!"));
	ChangeWord();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Cyan, Input);
	ClearScreen();
	PrintLine(Input);
	const auto LowerInput = Input.ToLower();

	if (CurrentLives <= 0)
	{
		if (LowerInput.Len() >= 1 && LowerInput[0] == 'y')
		{
			ChangeWord();
		}
		else
		{
			AskAgain();
		}
		return;
	}

	if (Input == HiddenWord)
	{
		PrintLine(TEXT("You win!"));
		CurrentLives = 0;
		AskAgain();
	}
	else
	{
		CurrentLives -= 1;
		if (CurrentLives <= 0)
		{
			PrintLine(TEXT("You lose!"));
			PrintLine(FString::Printf(TEXT("The word was '%s'"), *HiddenWord));
			AskAgain();
		}
		else
		{
			const auto Count = GetBullsCows(LowerInput);

			PrintLine(FString::Printf(TEXT("Lives: %d/%d"), CurrentLives, MaxLives));
			PrintLine(FString::Printf(TEXT("Bulls: %d"), Count.Bulls));
			PrintLine(FString::Printf(TEXT("Cows: %d"), Count.Cows));
		}
	}
}

void UBullCowCartridge::ChangeWord()
{
	CurrentLives = MaxLives;
	const auto Idx = FMath::RandRange(0, Words.Num() - 1);
	SetHiddenWord(Words[Idx]);
	PrintLine(FString::Printf(TEXT("Try guessing %d character word"), HiddenWord.Len()));
}

void UBullCowCartridge::SetHiddenWord(const FString& Word)
{
	HiddenWord = Word.ToLower();
	UE_LOG(LogTemp, Display, TEXT("Word set to \"%s\""), *HiddenWord);
	HiddenWordChars.Empty();
	HiddenWordChars.Append(HiddenWord.GetCharArray());
}

FBullCowCount UBullCowCartridge::GetBullsCows(const FString& Input) const
{
	auto Count = FBullCowCount();
	const int32 MaxLen = FMath::Min(Input.Len(), HiddenWord.Len());
	for (int32 Idx = 0; Idx < MaxLen; ++Idx)
	{
		if (Input[Idx] == HiddenWord[Idx])
		{
			Count.Bulls += 1;
		}
		else if (HiddenWordChars.Contains(Input[Idx]))
		{
			Count.Cows += 1;
		}
	}
	return Count;
}

void UBullCowCartridge::AskAgain() const
{
	PrintLine(TEXT("Play again? (Yes/no)"));
}
