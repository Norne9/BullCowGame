// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

UBullCowCartridge::UBullCowCartridge()
{
	MaxLives = 10;
}

void UBullCowCartridge::BeginPlay() // When the game starts
{
	Super::BeginPlay();
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
			AskAgain();
		}
		else
		{
			const int Bulls = GetBulls(LowerInput);
			const int Cows = GetCows(LowerInput);

			PrintLine(FString::Printf(TEXT("Lives: %d/%d"), CurrentLives, MaxLives));
			PrintLine(FString::Printf(TEXT("Bulls: %d"), Bulls));
			PrintLine(FString::Printf(TEXT("Cows: %d"), Cows));
		}
	}
}

void UBullCowCartridge::ChangeWord()
{
	CurrentLives = MaxLives;
	SetHiddenWord(TEXT("Word"));
	PrintLine(FString::Printf(TEXT("Try guessing %d character word"), HiddenWord.Len()));
}

void UBullCowCartridge::SetHiddenWord(const FString& Word)
{
	HiddenWord = Word.ToLower();
	UE_LOG(LogTemp, Display, TEXT("Word set to \"%s\""), *HiddenWord);
	HiddenWordChars.Empty();
	HiddenWordChars.Append(HiddenWord.GetCharArray());
}

int UBullCowCartridge::GetBulls(const FString& Input) const
{
	const int MaxLen = FMath::Min(Input.Len(), HiddenWord.Len());
	int BullCount = 0;
	for (int i = 0; i < MaxLen; ++i)
	{
		if (Input[i] == HiddenWord[i])
		{
			BullCount += 1;
		}
	}
	return BullCount;
}

int UBullCowCartridge::GetCows(const FString& Input) const
{
	int CowCount = 0;
	for (TCHAR c : Input)
	{
		if (HiddenWordChars.Contains(c))
		{
			CowCount += 1;
		}
	}
	return CowCount;
}

void UBullCowCartridge::AskAgain() const
{
	PrintLine(TEXT("Play again? (Yes/no)"));
}
