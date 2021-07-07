// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
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
	int MaxLives;
	UPROPERTY(VisibleAnywhere)
	int CurrentLives;
	UPROPERTY(VisibleAnywhere)
	FString HiddenWord;
	TSet<TCHAR> HiddenWordChars;

	void ChangeWord();
	void SetHiddenWord(const FString& Word);
	int GetBulls(const FString& Input) const;
	int GetCows(const FString& Input) const;
	void AskAgain() const;
};
