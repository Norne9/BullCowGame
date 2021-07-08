// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "FBullCowCount.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	UBullCowCartridge();
	
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;

	// Your declarations go below!
private:
	UPROPERTY(EditAnywhere)
	int32 MaxLives;
	UPROPERTY(VisibleAnywhere)
	int32 CurrentLives;
	UPROPERTY(VisibleAnywhere)
	TArray<FString> Words;
	UPROPERTY(VisibleAnywhere)
	FString HiddenWord;
	TSet<TCHAR> HiddenWordChars;

	void ChangeWord();
	void SetHiddenWord(const FString& Word);
	FBullCowCount GetBullsCows(const FString&) const;
	void AskAgain() const;
};
